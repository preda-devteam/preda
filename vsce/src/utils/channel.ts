import * as vscode from "vscode";
import { formatTime } from "./time";

class OutputChannel {
  channel: vscode.OutputChannel;
  constructor(name: string) {
    this.channel = vscode.window.createOutputChannel(name);
  }

  clear() {
    this.channel.clear();
  }

  show() {
    this.channel.show();
  }

  append(message: string) {
    const now = formatTime(Date.now(), "YYYY-MM-DD HH:mm:ss");
    this.channel.appendLine(`=> ${now} ${message}`);
  }
}

export default OutputChannel;
