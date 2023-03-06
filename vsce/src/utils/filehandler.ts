import * as vscode from "vscode";
import * as fs from "fs";
import { promisify } from "util";
import * as Mustache from "mustache";
import * as path from "path";

interface Params {
  filepath: string;
}

export class File {
  readFile() {
    return promisify(fs.readFile);
  }

  writeFile() {
    return promisify(fs.writeFile);
  }
}

export default class FileHandler extends File {
  filepath: string;

  constructor(params: Params) {
    super();
    this.filepath = params.filepath;
  }

  async inject(data: KeyValue) {
    const exist = await this.fileExist();
    if (exist) {
      const raw = await this.readFile()(this.filepath, {
        encoding: "utf-8",
      });
      const content = Mustache.render(raw, data || {});
      return this.writeFile()(this.filepath, content);
    }
    throw new Error(
      "Result output to html file failed for the file does not exist: " +
        this.filepath
    );
  }

  async fileExist() {
    return fs.existsSync(this.filepath);
  }

  async overide() {}
}
