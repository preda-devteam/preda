import fetcher from 'node-fetch';

const TIMEOUT = 10000;

function checkStatus(response: any) {
  if (response.ok) {
    return response;
  }
  const error = new Error(response.statusText);
  return Promise.reject(error);
}

export default class Fetcher {
  constructor() {}

  getCmdName(url: string) {
    return url.match(/(?<=\/cmd\/)([\w\.])+/)?.[0];
  }

  fetch<T = {}>(url: string, options: any = {}): Promise<T> {
    const opt = Object.assign(options, {
      timeout: TIMEOUT,
    });
    return fetcher(url, opt)
      .then(checkStatus)
      .then(async r => {
        const contentType = r.headers.get('content-type');
        if (contentType === 'text/plain') {
          const data = await r.text();
          // data.includes('ERR:') && showErrorTip(data, this.getCmdName(url) || '');
          return data;
        }
        return r.json();
      })
      .catch(ex => {
        // showErrorTip(ex.toString(), this.getCmdName(url) || '');
      });
  }

  post<T = {}>(url: string, body = {}): Promise<T> {
    const options = {
      method: 'post',
      headers: {
        'Content-Type': 'application/json',
      },
      body: typeof body === 'string' ? body : JSON.stringify(body),
      timeout: TIMEOUT,
    };
    return this.fetch(url, options);
  }
}
