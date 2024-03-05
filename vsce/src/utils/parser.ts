import { readFile, readdir } from "node:fs/promises";
import { basename, dirname, resolve } from "node:path";

export interface ContractItem {
  name: string;
  fullPath: string;
  content: string;
  filename: string;
  dependedBy: string | null;
  //   depItems?: ContractItem[];
}

export interface ContractTree {
  [key: string]: {
    name: string;
    fullpath: string;
    deps: string[];
    filename: string;
  };
}

const nameReg = /(?<=contract)\s+\w+\b/;

function getContractName(content: string): string | null {
  const contractName = content.match(nameReg);
  return contractName ? contractName[0].trim() : null;
}

async function buildLocalTree(dirname: string) {
  const files = await readdir(dirname);
  const prds = files.filter((file) => file.endsWith(".prd"));
  return prds.reduce<Promise<ContractTree>>((prev, filepath) => {
    return prev.then(async (resp) => {
      const filename = basename(filepath);
      const fullpath = resolve(dirname, filepath);
      const content = await readFile(fullpath, { encoding: "utf-8" });
      const name = getContractName(content);
      const deps: string[] = [];
      const depReg = /(?<!\/\/.*)(?<!\/\*[\s\S]*?)(?<=\bimport\s+)(\w+)\b/g;
      const matched = content.match(depReg);
      if (!name) {
        return resp;
      }
      resp[name] = { name, fullpath, filename, deps: matched || [] };
      return resp;
    });
  }, Promise.resolve({}));
}

async function collectOne(params: {
  fullPath: string;
  tree: ContractTree;
  collection: ContractItem[];
  dependedBy: string | null;
}): Promise<ContractItem[]> {
  const { collection, fullPath, tree, dependedBy } = params;
  const content = await readFile(fullPath, { encoding: "utf-8" });
  const contractName = content.match(nameReg);
  const cname = contractName ? contractName[0].trim() : "";
  const matched = tree[cname];
  const filename = basename(fullPath);

  if (matched) {
    const { deps } = matched;
    if (deps.length > 0) {
      for (let dep of deps) {
        const depMatched = tree[dep];
        if (depMatched) {
          const { fullpath: depFullPath } = depMatched;
          await collectOne({
            fullPath: depFullPath,
            tree,
            collection,
            dependedBy: cname,
          });
        }
      }
    }
  }
  // deplication
  const exist = collection.some(
    (col) => col.name === cname && col.fullPath === fullPath
  );
  if (!exist) {
    collection.push({
      name: cname,
      fullPath: fullPath,
      content,
      filename,
      dependedBy,
    });
  }
  return collection;
}

async function collect(
  fullPath: string,
  tree: ContractTree
): Promise<ContractItem[]> {
  const collection: ContractItem[] = [];
  await collectOne({ fullPath, tree, collection, dependedBy: null });
  return collection;
}

export default async function collectDependency(
  path: string
): Promise<ContractItem[]> {
  const dir = dirname(path);
  const tree = await buildLocalTree(dir);
  return collect(path, tree);
}
