import * as qs from "qs";
import fetch, { RequestInit } from "node-fetch";
import { getRPCService, getDioScanService } from "../utils/configure";

import { shakeKeyValue } from "./string";

interface CommonResponse<T> {
  Status: number;
  Message: string;
  Result: T;
}

type DioxScanChainBasicInfo = CommonResponse<{
  AvgGasPrice: number;
}>;

function checkStatus(response: any) {
  if (response.ok) {
    return response;
  } else {
    return Promise.reject(response);
  }
}

export default class Fetcher {
  get api() {
    return `${getRPCService()}/api`;
  }

  get dioScanApi() {
    const host = getDioScanService();
    // Environment: production
    if (host.startsWith("https://")) {
      return `${host}/api`;
    }
    // Environment: dev
    return `${host}/dev/api`;
  }

  prune = (url: string) => (url.endsWith("/") ? url.slice(0, -1) : url);

  get<T>(service: string, options: any): Promise<T> {
    options = { credentials: "omit", ...options };

    let absoluteUrl = service.startsWith("http") ? service : this.api + service;

    if (options.data) {
      const data = shakeKeyValue(options.data) || {};
      absoluteUrl += "?" + qs.stringify(data, { encode: false });
    }

    return fetch(absoluteUrl, options)
      .then(checkStatus)
      .then((r) => {
        return r.json();
      });
  }

  post<T>(service: string, options: RequestInit = {}): Promise<T> {
    const { body } = options;

    const concatOption: RequestInit = {
      ...options,
      method: "post",
      body,
    };
    const absoluteUrl = service.startsWith("http")
      ? service
      : this.api + (service.startsWith("/") ? service.slice(1) : service);

    return fetch(absoluteUrl, concatOption)
      .then(checkStatus)
      .then((r) => r.json());
  }

  composeDeployData(body: string) {
    return this.post<{
      err?: number;
      rsp: string;
      ret: { TxData: string; GasOffered: number };
    }>("?req=tx.compose", { body });
  }

  getAverageGasPrice() {
    return this.get<DioxScanChainBasicInfo>(this.dioScanApi, {
      data: {
        module: "chain",
        action: "status",
      },
    });
  }
}
