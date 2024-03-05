import * as vscode from "vscode";
import { existsSync, readFileSync } from "fs";
import * as path from "node:path";
import Channel from "../utils/channel";
import {
  getConf,
  getCoreDAppUrl,
  DeploymentArgsCache,
} from "../utils/configure";
import collectDependency, { ContractItem } from "../utils/parser";

import { getCurrentActiveFileAndFolder, getConfigName } from "../utils/finder";
import { WSServer } from "../wss";
import Fetcher from "../utils/webapi";

let wss: WSServer | null = null;
let outputChannel: Channel;

function Inputbox(params: {
  placeholder: string;
  prompt: string;
  value?: string | null;
}) {
  return new Promise((resolve, reject) => {
    const { placeholder, prompt, value } = params;
    const inputBox = vscode.window.createInputBox();
    inputBox.placeholder = placeholder;
    inputBox.prompt = prompt;
    inputBox.value = value || "";
    inputBox.ignoreFocusOut = true;
    setTimeout(() => {
      inputBox.show();
    }, 100);
    inputBox.onDidAccept(async () => {
      if (inputBox) {
        inputBox.hide();
        resolve(inputBox.value.trim());
        return;
      }
      reject(false);
    });
  });
}

async function quickPick(
  placeHolder: string
): Promise<vscode.QuickPickItem | undefined> {
  const options: vscode.QuickPickItem[] = [
    { label: "Y", description: "Yes, I'm sure to deploy this smart contract" },
    {
      label: "N",
      description:
        "Skip the current smart contract deployment, because i have already deployed it, there is no need to deploy it again",
    },
  ];
  // 显示快速选择框
  const selectedOption = await vscode.window.showQuickPick(options, {
    placeHolder,
  });
  if (!selectedOption) {
    return Promise.reject({ message: "User Rejected" });
  }
  return selectedOption;
}

async function confirmDeploy(
  contractList: ContractItem[],
  dapp: string
): Promise<{
  cargs: string[];
  code: string[];
  names: string[];
  filepaths: string[];
  filenames: string[];
}> {
  const max = contractList.length;
  const code: string[] = [];
  const cargs: string[] = [];
  const names: string[] = [];
  const filepaths: string[] = [];
  const filenames: string[] = [];
  let i = 0;
  while (i < max) {
    const current = contractList[i];
    const { name, content, filename, fullPath, dependedBy } = current;
    const depondon = dependedBy ? `(depended upon by '${dependedBy})'` : "";

    const selected = await quickPick(`Confirm to deploy "${name}" ${depondon}`);
    const dirname = path.dirname(fullPath);
    const cache = new DeploymentArgsCache({ dirname, group: filename });
    const value = cache.get("deploy") ?? "";

    if (!selected || selected.label === "N") {
      i += 1;
      continue;
    }
    const arg = (await Inputbox({
      placeholder: `${name} parameters`,
      prompt:
        'Leave this blank if the contract has no parameters. Otherwise it must be json-formated. Let\'s assume that you have a contact function like \'function on_deploy(string a, string b, string c),\' then here you should input {"a": "hello", "b": "world", "c": "!"}',
      value,
    })) as string;
    code.push(content);
    cargs.push(arg || "");
    names.push(name);
    filepaths.push(fullPath);
    filenames.push(filename);
    i += 1;
    cache.set("dapp", dapp);
    cache.set("deploy", arg || "");
  }
  return { cargs, code, names, filepaths, filenames };
}

export default async (uri: vscode.Uri, context: vscode.ExtensionContext) => {
  try {
    if (outputChannel) {
      outputChannel.clear();
    } else {
      outputChannel = new Channel("Preda Deploy Script");
    }
    outputChannel.show();

    if (!wss) {
      wss = await new WSServer(outputChannel).create();
    }

    const { currentFileName, currentFilePath, currentFolder } =
      getCurrentActiveFileAndFolder(uri);

    // config cache
    const configPath = path.resolve(currentFolder, getConfigName());
    let configJson: any = {};
    if (existsSync(configPath)) {
      delete require.cache[require.resolve(configPath)];
      configJson = require(configPath);
    }

    const cache = new DeploymentArgsCache({
      group: currentFileName,
      dirname: currentFolder,
    });

    if (currentFileName.match(/\.prd$/)) {
      const dapp = (await Inputbox({
        placeholder: "DAPP",
        value: cache.get("dapp"),
        prompt:
          "Input the symbol of dapp, create it on https://dapps.dioxide.network/dapp if you haven't",
      })) as string;

      if (!dapp) {
        vscode.window.showErrorMessage("DApp symbol is required");
        return;
      }
      cache.set("dapp", dapp);
      const contractItems = await collectDependency(currentFilePath);

      const { cargs, code, names, filenames, filepaths } = await confirmDeploy(
        contractItems,
        dapp
      );

      outputChannel.append(`get base information from diox-chain`);
      const dioResp = await new Fetcher().getAverageGasPrice();
      const { Message, Result, Status } = dioResp;
      if (Status !== 0) {
        outputChannel.append(`DioScan service failed: ${dioResp}`);
        vscode.window.showErrorMessage(
          `DioScan service failed: ${Status}:${Message}`
        );
        return;
      }
      outputChannel.append(`DioScan service: ${JSON.stringify(dioResp)}`);
      const { AvgGasPrice } = Result;

      outputChannel.append(`start to compose transaction`);
      const payload = JSON.stringify({
        delegatee: dapp + ":dapp",
        function: "core.delegation.deploy_contracts",
        gasprice: AvgGasPrice,
        args: {
          code,
          cargs,
          time: 20,
        },
      });

      const log = new DeploymentArgsCache({
        dirname: currentFolder,
        group: "request",
      });

      log.set("tx.compose", payload);

      outputChannel.append(`about to deploy contracts to dapp: ${dapp}`);
      names.map((name, i) => {
        outputChannel.append(
          `about to deploy contract '${name}', args: ${JSON.stringify(
            cargs[i]
          )}`
        );
      });
      const response = await new Fetcher().composeDeployData(payload);
      const { err, rsp, ret } = response;

      if (err) {
        outputChannel.append(
          `compose transaction failed, err: ${err}, rsp: ${rsp}, ret: ${ret}`
        );
        vscode.window.showErrorMessage(
          `tx.deploy_compose failed, err: ${err}, rsp: ${rsp}, ret: ${ret}`
        );
        return;
      }

      outputChannel.append(
        `compose transaction successfully, rsp: ${rsp}, ret.TxData: ${ret.TxData} ret.GasOffered: ${ret.GasOffered}`
      );

      const { TxData, GasOffered } = ret;
      const taskId = wss.addTask({
        data: TxData,
        gasOffered: GasOffered,
        avgGas: AvgGasPrice,
        filenames: filenames,
        filepaths: filepaths,
        cname: names,
        dapp,
      });
      const host = getCoreDAppUrl();
      const url = `${host}/vscode?port=${wss.port}&taskid=${taskId}`;
      vscode.env.openExternal(vscode.Uri.parse(url));
      // Now wait vscode-plugin dapp handle this task
      // Give tranascation hash back via websocket messsage
    } else {
      vscode.window.showErrorMessage("Preda deploy: only deploy with prd file");
    }
  } catch (e: any) {
    if (e.message) {
      vscode.window.showErrorMessage(e.message);
      return;
    }
    vscode.window.showErrorMessage(e.toString());
  }
};
