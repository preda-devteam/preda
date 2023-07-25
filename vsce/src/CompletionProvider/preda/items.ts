import * as vscode from "vscode";

import { CompletationItems } from "../provider";

const completaionItems: CompletationItems[] = [
  {
    match: /\b__transaction\.$/,
    items: [
      new vscode.CompletionItem("get_type", vscode.CompletionItemKind.Method),
      new vscode.CompletionItem(
        "get_self_address",
        vscode.CompletionItemKind.Method
      ),
      new vscode.CompletionItem(
        "get_timestamp",
        vscode.CompletionItemKind.Method
      ),
      new vscode.CompletionItem(
        "get_signers",
        vscode.CompletionItemKind.Method
      ),
      new vscode.CompletionItem(
        "verify_signer",
        vscode.CompletionItemKind.Method
      ),
      new vscode.CompletionItem(
        "get_originated_shard_index",
        vscode.CompletionItemKind.Method
      ),
      new vscode.CompletionItem(
        "get_originated_shard_order",
        vscode.CompletionItemKind.Method
      ),
      new vscode.CompletionItem(
        "get_initiator_address",
        vscode.CompletionItemKind.Method
      ),
      new vscode.CompletionItem(
        "get_sender",
        vscode.CompletionItemKind.Method
      ),
    ],
  },
  {
    match: /\b__block\.$/,
    items: [
      new vscode.CompletionItem("get_height", vscode.CompletionItemKind.Method),
      new vscode.CompletionItem(
        "get_shard_index",
        vscode.CompletionItemKind.Method
      ),
      new vscode.CompletionItem(
        "get_shard_order",
        vscode.CompletionItemKind.Method
      ),
      new vscode.CompletionItem(
        "get_parent_shard_index",
        vscode.CompletionItemKind.Method
      ),
      new vscode.CompletionItem(
        "get_parent_shard_order",
        vscode.CompletionItemKind.Method
      ),
      new vscode.CompletionItem(
        "get_parent_block_hash",
        vscode.CompletionItemKind.Method
      ),
      new vscode.CompletionItem(
        "get_timestamp",
        vscode.CompletionItemKind.Method
      ),
      new vscode.CompletionItem(
        "get_random_number",
        vscode.CompletionItemKind.Method
      ),
      new vscode.CompletionItem(
        "get_secure_random_number",
        vscode.CompletionItemKind.Method
      ),
      new vscode.CompletionItem(
        "get_miner_address",
        vscode.CompletionItemKind.Method
      ),
    ],
  },
  {
    match: /\b__debug\.$/,
    items: [
      new vscode.CompletionItem("assert", vscode.CompletionItemKind.Method),
      new vscode.CompletionItem("print", vscode.CompletionItemKind.Method),
    ],
  },
];

export default completaionItems;
