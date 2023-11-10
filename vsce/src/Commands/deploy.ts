import * as vscode from "vscode";
import { existsSync, readFileSync } from "fs";
import Channel from "../utils/channel";
import { getConf, getCoreDAppUrl } from "../utils/configure";

import { getCurrentActiveFileAndFolder, getConfigName } from "../utils/finder";
import { WSServer } from "../wss";
import Fetcher from "../utils/webapi";

const path = require("path");

let wss: WSServer | null = null;
let outputChannel: Channel;

function Inputbox(placeholder: string, prompt: string) {
  return new Promise((resolve, reject) => {
    const inputBox = vscode.window.createInputBox();
    inputBox.placeholder = placeholder;
    inputBox.prompt = prompt;
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

    if (currentFileName.match(/\.prd$/)) {
      const dapp = (await Inputbox(
        "DAPP",
        "Input the symbol of dapp, create it on https://dapps.dioxide.network/dapp if you haven't"
      )) as string;

      if (!dapp) {
        vscode.window.showErrorMessage("DApp symbol is required");
        return;
      }
      const contract = readFileSync(currentFilePath, {
        encoding: "utf-8",
      });
      const contractName = contract.match(/(?<=contract)\s+\w+\b(?=.*\{)/);
      const cname = contractName ? contractName[0].trim() : "";
      const cargs: string = (await Inputbox(
        `${contractName}'s arguments`,
        'It must be json-formated, for example, if you have a contact function like \'function on_deploy(string a, string b, string c),\' then here you should input {"a": "hello", "b": "world", "c": "!"}'
      )) as string;

      const args = cargs.trim().length === 0 ? [""] : [cargs.trim()];

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
        sender: dapp + ":dapp",
        function: "core.delegation.deploy_contracts",
        gasprice: AvgGasPrice,
        args: {
          code: [contract],
          cargs: args,
          dapp,
          time: 20,
        },
      });

      outputChannel.append(`dapp: ${dapp}, cargs: ${JSON.stringify(args)}`);
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
        filename: currentFileName,
        filepath: currentFilePath,
        cname: cname.trim(),
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
