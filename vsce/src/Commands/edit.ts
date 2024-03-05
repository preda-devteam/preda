import * as vscode from "vscode";
import path = require("path");
import { existsSync, writeFileSync } from "fs";

import {
  getCurrentActiveFileAndFolder,
  findTSByName,
  getConfigName
} from "../utils/finder";
import { outputToChannel } from "../utils/chsimu";

export default async (uri: vscode.Uri, context: vscode.ExtensionContext) => {
  try {
    vscode.commands.executeCommand('workbench.action.files.save');
    const { currentFolder } = getCurrentActiveFileAndFolder(uri);
    let { currentFileName, currentFilePath, exist } = findTSByName(uri);

    if (!exist) {
      vscode.window.showErrorMessage(`./${currentFileName} not exist`);
      return;
    }

    if (currentFileName.match(/\.prdts|\.prd/)) {
      const configPath = path.resolve(currentFolder, getConfigName());
      let configJson: any = {};
      if (existsSync(configPath)) {
        delete require.cache[require.resolve(configPath)];
        configJson = require(configPath);
      }

      // Get the parameter of the user input
      const inputBox = vscode.window.createInputBox();
      inputBox.placeholder = "contract script args";
      inputBox.prompt = "run contract with script args. e.g.: -count:1000";
      inputBox.value = configJson[currentFileName] || "";
      inputBox.ignoreFocusOut = true;
      inputBox.show();
      inputBox.onDidAccept(async () => {
        if (inputBox) {
          const contractScriptArg = inputBox.value;
          configJson[currentFileName] = contractScriptArg;
          writeFileSync(configPath, JSON.stringify(configJson, null, 2));
          // close input
          inputBox.hide();
          try {
            await outputToChannel({
              context,
              currentFileName,
              currentFilePath,
              currentFolder,
              contractScriptArg,
            });
          } catch (ex: any) {
            vscode.window.showErrorMessage(ex.message);
          }

          
        }
      });
    } else {
      vscode.window.showErrorMessage(
        "Run Chain Simulator: only run with script file"
      );
    }
  } catch (e: any) {
    vscode.window.showErrorMessage(e.toString());
  }
};
