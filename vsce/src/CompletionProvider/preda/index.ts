// https://code.visualstudio.com/api/language-extensions/programmatic-language-features#show-code-completion-proposals
import * as vscode from "vscode";
import Provider from "../provider";
import completations from "./items";

class PredaCompletationProvider extends Provider {
  constructor() {
    super(completations);
  }
}

export default vscode.languages.registerCompletionItemProvider(
  "preda",
  new PredaCompletationProvider(),
  "."
);
