import * as vscode from "vscode";
import * as fs from "fs/promises";
import * as ejs from "ejs";
import * as path from "path";
import * as Mustache from "mustache";

interface CreateParams {
  pageData: KeyValue;
}

interface ViewLoaderParams {
  filepath: string;
  context: vscode.ExtensionContext;
}

export default class ViewLoader {
  // static currentPanel?: vscode.WebviewPanel;

  private context: vscode.ExtensionContext;
  private filepath: string;
  private panel?: vscode.WebviewPanel;
  private disposables: vscode.Disposable[];
  private filename: string;

  resourceUri: vscode.Uri;

  constructor(params: ViewLoaderParams) {
    this.context = params.context;
    this.filepath = params.filepath;
    this.filename = path.basename(this.filepath, ".html");
    this.disposables = [];
    this.resourceUri = vscode.Uri.file(
      path.join(this.context.extensionPath, "out/web")
    );
    this.init();
  }

  get currentPanel() {
    return this.panel;
  }

  init() {}

  async create(params?: CreateParams) {
    const { pageData } = params || {};
    this.panel = vscode.window.createWebviewPanel(
      "Preda",
      "Preda Viz: " + this.filename,
      vscode.ViewColumn.One,
      {
        enableScripts: true,
        retainContextWhenHidden: true,
        localResourceRoots: [
          vscode.Uri.file(path.join(this.context.extensionPath, "out/web")),
        ],
      }
    );
    this.panel.webview.html = await this.render(pageData);

    // Reset when the current panel is closed
    this.panel.onDidDispose(
      () => {
        this.panel = undefined;
        console.log("webview disposed");
      },
      null,
      this.context.subscriptions
    );
    return this;
  }

  dispose() {
    this.panel?.dispose();
  }

  async render(data: KeyValue = {}): Promise<string> {
    const content = await fs.readFile(this.filepath, { encoding: "utf-8" });
    const resourcePath = this.panel?.webview.asWebviewUri(this.resourceUri);
    const joined = Object.assign(data, {
      staticPath: resourcePath,
    });
    // return ejs.render(content, joined);
    return Mustache.render(content, joined);
  }
}
