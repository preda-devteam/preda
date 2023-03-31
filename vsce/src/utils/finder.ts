import * as vscode from "vscode";
import { existsSync } from "fs-extra";

const path = require("path");
export const isWin = process.platform === "win32";

export const getCurrentActiveFileAndFolder = (uri?: vscode.Uri) => {
  // the path of the folder
  let currentFilePath = uri?.fsPath;
  // command line to get the current TAB path
  if (!currentFilePath) {
    currentFilePath =
      vscode.window?.activeTextEditor?.document.uri.fsPath || "";
  }
  const lastStr = currentFilePath.lastIndexOf(isWin ? "\\" : "/") + 1;
  const currentFileName = currentFilePath.substring(lastStr);
  const currentFolder = currentFilePath.substring(0, lastStr);
  return {
    currentFileName,
    currentFolder,
    currentFilePath,
  };
};

export const getPathFloderAndName = (path: string) => {
  const lastStr = path.lastIndexOf(isWin ? "\\" : "/") + 1;
  const fileName = path.substring(lastStr);
  const fileFloder = path.substring(0, lastStr);
  return {
    fileName,
    fileFloder,
  };
};

export const getChsimuFileFloder = () => {
  // get Chsimu path
  const chsimuPath = vscode.workspace
    .getConfiguration("Preda")
    .get("path") as string;

  if (!chsimuPath) {
    const errorText = "settings.preda.path is unset ";
    vscode.window.showErrorMessage(errorText);
    throw new Error(errorText);
  }

  if (!existsSync(chsimuPath)) {
    const errorText =
      "The executable program(" + chsimuPath + ") doesn't exist";
    vscode.window.showErrorMessage(errorText);
    throw new Error(errorText);
  }

  const { fileName: chsimuName, fileFloder: chsimuFloder } =
    getPathFloderAndName(chsimuPath);

  return { chsimuName, chsimuFloder };
};

export function findTSByPrdName(uri: vscode.Uri) {
  const fileContext = getCurrentActiveFileAndFolder(uri);
  const { currentFolder } = fileContext;
  let { currentFileName, currentFilePath } = fileContext;

  if (currentFileName.endsWith(".prd")) {
    currentFileName = currentFileName.replace(".prd", ".prdts");
    currentFilePath = currentFilePath.replace(".prd", ".prdts");
  }

  return {
    currentFileName,
    currentFilePath,
    currentFolder,
    exist: existsSync(currentFilePath),
  };
}

export function transformCompileArg (pathStr: string, currentFolder: string): string {
  if (!pathStr) {return '';}
  let result = '';
  const pathArr = pathStr.split(',');
  pathArr.forEach((p, index) => {
    const isFilePath = p.match(/(\.prd|\.sol-json)$/);
    if (isFilePath) {
      result += `"${path.resolve(currentFolder, p)}"`;
    } else {
      result += p;
    }
    if (index < pathArr.length - 1) {
      result += ' ';
    }
  });
  return result;
}

export function getConfigName () {
  return 'scriptArgs.json';
}
