import * as assert from "assert";

// You can import and use all API from the 'vscode' module
// as well as import your extension to test it
import * as vscode from "vscode";

suite("Extension Test Suite", () => {
  vscode.window.showInformationMessage("Start all tests.");

  test('Extension should be present', () => {
    assert.ok(vscode.extensions.getExtension('PREDADevTeam.preda'));
  });

  test('Preda should activate', function () {
    this.timeout(1 * 60 * 1000);
    return vscode.extensions.getExtension('PREDADevTeam.preda')?.activate().then((api) => {
      assert.ok(true);
    });
  });

  test('Register all preda commands', function () {
    return vscode.commands.getCommands(true).then((commands) => {
      const COMMANDS = [
        'Preda.run',
        'Preda.edit',
        'Preda.compile',
        'Preda.compileMultiple',
        'Preda.view',
      ];
      const filterPredaCommands = commands.filter((value) => {
        return COMMANDS.indexOf(value) >= 0 || value.startsWith('extension.preda.');
      });
      assert.equal(filterPredaCommands.length, COMMANDS.length);
    });
  });

});
