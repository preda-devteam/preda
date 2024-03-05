import * as vscode from "vscode";
import { existsSync } from "fs";

import {
  getCurrentActiveFileAndFolder,
  getChsimuFileFloder,
  getConfigName,
  transformCompileArg,
} from "../utils/finder";
import { exec } from "child_process";
import { spawn } from "../utils/process";
import { msg2output, msg2problems, getdiagnosticCollection } from "../utils/common";

const path = require("path");
let terminal: vscode.Terminal | undefined;
const isWin = process.platform === "win32";

let bashPath: string;
if (isWin) {
  function getBashPath(callback: (bashPath: string) => void) {
    exec(`echo %ComSpec%`, (error, stdout, stderr) => {
      if (error) {
        return;
      }
      callback(stdout.trim());
    });
  }
  getBashPath((defaultBashPath: string) => {
    bashPath = defaultBashPath;
  });
}

export default async (uri: vscode.Uri, context: vscode.ExtensionContext) => {
  try {
    vscode.commands.executeCommand('workbench.action.files.save');
    const { currentFileName, currentFilePath, currentFolder } =
      getCurrentActiveFileAndFolder(uri);

    // config cache
    const configPath = path.resolve(currentFolder, getConfigName());
    let configJson: any = {};
    if (existsSync(configPath)) {
      delete require.cache[require.resolve(configPath)];
      configJson = require(configPath);
    }
    const compileArgs = configJson[currentFileName]
      ? transformCompileArg(configJson[currentFileName], currentFolder)
      : "";

    if (currentFileName.match(/\.prd|\.sol-json/)) {
      const { chsimuFloder, chsimuName } = getChsimuFileFloder();
      const outputDirPath = path.resolve(currentFolder);
      const fname = currentFileName.split(".")[0];
      const outFilename = `${fname}_latest_compile`;
      const logPath = path.resolve(outputDirPath, outFilename + ".log");
      // Release the terminal to prevent stuck
      if (terminal) {
        terminal.dispose();
      }

      terminal = vscode.window.createTerminal({
        message: "Preda Compile",
        cwd: chsimuFloder,
        shellPath: bashPath,
      });
      // const isGitBash = (
      //   terminal.creationOptions as vscode.TerminalOptions
      // ).shellPath
      //   ?.toLowerCase()
      //   .match("git");
      // terminal.show();
      // terminal.sendText(
      //   `.${
      //     isWin && !isGitBash ? "\\" : "/"
      //   }${chsimuName} -log:${logPath} "${currentFilePath}" ${compileArgs} -stdout`
      // );
      const diagnosticCollection = getdiagnosticCollection();
      diagnosticCollection.clear();
      const disgnostics: {[file: string]: vscode.Diagnostic[]} = {};
      let msg = ''
      spawn({
        cmd: isWin ? chsimuName : "./" + chsimuName,
        option: { cwd: chsimuFloder, shell: true },
        args: [
          `"${currentFilePath}"`,
          `${compileArgs || ""}`,
          '-stdout',
        ],
        onData: (data) => {
          const message = data.toString();
          msg += message;
          msg2problems(message, disgnostics);
        },
        onErr () {},
        onExt () {
          msg2output(msg, 'Preda');
        }
      });
    } else {
      vscode.window.showErrorMessage("Preda Compile: only run with prd file");
    }
  } catch (e: any) {
    vscode.window.showErrorMessage(e.toString());
  }
};
