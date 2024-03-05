import * as vscode from "vscode";

const diagnosticCollection = vscode.languages.createDiagnosticCollection('preda');
export const getdiagnosticCollection = () => diagnosticCollection;
let outputChannel: vscode.OutputChannel;
export const msg2problems = (message: string, disgnostics: {[file: string]: vscode.Diagnostic[]}) => {

  if (message.match(': compile error')) {
    let errors = message.match(/(\S+): compile error(.)*/g);
    
    if (errors) {
      errors.forEach(e => {
        const [file, error] = e.split(': compile error');
        const [errorType, errorMsg] = error.match(': syntax error: ') ? error.split(': syntax error: ') : error.split(': ');
        const [fileName, rowcolumn ] = file.split('.prd:');
        const [row, column] = rowcolumn.split(':') || [0, 0];
        const range = new vscode.Range(+row-1, +column, +row-1, +column);
        const diagnostic = new vscode.Diagnostic(range, errorMsg, vscode.DiagnosticSeverity.Error);

        if (!disgnostics[fileName]) {
          disgnostics[fileName] = [diagnostic];
        } else {
          disgnostics[fileName].push(diagnostic);
        }
      });
      Object.keys(disgnostics).forEach(fileName => {
        const filePath = vscode.Uri.file(fileName + '.prd');
        diagnosticCollection.set(filePath, disgnostics[fileName]);
      });
    }
  }
}

export const msg2output = (message: string, channel: string) => {
  if (outputChannel) {
    outputChannel.clear();
  } else {
    outputChannel = vscode.window.createOutputChannel(channel);
  }
  const compileContent = message.match(/\[PRD\]([\s\S]+)(?=\[PRD)/g)
  if (compileContent) {
    compileContent.forEach(cc => {
      const msg = cc.split('\n');
      msg.shift();
      msg.forEach(m => {
        outputChannel.appendLine(m);
      });
    });
    outputChannel.show();
  }
}