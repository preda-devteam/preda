type Message = any;

type VSCode = {
  postMessage<T extends Message = Message>(message: T): void;
  getState(): any;
  setState(state: any): void;
  [prop: string]: any;
};

declare const vscode: VSCode;

declare const PREDA_VIZ_LOG: any;

interface Struct {
  name: string;
  layout: Array<{identifier: string; dataType: string}>
}

interface Enumerator {
  name: string;
  value: Array<string>;
}

interface DeployFunction {
  name: string;
  flag: string;
  scope: string;
  opcode: number;
}

interface StateVariable {
  name: string;
  dataType: string;
  scope: string;
}

declare const BuildContext: {
  args: string;
  contract: string;
};
