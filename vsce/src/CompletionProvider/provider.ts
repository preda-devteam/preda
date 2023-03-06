// https://code.visualstudio.com/api/language-extensions/programmatic-language-features#show-code-completion-proposals

import * as vscode from "vscode";

export interface CompletationItems {
  match: RegExp;
  items: vscode.CompletionItem[];
}

export default class Provider implements vscode.CompletionItemProvider {
  items: CompletationItems[];

  constructor(items: CompletationItems[]) {
    this.items = items;
  }

  provideCompletionItems(
    document: vscode.TextDocument,
    position: vscode.Position
  ) {
    const linePrefix = document
      .lineAt(position)
      .text.substr(0, position.character);

    for (let i = 0; i < this.items.length; i++) {
      const provider = this.items[i];
      if (provider.match.test(linePrefix)) {
        return provider.items;
      }
    }
    return [];
  }
}
