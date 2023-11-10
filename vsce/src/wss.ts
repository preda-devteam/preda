import { WebSocketServer, WebSocket, Server } from "ws";
import * as vscode from "vscode";
import * as detectPort from "detect-port";
import { v4 as uuidV4 } from "uuid";

import Channel from "./utils/channel";

interface Task {
  data: string;
  id?: string;
  filename: string;
  filepath: string;
  cname: string;
  dapp: string;
  avgGas: number;
  gasOffered: number;
}

interface TaskRes {
  err?: string;
  res: string;
  ret?: Task;
}

export class WSServer {
  server: Server | null = null;
  connections: WebSocket[] = [];
  port: number = 15123;
  outputChannel: Channel;
  taskQueue: Task[] = [];

  constructor(outputChannel: Channel) {
    // setInterval(() => {
    //   this.broadcast(new Date().toString());
    // }, 5000);
    this.outputChannel = outputChannel;
  }

  create = async (): Promise<WSServer> => {
    const port = await detectPort(this.port);
    this.port = port;
    this.createWSServer(port);
    this.outputChannel.append("websocket server is listening on port: " + port);
    return this;
  };

  createWSServer = (port: number) => {
    this.server = new WebSocketServer({ port });

    this.server.on("connection", (ws) => {
      this.connections.push(ws);

      const total = this.connections.length;
      this.outputChannel.append(
        `the core-dapps connected, current clients connected: ${total}`
      );

      ws.on("error", (e) => {
        this.outputChannel.append(e.toString());
        vscode.window.showErrorMessage(e.toString());
      });

      ws.on("message", (data) => {
        const request = data.toString();
        const json = JSON.parse(request);
        const { req, params } = json;
        let resp: TaskRes | null = null;

        this.outputChannel.append("websocket server received: " + request);
        switch (req) {
          case "task.get":
            resp = this.handleGetTask(req, params);
            break;
          case "task.done":
            this.handleTaskDone(req, params);
            return;
          default:
            resp = { err: "Unsupported request: " + req, res: req };
        }
        ws.send(JSON.stringify(resp));
      });

      ws.on("close", () => {
        const index = this.connections.findIndex((conn) => conn === ws);
        if (index > -1) {
          this.connections.splice(index, 1);
        }
        const total = this.connections.length;
        this.outputChannel.append(
          `the core-dapps disconnect, remaining ${total} clients connected`
        );
      });
    });
  };

  handleGetTask(req: string, id: string): TaskRes {
    if (!id) {
      return { err: "Task Id is required", res: req };
    }
    const task = this.getTask(id);
    return { res: req, ret: task };
  }

  handleTaskDone(req: string, params: { id: string; hash: string }) {
    const { id, hash } = params;
    if (!hash || !id) {
      this.outputChannel.append("Id or hash is empty");
      return;
    }
    this.removeTask(id);
    this.outputChannel.append(
      `🎉🎉🎉Deployed successfully🎉🎉🎉, tx hash: ${hash}`
    );
    vscode.window.showInformationMessage(
      `Deployed successfully, tx hash: ${hash}`
    );
  }

  broadcast = (message: string) => {
    this.connections.forEach((conn) => {
      conn.send(message);
    });
  };

  addTask(task: Task) {
    task.id = task.id || uuidV4();
    this.taskQueue.push(task);
    return task.id;
  }

  getTask(id: string) {
    return this.taskQueue.find((t) => t.id === id);
  }

  removeTask(id: string) {
    // remove one task
    if (id) {
      const index = this.taskQueue.findIndex((item) => item.id === id);
      this.taskQueue.splice(index);
      return;
    }
    // remove all task
    this.taskQueue = [];
  }
}
