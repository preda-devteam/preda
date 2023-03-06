interface KeyValue<T = any> {
  [props: string]: T;
}

interface Window {
  PREDA_VIZ_LOG: any;
  BuildContext: {
    args: string;
    contract: string;
  };
}

declare module 'react-ui-tree'