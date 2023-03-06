import * as cp from "child_process";
import * as vscode from "vscode";

export function exec(cmd: string, options?: cp.ExecOptions): Promise<string> {
  return new Promise((resolve, reject) => {
    cp.exec(
      cmd,
      Object.assign(options || {}, { maxBuffer: 1024 * 1024 * 5 }),
      (error, stdout, stderr) => {
        if (error || stderr) {
          reject(error || stderr);
          return;
        }
        resolve(stdout);
      }
    );
  });
}

interface SpawnOutput {
  cmd: string;
  option: cp.SpawnOptionsWithoutStdio;
  args?: string[];
  onData: (data: Buffer) => void;
  onErr: (err: Error | Buffer) => void;
  onExt: (code: number | null) => Promise<void> | void;
}

export function spawn(params: SpawnOutput): cp.ChildProcess | null {
  const { cmd, option, onData, onErr, onExt, args = [] } = params;
  const sp: cp.ChildProcess = cp.spawn(cmd, args, option);
  if (sp) {
    sp.stdout!.on("data", (data) => onData(data));
    sp.stderr!.on("data", (data) => onErr(data));
  }
  sp.on("error", (err) => onErr(err));
  sp.on("exit", (code) => onExt(code));
  return sp;
}
