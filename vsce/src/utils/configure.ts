import * as vscode from "vscode";

function trim(url: string) {
  if (url.endsWith("/")) {
    return url.slice(0, -1);
  }
  return url;
}

export function getConf(key: string, defaults = ""): string {
  const conf = vscode.workspace.getConfiguration("Preda");
  const v = conf.get<string>(key) ?? defaults;
  return v;
}

export function getCoreDAppUrl() {
  const url = trim(getConf("core-dapp.Url"));
  return url;
}

export function getRPCService() {
  const url = trim(getConf("rpc.service"));
  return url;
}

export function getDioScanService() {
  const url = trim(getConf("dioscan.service"));
  return url;
}
