import * as vscode from "vscode";
import path = require("path");
import { existsSync } from "fs";

import {
  getCurrentActiveFileAndFolder,
  findTSByName,
  getConfigName
} from "../utils/finder";
import { outputToChannel } from "../utils/chsimu";

export default async (uri: vscode.Uri, context: vscode.ExtensionContext) => {
  try {
    vscode.commands.executeCommand('workbench.action.files.save');
    console.log('run', context)
    const fileContext = getCurrentActiveFileAndFolder(uri);
    const { currentFolder } = fileContext;
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

      const contractScriptArg = configJson[currentFileName] || "";

      try {
        await outputToChannel({
          context,
          currentFileName,
          currentFolder,
          contractScriptArg,
          currentFilePath,
        });
      } catch (ex: any) {
        vscode.window.showErrorMessage(ex.message);
      }
    } else {
      vscode.window.showErrorMessage(
        "Run Chain Simulator: only run with prd(ts) file"
      );
    }
  } catch (e: any) {
    vscode.window.showErrorMessage(e.toString());
  }
};
