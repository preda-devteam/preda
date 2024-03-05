import * as assert from "assert";

// You can import and use all API from the 'vscode' module
// as well as import your extension to test it
import * as vscode from "vscode";
import {
  isWin,
  getCurrentActiveFileAndFolder,
  getPathFloderAndName,
  getChsimuFileFloder,
  transformCompileArg,
  getConfigName,
  findTSByName
} from '../../src/utils/finder';
import { padStart, formatTime } from '../../src/utils/time'
import path = require('path');
import { examplePrdFileName, testWorkspace } from "../utils";

suite("Uitls.finder Test Suite", () => {
  
  test('Test getCurrentActiveFileAndFolder|findTSByName function', async () => {
    const exampleFilePath = path.resolve(testWorkspace, examplePrdFileName)
    const Uri = vscode.Uri.file(exampleFilePath);
    await vscode.commands.executeCommand<vscode.TextDocumentShowOptions>("vscode.open",Uri);
    const {
      currentFileName,
      currentFilePath
    } = getCurrentActiveFileAndFolder();
    const {
      currentFileName: tsFileName,
      currentFilePath: tsFilePath
    } = findTSByName(Uri);

    // getCurrentActiveFileAndFolder
    assert.equal(currentFileName, examplePrdFileName);
    assert.equal(currentFilePath, exampleFilePath);

    // findTSByName
    assert.equal(tsFileName, examplePrdFileName + 'ts');
    assert.equal(tsFilePath, exampleFilePath + 'ts');


  });

  test('Test getPathFloderAndName function', () => {
    const {
      fileName,
      fileFloder,
    } = getPathFloderAndName(isWin ? '.\\constracts\\constract.prd' : './constracts/constract.prd');
    assert.equal(fileName, 'constract.prd');
    assert.equal(fileFloder, isWin ? '.\\constracts\\' : './constracts/');
  });

  test('Test transformCompileArg function', () => {
    assert.equal(transformCompileArg('./constract.prd,-WASM', '/constract/'), '"/constract/constract.prd" -WASM');
  });

  test('Test getConfigName function', () => {
    assert.equal(getConfigName(), 'scriptArgs.json');
  });

  test('Test getChsimuFileFloder function', () => {
    const {
      chsimuFloder,
      chsimuName
    } = getChsimuFileFloder();
    assert.equal(chsimuName, 'chsimu');
    assert.equal(chsimuFloder, '/Applications/PREDA/bin/');
  });



});

suite("Uitls.time Test Suite", () => {

  test('Test padStart function', () => {
    const padStartStr = padStart(1);
    assert.equal(padStartStr, '01');
  });

  test('Test formatTime function', () => {
    const formatTimeStr = formatTime(1672502400000);
    assert.equal(formatTimeStr, '2023-01-01');
  });
});