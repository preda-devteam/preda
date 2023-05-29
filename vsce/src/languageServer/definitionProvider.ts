import * as vscode from 'vscode';
import * as vscodeLang from 'vscode-languageserver';
import { PredaListener } from './Preda/PredaListener';
import { FunctionDeclarationContext, ImportDirectiveContext, ExpressionContext } from './Preda/PredaParser';
import { ParseTreeWalker } from 'antlr4ts/tree/ParseTreeWalker';
import { getCurrentActiveFileAndFolder, isWin } from '../utils/finder';
import { existsSync, readFileSync } from 'fs-extra';
import path = require('path');
import predaStrParser, { getPostionByIdentifierContext } from '../utils/predaParser';

const fileScheme = isWin ? 'file:\\\\' : 'file://';
class EnterFunctionListener implements PredaListener {
  // Assuming a parser rule with name: `enterFunctionDeclaration`
}
export class PredaDefinitionProvider implements vscode.DefinitionProvider {
  /**
     * Provide definition for cursor position in Solidity codebase. It calculate offset from cursor position and find the
     * most precise statement in solparse AST that surrounds the cursor. It then deduces the definition of the element based
     * on the statement type.
     *
     * @param {vscode.TextDocument} document
     * @param {vscode.Position} position
     * @returns {(Thenable<vscode.LocationLink[]>)}
     * @memberof PredaDefinitionProvider
     */
  public provideDefinition(
    document: vscode.TextDocument,
    position: vscode.Position,
  ): Thenable<vscode.LocationLink[]> {
      const documentText = document.getText();
      const currentContractUri = vscode.Uri.parse(`${fileScheme}${document.uri.fsPath}`);
      const wordRangePosition = document.getWordRangeAtPosition(position);
      const word = document.getText(wordRangePosition);
      const listener: PredaListener = new EnterFunctionListener();
      const { currentFolder } = getCurrentActiveFileAndFolder(document.uri);
      const globalImportMap = new Map();

      const promise = new Promise<vscode.LocationLink[]>((resolve) => {
        let importContractFnLocation: vscode.LocationLink[] = [];
        let currentContractFnLocation: vscode.LocationLink[] = [];
        // check ? import expression : expression
        listener.enterExpression = function (ctx: ExpressionContext) {
          // expressionType: 4 => expression . identifier
          // expressionType: 3 => expression '(' functionCallArguments ')'
          const parentNode = ctx.parent as ExpressionContext;
          if (ctx.text.match(word) && ctx.expressionType === 4 && parentNode && parentNode.expressionType === 3) {
            const [contractExpression] = ctx.expression();
            const targetTree = globalImportMap.get(contractExpression?.text);
            if(targetTree) {
              const filepath = path.resolve(currentFolder, contractExpression?.text + '.prd');
              if (!existsSync(filepath)) {
                return vscode.window.showErrorMessage(`${filepath} is not found`);
              }
              const targetContractUri = vscode.Uri.parse(fileScheme + filepath);
              const listener: PredaListener = new EnterFunctionListener();
              listener.enterFunctionDeclaration = function (ctx: FunctionDeclarationContext) { 
                // match function name
                const ctxIdentifier = ctx.identifier();
                if (ctxIdentifier.text === word) {
                  const { startPostion, endPostion } = getPostionByIdentifierContext(ctxIdentifier);
                  importContractFnLocation.push({
                    targetUri: targetContractUri,
                    targetRange: vscodeLang.Range.create(startPostion, endPostion) as vscode.Range
                  });
                }
              };
              // dfs with walker
              ParseTreeWalker.DEFAULT.walk(listener, targetTree);
            }
          }
        };
        // cache importDirective
        listener.enterImportDirective = async function (ctx: ImportDirectiveContext) {
          const [ctxContract, ctxFunction] = ctx.identifier();
          const filepath = path.resolve(currentFolder, ctxContract.text + '.prd');
          
          if (existsSync(filepath)) {
            const importDocumentText = readFileSync(filepath)
            const tree = predaStrParser(importDocumentText.toString());
            // set tree to import map for expression finder
            globalImportMap.set(ctxContract.text, tree);
          }
          // todo ctx.AsKeyword()
        };
        // find function location
        listener.enterFunctionDeclaration = function (ctx: FunctionDeclarationContext) { 
          // match function name
          const ctxIdentifier = ctx.identifier();
          if (ctxIdentifier.text === word) {
            const { startPostion, endPostion } = getPostionByIdentifierContext(ctxIdentifier);
            currentContractFnLocation.push({
              targetUri: currentContractUri,
              targetRange: vscodeLang.Range.create(startPostion, endPostion) as vscode.Range
            });
          }
        };
        // dfs end
        listener.exitPredaSource = () => {
          if (importContractFnLocation.length) {
            resolve(importContractFnLocation);
          } else {
            resolve(currentContractFnLocation);
          }
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