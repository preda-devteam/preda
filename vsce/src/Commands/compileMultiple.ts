import * as vscode from "vscode";
import { existsSync, writeFileSync } from "fs";

import {
  getCurrentActiveFileAndFolder,
  getChsimuFileFloder,
  getConfigName,
  transformCompileArg
} from "../utils/finder";
import { getdiagnosticCollection, msg2output, msg2problems } from "../utils/common";
import { spawn } from "../utils/process";

const path = require("path");
let terminal: vscode.Terminal | undefined;
const isWin = process.platform === "win32";

export default async (uri: vscode.Uri, context: vscode.ExtensionContext) => {
  try {
    vscode.commands.executeCommand('workbench.action.files.save');
    const { currentFolder, currentFileName, currentFilePath } =
      getCurrentActiveFileAndFolder(uri);

    async function getConfig (): Promise<string> {
      return new Promise((resolve, reject) => {
        const configPath = path.resolve(currentFolder, getConfigName());
        let configJson: any = {};
        if (existsSync(configPath)) {
          delete require.cache[require.resolve(configPath)];
          configJson = require(configPath);
        }
        // Get the parameter of the user input
        const inputBox = vscode.window.createInputBox();
        inputBox.placeholder = "compile arguments";
        inputBox.prompt = "set dependent contracts for compilation or other compile arguments. e.g: ./IERC20.prd,./IERC721.prd";
        inputBox.value = configJson[currentFileName] || "";
        inputBox.ignoreFocusOut = true;
        inputBox.show();
        inputBox.onDidAccept(async () => {
          if (inputBox && inputBox.value) {
            configJson[currentFileName] = inputBox.value;
          } else {
            configJson[currentFileName] = "";
          }
          // close input
          inputBox.hide();
          resolve(configJson[currentFileName]);
          writeFileSync(configPath, JSON.stringify(configJson, null, 2));
        });
      });
    }

    if (currentFileName.match(/\.prd|\.sol-json/)) {
      const { chsimuFloder, chsimuName } = getChsimuFileFloder();
      // config cache
      const configCache = await getConfig();

      // Release the terminal to prevent stuck
      if (terminal) {
        terminal.dispose();
      }

      // terminal = vscode.window.createTerminal({
      //   message: "Preda Compile With Arguments",
      //   cwd: chsimuFloder,
      // });
      // terminal.show();
      // terminal.sendText(
      //   `.${isWin ? "\\" : "/"}${chsimuName} -log "${currentFilePath}" ${transformCompileArg(configCache, currentFolder)} -stdout`
      // );
      const diagnosticCollection = getdiagnosticCollection();
      diagnosticCollection.clear();
      const disgnostics: {[file: string]: vscode.Diagnostic[]} = {};
      let msg = '';
      spawn({
        cmd: isWin ? chsimuName : "./" + chsimuName,
        option: { cwd: chsimuFloder, shell: true },
        args: [
          `"${currentFilePath}"`,
          `${transformCompileArg(configCache, currentFolder)}`,
          '-stdout',
        ],
        onData: (data) => {
          const message = data.toString();
          msg += message;
          msg2problems(message,disgnostics);
        },
        onErr () {},
        onExt () {
          msg2output(msg, 'Preda');
        }
      });
    } else {
      vscode.window.showErrorMessage("Preda Compile With Arguments: only run with prd file");
    }
  } catch (e: any) {
    vscode.window.showErrorMessage(e.toString());
  }
};
