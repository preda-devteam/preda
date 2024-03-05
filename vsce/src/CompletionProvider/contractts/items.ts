import * as vscode from "vscode";

interface Complation {
  match: RegExp;
  items: vscode.CompletionItem[];
}

const completaionItems: Complation[] = [
  {
    match: /\bchain\.$/,
    items: [
      new vscode.CompletionItem("info", vscode.CompletionItemKind.Method),
      new vscode.CompletionItem("run", vscode.CompletionItemKind.Method),
      new vscode.CompletionItem("deploy", vscode.CompletionItemKind.Method),
      new vscode.CompletionItem("gaslimit", vscode.CompletionItemKind.Method),
    ],
  },
  {
    match: /\blog\.$/,
    items: [
      new vscode.CompletionItem("highlight", vscode.CompletionItemKind.Method),
      // new vscode.CompletionItem("warning", vscode.CompletionItemKind.Method),
      // new vscode.CompletionItem("error", vscode.CompletionItemKind.Method),
    ],
  },
  {
    match: /\bviz\.$/,
    items: [
      new vscode.CompletionItem("block", vscode.CompletionItemKind.Method),
      new vscode.CompletionItem("shard", vscode.CompletionItemKind.Method),
      new vscode.CompletionItem("txn", vscode.CompletionItemKind.Method),
      new vscode.CompletionItem("addr", vscode.CompletionItemKind.Method),
      new vscode.CompletionItem("section", vscode.CompletionItemKind.Method),
      new vscode.CompletionItem("trace", vscode.CompletionItemKind.Method),
      new vscode.CompletionItem("profiling", vscode.CompletionItemKind.Method),
    ],
  },
  {
    match: /\bstopwatch\.$/,
    items: [
      new vscode.CompletionItem("report", vscode.CompletionItemKind.Method),
      new vscode.CompletionItem("restart", vscode.CompletionItemKind.Function),
    ],
  },
  {
    match: /\brandom\.$/,
    items: [
      new vscode.CompletionItem("reseed", vscode.CompletionItemKind.Method),
    ],
  },
  {
    match: /\ballocate\.$/,
    items: [
      new vscode.CompletionItem("address", vscode.CompletionItemKind.Method),
    ],
  },
  {
    match: /\s@$/,
    items: [
      new vscode.CompletionItem("all", vscode.CompletionItemKind.Variable),
      new vscode.CompletionItem("random", vscode.CompletionItemKind.Variable),
      new vscode.CompletionItem("global", vscode.CompletionItemKind.Variable),
      new vscode.CompletionItem("shard", vscode.CompletionItemKind.Variable),
      new vscode.CompletionItem("0", vscode.CompletionItemKind.Variable),
    ],
  },
];

export default completaionItems;
