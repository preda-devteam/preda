import * as vscode from "vscode";

import ViewLoader from "../viewloader";

export default async (uri: vscode.Uri, context: vscode.ExtensionContext) => {
  try {
    const webview = new ViewLoader({ context, filepath: uri.fsPath });
    webview.create();
  } catch (e: any) {
    vscode.window.showErrorMessage(e.toString());
  }
};
