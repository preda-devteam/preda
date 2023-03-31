import * as assert from "assert";
import path = require("path");

// You can import and use all API from the 'vscode' module
// as well as import your extension to test it
import * as vscode from "vscode";
import run from "../../src/Commands/run";
import { examplePrdFileName, testWorkspace } from "../utils";

suite("Command Test Suite", () => {
  
  test('Test command run', async function (): Promise<string> {
    this.timeout(1000);
    const exampleFilePath = path.resolve(testWorkspace, examplePrdFileName);
    const Uri = vscode.Uri.file(exampleFilePath);
    await vscode.commands.executeCommand('Preda.run', Uri);

    return new Promise((res) => {
        setInterval(async () => {
          const t = vscode.workspace.textDocuments;
          // use this to match outputchannel
          if (t && t[0].fileName.match('Preda')) {
            res('ok');
          }
        }, 300);
      });
    });
});