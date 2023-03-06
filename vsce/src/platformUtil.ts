import { exec } from "./utils/process";

type SupportedTerminal = "cmd" | "bash";

export default class PlatformUtil {
  platform: string;

  constructor() {
    this.platform = process.platform;
  }

  get isWin() {
    return this.platform === "win32";
  }

  async terminalShellPath(name: SupportedTerminal): Promise<string> {
    if (!this.isWin) {
      // if mac
    }
    return exec("where " + name);
  }
}
