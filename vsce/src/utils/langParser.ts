import { ANTLRInputStream, CommonTokenStream } from 'antlr4ts';
import { PredaLexer } from '../languageServer/Lang/LangLexer';
import { IdentifierContext, PredaParser } from '../languageServer/Lang/LangParser';
import * as vscode from 'vscode';

const predaStrParser = (str: string) => {
  const inputStream = new ANTLRInputStream(str);
  const lexer = new PredaLexer(inputStream);
  const tokenStream = new CommonTokenStream(lexer);
  const parser = new PredaParser(tokenStream);
  return parser.predaSource();
};

export const getPostionByIdentifierContext = (identifier: IdentifierContext) => {
  const ctxIdentifierStart = identifier.start;
  const startLine = ctxIdentifierStart.line - 1;
  const charStartLine = ctxIdentifierStart.charPositionInLine;
  const startPostion = new vscode.Position(startLine, charStartLine);
  const endPostion = new vscode.Position(startLine, charStartLine + identifier.text.length);
  return { startPostion, endPostion };
}

export default predaStrParser;