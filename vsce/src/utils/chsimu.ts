import * as vscode from "vscode";
import * as path from "path";

import { spawn } from "./process";
import { formatTime } from "./time";
import ViewLoader from "../viewloader";
import FileHandler from "./filehandler";
import { getChsimuFileFloder } from "./finder";

const isWin = process.platform === "win32";
let outputChannel: vscode.OutputChannel;

// export const getOutputPath = () => {
//   const chsimuConf = vscode.workspace.getConfiguration("Preda");
//   return chsimuConf.get<string>("output");
// };

interface OutputParams {
  currentFilePath: string;
  currentFolder: string;
  currentFileName: string;
  contractScriptArg: string;
  channel?: string;
  context: vscode.ExtensionContext;
}

export async function outputToChannel(params: OutputParams) {
  const {
    currentFilePath,
    contractScriptArg,
    currentFolder,
    currentFileName,
    context,
    channel = "Preda",
  } = params;

  const extesionPath = context.extensionPath;
  const { chsimuFloder, chsimuName } = getChsimuFileFloder();
  const uiTemp = path.resolve(extesionPath, "out/web/index.html");
  const fname = currentFileName.split(".")[0];
  const outFilename = `${fname}_latest_run`;

  const outputDirPath = path.resolve(currentFolder);
  const outFilePath = path.resolve(outputDirPath, outFilename + ".html");
  const logPath = path.resolve(outputDirPath, outFilename + ".log");

  if (outputChannel) {
    outputChannel.clear();
  } else {
    outputChannel = vscode.window.createOutputChannel(channel);
  }

  const args = [
    `"${currentFilePath}"`,
    `${contractScriptArg || ""}`,
    '-stdout',
    `-viz_templ:"${uiTemp}"`,
    `-viz:"${outFilePath}"`,
    `-log:"${logPath}"`,
  ];
  const invokeMsg = `[${formatTime(
    Date.now(),
    "YYYY-MM-DD HH:mm:ss"
  )}] ${chsimuName} ${args.join(" ")}`;

  outputChannel.show();
  outputChannel.appendLine(invokeMsg);
  spawn({
    cmd: isWin ? chsimuName : "./" + chsimuName,
    option: { cwd: chsimuFloder, shell: true },
    args,
    onData: (data) => {
      const message = data.toString();
      outputChannel.append(message);
    },
    onErr: (err) => {
      outputChannel.appendLine(`${err.toString()}`);
    },
    onExt: (code) => {
      outputChannel.show();

      if (code === 0) {
        outputChannel.appendLine(`Result will output to "${outFilePath}"`);
        outputChannel.appendLine("");
        const file = new FileHandler({
          filepath: outFilePath,
        });
        file
          .inject({
            args: contractScriptArg,
            contract: currentFileName,
            staticPath: "{{staticPath}}",
            title: outFilename,
          })
          .then(() => {
            const view = new ViewLoader({ context, filepath: outFilePath });
            view.create();
          })
          .catch((ex) => {
            vscode.window.showErrorMessage(ex.message);
          });
        return;
      }
      outputChannel.appendLine(`[Failed] exit code: ${code}`);
    },
  });
}
