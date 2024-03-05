import * as vscode from 'vscode';
import { getCurrentActiveFileAndFolder, isWin } from '../utils/finder';
import { PredaListener } from './Lang/LangListener';
import { ParseTreeWalker } from 'antlr4ts/tree/ParseTreeWalker';
import { ExpressionContext } from './Lang/LangParser';
import path = require('path');
import predaStrParser from '../utils/langParser';

const fileScheme = isWin ? 'file:\\\\' : 'file://';
class EnterFunctionListener implements PredaListener {
  // Assuming a parser rule with name: `enterFunctionDeclaration`
}
export default class ReferenceProvider implements vscode.ReferenceProvider {
  public provideReferences(document: vscode.TextDocument, position: vscode.Position, options: { includeDeclaration: boolean }, token: vscode.CancellationToken): Thenable<vscode.Location[]> {
		return vscode.workspace.saveAll(false).then(() => {
			return this.doFindReferences(document, position, options, token);
		});
	}

	private doFindReferences(document: vscode.TextDocument, position: vscode.Position, options: { includeDeclaration: boolean }, token: vscode.CancellationToken): Thenable<vscode.Location[]> {
    const documentText = document.getText();
    const currentContractUri = vscode.Uri.parse(`${fileScheme}${document.uri.fsPath}`);
    const wordRangePosition = document.getWordRangeAtPosition(position);
    const word = document.getText(wordRangePosition);
    const listener: PredaListener = new EnterFunctionListener();
    const { currentFolder } = getCurrentActiveFileAndFolder(document.uri);
    const globalImportMap = new Map();

    const promise = new Promise<vscode.Location[]>((resolve) => {
      let currentContractFnLocation: vscode.Location[] = [];
      listener.enterExpression = function (ctx: ExpressionContext) {
        if (ctx.text === word) {
          const varRange = new vscode.Range(ctx.start.line - 1, ctx.start.charPositionInLine, (ctx.stop || ctx.start).line - 1, ctx.start.charPositionInLine + word.length);
          const location = new vscode.Location(currentContractUri, varRange);
          currentContractFnLocation.push(location);
          console.log(location, ctx);
        }
      };
      listener.exitPredaSource = () => {
          resolve(currentContractFnLocation);
      };
    });
    
    try {
      const tree = predaStrParser(documentText);
      // dfs with walker
      ParseTreeWalker.DEFAULT.walk(listener, tree);
    } catch (err) {
      console.log(err);
    }

    return promise;
	}
}