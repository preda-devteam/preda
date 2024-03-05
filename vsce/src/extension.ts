// The module 'vscode' contains the VS Code extensibility API
// Import the module and reference it with the alias vscode in your code below
import * as vscode from "vscode";

import completationProvider from "./CompletionProvider/contractts";
import CompletationProvider from "./CompletionProvider/contract";
import run from "./Commands/run";
import editArgs from "./Commands/edit";
import compile from "./Commands/compile";
import deploy from "./Commands/deploy";
import compileMultiple from "./Commands/compileMultiple";
import view from "./Commands/view";
import DefinitionProvider from "./languageServer/definitionProvider";
import ReferenceProvider from "./languageServer/referenceProvider";

// this method is called when your extension is activated
// your extension is activated the very first time the command is executed
export function activate(context: vscode.ExtensionContext) {
  // Use the console to output diagnostic information (console.log) and errors (console.error)
  // This line of code will only be executed once when your extension is activated

  // run
  const runChsimuCommand = vscode.commands.registerCommand(
    "Preda.run",
    (uri: vscode.Uri) => run(uri, context)
  );

  // edit
  const editChsimuCommand = vscode.commands.registerCommand(
    "Preda.edit",
    (uri: vscode.Uri) => editArgs(uri, context)
  );

  // compile
  const compileChsimuCommand = vscode.commands.registerCommand(
    "Preda.compile",
    (uri: vscode.Uri) => compile(uri, context)
  );

  // compile multiple
  const compileMultipleChsimuCommand = vscode.commands.registerCommand(
    "Preda.compileMultiple",
    (uri: vscode.Uri) => compileMultiple(uri, context)
  );

  const viewHtmlCommand = vscode.commands.registerCommand(
    "Preda.view",
    (uri: vscode.Uri) => view(uri, context)
  );

  // deploy
  const deployCommand = vscode.commands.registerCommand(
    "Preda.deploy",
    (uri: vscode.Uri) => deploy(uri, context)
  );

  // Register to the monitoring queue
  context.subscriptions.push(runChsimuCommand);
  context.subscriptions.push(editChsimuCommand);
  context.subscriptions.push(compileChsimuCommand);
  context.subscriptions.push(compileMultipleChsimuCommand);
  context.subscriptions.push(viewHtmlCommand);
  context.subscriptions.push(completationProvider);
  context.subscriptions.push(CompletationProvider);
  context.subscriptions.push(deployCommand);

  let timeout: any = null;
  let activeEditor = vscode.window.activeTextEditor;
  let decorationTypes: { [key: string]: vscode.TextEditorDecorationType };
  let pattern: any;
  let styleForRegExp: any;

  const keywordsPattern = "\\[HIGHLIGHT\\].*";

  init();

  if (activeEditor) {
    triggerUpdateDecorations();
  }

  vscode.window.onDidChangeActiveTextEditor(
    function (editor) {
      activeEditor = editor;
      if (editor) {
        triggerUpdateDecorations();
      }
    },
    null,
    context.subscriptions
  );

  // An event that is emitted when a text document is changed.
  // This usually happens when the contents changes but also when other things like the dirty-state changes
  vscode.workspace.onDidChangeTextDocument(
    function (event: vscode.TextDocumentChangeEvent) {
      if (activeEditor && event.document === activeEditor.document) {
        triggerUpdateDecorations();
      }
    },
    null,
    context.subscriptions
  );

  // An event that is emitted when the configuration changed.
  vscode.workspace.onDidChangeConfiguration(
    function () {
      init();
      triggerUpdateDecorations();
    },
    null,
    context.subscriptions
  );

  function updateDecorations() {
    if (!activeEditor || !activeEditor.document) {
      return;
    }

    const text = activeEditor.document.getText();
    const matches: any = {};
    let match: RegExpExecArray | null;

    while ((match = pattern.exec(text))) {
      const startPos = activeEditor.document.positionAt(match.index);
      const endPos = activeEditor.document.positionAt(
        match.index + match[0].length
      );

      let decoration = {
        range: new vscode.Range(startPos, endPos),
      };

      let matchedValue = match[0];
      let patternIndex = match.slice(1).indexOf(matchedValue);
      matchedValue = Object.keys(decorationTypes)[patternIndex] || matchedValue;

      if (matches[matchedValue]) {
        matches[matchedValue].push(decoration);
      } else {
        matches[matchedValue] = [decoration];
      }

      if (keywordsPattern.trim() && !decorationTypes[matchedValue]) {
        decorationTypes[matchedValue] =
          vscode.window.createTextEditorDecorationType(styleForRegExp);
      }
    }

    Object.keys(decorationTypes).forEach((v) => {
      const rangeOption = matches[v] ? matches[v] : [];
      const decorationType = decorationTypes[v];
      activeEditor?.setDecorations(decorationType, rangeOption);
    });
  }

  function init() {
    decorationTypes = {};
    const style = {
      color: "#000",
      backgroundColor: "#ffff00",
    };
    styleForRegExp = Object.assign({}, style, {
      overviewRulerLane: vscode.OverviewRulerLane.Right,
    });
    pattern = new RegExp(keywordsPattern, "gi");
  }

  function triggerUpdateDecorations() {
    timeout && clearTimeout(timeout);
    timeout = setTimeout(updateDecorations, 0);
  }
  // defind language
  // if (vscode.workspace.workspaceFolders) {
    // Push the disposable to the context's subscriptions so that the
    // client can be deactivated on extension deactivation
    context.subscriptions.push(
      vscode.languages.registerReferenceProvider(
        { language: "preda", scheme: "file" },
        new ReferenceProvider()
      )
    );
    context.subscriptions.push(
      vscode.languages.registerDefinitionProvider(
        { language: "preda", scheme: "file" },
        new DefinitionProvider()
      )
    );
  // }
}

export function deactivate() {}
