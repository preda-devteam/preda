import * as vscode from "vscode";
import { existsSync } from "fs";

import {
  getCurrentActiveFileAndFolder,
  getChsimuFileFloder,
  getConfigName,
  transformCompileArg
} from "../utils/finder";

const path = require('path');
let terminal: vscode.Terminal | undefined;
const isWin = process.platform === "win32";

export default async (uri: vscode.Uri, context: vscode.ExtensionContext) => {
  try {
    const { currentFileName, currentFilePath, currentFolder } =
      getCurrentActiveFileAndFolder(uri);
    
    // config cache
    const configPath = path.resolve(currentFolder, getConfigName());
    let configJson: any = {};
    if (existsSync(configPath)) {
      delete require.cache[require.resolve(configPath)];
      configJson = require(configPath);
    }
    const compileArgs = configJson[currentFileName] ? transformCompileArg(configJson[currentFileName], currentFolder) : '';

    if (currentFileName.match(/\.prd|\.sol-json/)) {
      const { chsimuFloder, chsimuName } = getChsimuFileFloder();

      // Release the terminal to prevent stuck
      if (terminal) {
        terminal.dispose();
      }

      terminal = vscode.window.createTerminal({
        message: "Preda Compile",
        cwd: chsimuFloder,
      });
      terminal.show();
      terminal.sendText(
        `.${isWin ? "\\" : "/"}${chsimuName} -log "${currentFilePath}" ${compileArgs} -stdout`
      );
    } else {
      vscode.window.showErrorMessage("Preda Compile: only run with prd file");
    }
  } catch (e: any) {
    vscode.window.showErrorMessage(e.toString());
  }
};
