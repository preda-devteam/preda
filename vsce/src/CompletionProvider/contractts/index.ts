// https://code.visualstudio.com/api/language-extensions/programmatic-language-features#show-code-completion-proposals
import * as vscode from "vscode";
import Provider from "../provider";
import completations from "./items";

class CompletationProvider extends Provider {
  constructor() {
    super(completations);
  }
}

export default vscode.languages.registerCompletionItemProvider(
  "prdts",
  new CompletationProvider(),
  ".",
  "@"
);
