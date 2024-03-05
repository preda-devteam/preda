import * as vscode from "vscode";
import * as path from "node:path";
import { readFileSync, writeFileSync, existsSync } from "node:fs";
import * as json from "json-bigint";

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

export interface ArgsCacheParams {
  group: string;
  filename: string;
  dirname: string;
}

export class ArgsCache {
  // the contract name
  group: string;
  // cache.json
  filename: string;
  // full path
  fullpath: string;

  constructor(params: ArgsCacheParams) {
    const { group, filename, dirname } = params;
    this.group = group;
    this.filename = filename;
    this.fullpath = path.resolve(dirname, filename);
    if (!existsSync(this.fullpath)) {
      writeFileSync(this.fullpath, json.stringify({}), { encoding: "utf-8" });
    }
  }

  set(key: string, value: string = "") {
    const file = readFileSync(this.fullpath, { encoding: "utf-8" });
    const content = json.parse(file);
    content[this.group] = content[this.group] || {};
    content[this.group][key] = value;
    writeFileSync(this.fullpath, JSON.stringify(content, null, 4));
    return true;
  }

  // get
  get(key: string): undefined | string {
    const file = readFileSync(this.fullpath, { encoding: "utf-8" });
    const content = JSON.parse(file);
    if (content[this.group]) {
      return content[this.group][key] ?? undefined;
    }
    return undefined;
  }
}

export class DeploymentArgsCache extends ArgsCache {
  constructor(params: Omit<ArgsCacheParams, "filename">) {
    super({
      filename: "cached.json",
      ...params,
    });
  }
}
