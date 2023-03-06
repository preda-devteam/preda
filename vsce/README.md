# PREDA Language Preview Toolchain

This is a local toolchain for the PREDA smart contract programming language. PREDA is designed for parallel execution of smart contract transactions on sharding blockchains. The PREDA language preview toolchain includes the pre-built PREDA compilers and execution engines, VSCode extensions, and sample smart contracts and execution scripts. Programmers can use VSCode to edit, compile, and execute PREDA smart contracts in a local blockchain simulator and check the execution results, e.g., address states on the chain.

## Installation
requires node v12.17.0 or higher for ES2015 and async function support.

```
$ npm install -g @vscode/vsce
```

## Usages

- To compile PREDA smart contract (.prd):

  - use shortcut `Ctrl+5` / `Command + 7`
  - or right click the Text Editor and then click `PREDA: Compile` in editor context menu
  - or click `PREDA: Compile` button in context menu of file explorer
    ![Alt text](https://github.com/preda-devteam/preda/blob/main/vsce/resource/images/compile.png?raw=true "Compile")

- To set arguments for PREDA script (.prdts):

  - use shortcut `Ctrl+6` / `Command + 6`
  - or right click the Text Editor and then click `PREDA: Set Args` in editor context menu
  - or click `PREDA: Set Args` button in context menu of file explorer
  - the arguments will be stored in a local file `scriptArgs.json` and be reused for further execution
    ![Alt text](https://github.com/preda-devteam/preda/blob/main/vsce/resource/images/edit.png?raw=true "Set Args")

- To run PREDA script (.prdts):

  - use shortcut `Ctrl+5` / `Command + 5`
  - or right click the Text Editor and then click `PREDA: Run` in editor context menu
  - or click `PREDA: Run` button in context menu of file explorer
  - a new VSCode Tab will be automatically launched after the execuiton of the PREDA script
    ![Alt text](https://github.com/preda-devteam/preda/blob/main/vsce/resource/images/run.png?raw=true "Run")

## Snippets

You can use those snippets in `.prdts`.

| Trigger           | content                                          |
| :---------------- | :----------------------------------------------- |
| set:seed          | random.reseed {seed}                             |
| set:gas           | chain.gaslimit {gas}                             |
| set:state         | state.set scope.contract_name {state}            |
| chain:run         | chain.run                                        |
| chain:info        | chain.info                                       |
| chain:deploy      | chain.deploy {contract}                          |
| viz:b#all         | viz.block #all                                   |
| viz:b#shard       | viz.block #shard                                 |
| viz:b#shard:block | viz.block #shard:block                           |
| viz:s             | viz.shard #g,n                                   |
| viz:a             | viz.addr @all,random,n                           |
| viz:t             | viz.txn {txn}                                    |
| viz:p             | viz.profiling                                    |
| viz:trace         | viz.trace {txn}                                  |
| viz:section       | viz.section {txn}                                |
| stopwatch         | stopwatch.restart + emptyline + stopwatch.report |
