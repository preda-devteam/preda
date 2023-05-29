import React from "react";
import ReactJson from "@dioxide-js/react-json-view";
const json = require("json-bigint")({ storeAsString: true });
import Tree from "../../component/Tree";

import './style.scss';
import { DeployBox, AddrBox, ShardBox, TxnBox, BlockBox, ProfingBox } from "@/component/BoxItem";

const mockdata = `
[
   {
      "type": "Run",
      "content": 
      {
         "script": "c:\\Users\\IDEA\\Documents\\GitHub\\oxd_preda\\simulator\\contracts\\Token.prdts",
         "ShardOrder": 2
      }
   },
   {
      "type": "Deploy",
      "content": 
      [
         {
            "contract": "Token",
            "source": "Token.prd",
            "engine": "PREDA_NATIVE",
            "hash": "07d55rhz0j7n1mkym1da6hcye6a8yc2e9kzz05fqbjyf6shftcn0",
            "finalized": false,
            "implments": [],
            "stateVariables": 
            [
               {"name": "a", "scope": "shard", "dataType": "int32"},
               {"name": "balance", "scope": "address", "dataType": "bigint"}
            ],
            "scopes": {"shard": "HasState", "address": "HasState|HasFunction"},
            "scatteredMaps": {},
            "structs": 
            [
               {
                  "name": "payment",
                  "layout": 
                  [
                     {"identifier": "to", "dataType": "address"},
                     {"identifier": "amount", "dataType": "bigint"}
                  ]
               }
            ],
            "enumerables": [],
            "interfaces": {},
            "functions": 
            [
               {
                  "name": "transfer",
                  "flag": "InvokeByNormalTransaction|EmitRelayInAddressScope",
                  "scope": "address",
                  "opcode": 0
               },
               {
                  "name": "transfer_n",
                  "flag": "InvokeByNormalTransaction|EmitRelayInAddressScope",
                  "scope": "address",
                  "opcode": 1
               },
               {
                  "name": "__relaylambda_2_transfer",
                  "flag": "InvokeByRelayTransaction",
                  "scope": "address",
                  "opcode": 2
               },
               {
                  "name": "__relaylambda_3_transfer_n",
                  "flag": "InvokeByRelayTransaction",
                  "scope": "address",
                  "opcode": 3
               }
            ]
         }
      ]
   },
   {
      "type": "Txn",
      "command": "viz.txn txn1[0]",
      "content": 
      [
         {
            "InvokeContextType": "Normal",
            "Target": "p8mw97q0ve5zywr12ren88gstekb56539n0ry4s1mya2wftjb0yg760n5g:ed25519",
            "AddressIndex": "@8",
            "BuildNum": 1,
            "Timestamp": 1683270844582,
            "Contract": "Token",
            "Function": "transfer",
            "InvokeResult": "Success",
            "Arguments": 
            {
               "to": "efv837mggrshfc5gq3jzayyjcwbyq2vc7fhm5vg1cm43de8mxxyg67dawr:ed25519",
               "amount": "128700"
            },
            "Height": 0,
            "ShardIndex": 3,
            "ShardOrder": 2
         }
      ]
   },
   {
      "type": "Trace",
      "command": "viz.trace txn1[0]",
      "content": 
      [
         {
            "tx_id": 1,
            "tx_info": 
            {
               "InvokeContextType": "Normal",
               "Target": "p8mw97q0ve5zywr12ren88gstekb56539n0ry4s1mya2wftjb0yg760n5g:ed25519",
               "AddressIndex": "@8",
               "BuildNum": 1,
               "Timestamp": 1683270844582,
               "Contract": "Token",
               "Function": "transfer",
               "Arguments": 
               {
                  "to": "efv837mggrshfc5gq3jzayyjcwbyq2vc7fhm5vg1cm43de8mxxyg67dawr:ed25519",
                  "amount": "128700"
               },
               "Height": 0,
               "ShardIndex": 3,
               "ShardOrder": 2
            },
            "father": -1
         },
         {
            "tx_id": 2,
            "tx_info": 
            {
               "InvokeContextType": "RelayInbound",
               "Target": "efv837mggrshfc5gq3jzayyjcwbyq2vc7fhm5vg1cm43de8mxxyg67dawr:ed25519",
               "AddressIndex": "@2",
               "BuildNum": 1,
               "Timestamp": 1683270843314,
               "Contract": "Token",
               "Function": "__relaylambda_2_transfer",
               "Arguments": {"amount": "128700"},
               "Height": 1,
               "ShardIndex": 1,
               "ShardOrder": 2
            },
            "father": 1
         }
      ]
   },
   {
      "type": "Block",
      "command": "viz.block #all",
      "content": 
      [
         {
            "Height": 0,
            "PrevBlock": "0000000000000000000000000000000000000000000000000000",
            "ShardIndex": "#0",
            "Timestamp": 1683270843219,
            "Miner": "m8gmd29r0afkxf8a4cvar2bf0psh1dq5k0pbm1gpggcat7tqfmq072xt20:ed25519",
            "TxnCount": 1,
            "ConfirmTxn": 
            [
               {
                  "InvokeResult": "Success",
                  "InvokeContextType": "Normal",
                  "Target": "qw98j2ev8rkxk5gbxg8nddhb74784s1pejnft1qr3y63gmfwntv07gb8xc:ed25519",
                  "AddressIndex": "@9",
                  "BuildNum": 1,
                  "Timestamp": 1683270844582,
                  "Contract": "Token",
                  "Function": "transfer",
                  "Arguments": 
                  {
                     "to": "3mfwbdv1wafdhptc5j69t90kz0p78q1xssfyx2j8cjvqsm1056j07953a0:ed25519",
                     "amount": "152200"
                  },
                  "Height": 0,
                  "ShardIndex": 0,
                  "ShardOrder": 2
               }
            ]
         },
         {
            "Height": 1,
            "PrevBlock": "t34f0n0t60jbg000000000000000000000000000000000000000",
            "ShardIndex": "#0",
            "Timestamp": 1683270848219,
            "Miner": "m8gmd29r0afkxf8a4cvar2bf0psh1dq5k0pbm1gpggcat7tqfmq072xt20:ed25519",
            "TxnCount": 1,
            "ConfirmTxn": 
            [
               {
                  "InvokeResult": "Success",
                  "InvokeContextType": "Normal",
                  "Target": "780x524p9ym3tdq3tafvqpjdwzbvmf1g8dmphht1d89n8e8qyer07myw94:ed25519",
                  "AddressIndex": "@11",
                  "BuildNum": 1,
                  "Timestamp": 1683270844582,
                  "Contract": "Token",
                  "Function": "transfer",
                  "Arguments": 
                  {
                     "to": "780x524p9ym3tdq3tafvqpjdwzbvmf1g8dmphht1d89n8e8qyer07myw94:ed25519",
                     "amount": "145700"
                  },
                  "Height": 1,
                  "ShardIndex": 0,
                  "ShardOrder": 2
               }
            ]
         },
         {
            "Height": 2,
            "PrevBlock": "fxcg78ej1kw6e000000000000000000000000000000000000000",
            "ShardIndex": "#0",
            "Timestamp": 1683270853219,
            "Miner": "m8gmd29r0afkxf8a4cvar2bf0psh1dq5k0pbm1gpggcat7tqfmq072xt20:ed25519",
            "TxnCount": 1,
            "ConfirmTxn": 
            [
               {
                  "InvokeResult": "Success",
                  "InvokeContextType": "RelayInbound",
                  "Target": "780x524p9ym3tdq3tafvqpjdwzbvmf1g8dmphht1d89n8e8qyer07myw94:ed25519",
                  "AddressIndex": "@14829735431805717965",
                  "BuildNum": 1,
                  "Timestamp": 1683270848219,
                  "Contract": "Token",
                  "Function": "__relaylambda_2_transfer",
                  "Arguments": {"amount": "145700"},
                  "Height": 2,
                  "ShardIndex": 0,
                  "ShardOrder": 2
               }
            ]
         },
         {
            "Height": 3,
            "PrevBlock": "r7d4rcem5sbsm000000000000000000000000000000000000000",
            "ShardIndex": "#0",
            "Timestamp": 1683270858219,
            "Miner": "m8gmd29r0afkxf8a4cvar2bf0psh1dq5k0pbm1gpggcat7tqfmq072xt20:ed25519",
            "TxnCount": 1,
            "ConfirmTxn": 
            [
               {
                  "InvokeResult": "Success",
                  "InvokeContextType": "RelayInbound",
                  "Target": "780x524p9ym3tdq3tafvqpjdwzbvmf1g8dmphht1d89n8e8qyer07myw94:ed25519",
                  "AddressIndex": "@14829735431805717965",
                  "BuildNum": 1,
                  "Timestamp": 1683270848281,
                  "Contract": "Token",
                  "Function": "__relaylambda_2_transfer",
                  "Arguments": {"amount": "173100"},
                  "Height": 3,
                  "ShardIndex": 0,
                  "ShardOrder": 2
               }
            ]
         },
         {
            "Height": 4,
            "PrevBlock": "23chnd21a2ha4000000000000000000000000000000000000000",
            "ShardIndex": "#0",
            "Timestamp": 1683270863219,
            "Miner": "m8gmd29r0afkxf8a4cvar2bf0psh1dq5k0pbm1gpggcat7tqfmq072xt20:ed25519",
            "TxnCount": 1,
            "ConfirmTxn": 
            [
               {
                  "InvokeResult": "Success",
                  "InvokeContextType": "Normal",
                  "Target": "qw98j2ev8rkxk5gbxg8nddhb74784s1pejnft1qr3y63gmfwntv07gb8xc:ed25519",
                  "AddressIndex": "@9",
                  "BuildNum": 1,
                  "Timestamp": 1683270844583,
                  "Contract": "Token",
                  "Function": "transfer",
                  "Arguments": 
                  {
                     "to": "780x524p9ym3tdq3tafvqpjdwzbvmf1g8dmphht1d89n8e8qyer07myw94:ed25519",
                     "amount": "119900"
                  },
                  "Height": 4,
                  "ShardIndex": 0,
                  "ShardOrder": 2
               }
            ]
         },
         {
            "Height": 5,
            "PrevBlock": "13bv0zgjsqqtj000000000000000000000000000000000000000",
            "ShardIndex": "#0",
            "Timestamp": 1683270868219,
            "Miner": "m8gmd29r0afkxf8a4cvar2bf0psh1dq5k0pbm1gpggcat7tqfmq072xt20:ed25519",
            "TxnCount": 1,
            "ConfirmTxn": 
            [
               {
                  "InvokeResult": "Success",
                  "InvokeContextType": "RelayInbound",
                  "Target": "780x524p9ym3tdq3tafvqpjdwzbvmf1g8dmphht1d89n8e8qyer07myw94:ed25519",
                  "AddressIndex": "@14829735431805717965",
                  "BuildNum": 1,
                  "Timestamp": 1683270863219,
                  "Contract": "Token",
                  "Function": "__relaylambda_2_transfer",
                  "Arguments": {"amount": "119900"},
                  "Height": 5,
                  "ShardIndex": 0,
                  "ShardOrder": 2
               }
            ]
         },
         {
            "Height": 0,
            "PrevBlock": "0000000000000000000000000000000000000000000000000000",
            "ShardIndex": "#1",
            "Timestamp": 1683270843251,
            "Miner": "m8gmd29r0afkxf8a4cvar2bf0psh1dq5k0pbm1gpggcat7tqfmq072xt20:ed25519",
            "TxnCount": 1,
            "ConfirmTxn": 
            [
               {
                  "InvokeResult": "Success",
                  "InvokeContextType": "Normal",
                  "Target": "efv837mggrshfc5gq3jzayyjcwbyq2vc7fhm5vg1cm43de8mxxyg67dawr:ed25519",
                  "AddressIndex": "@2",
                  "BuildNum": 1,
                  "Timestamp": 1683270844582,
                  "Contract": "Token",
                  "Function": "transfer",
                  "Arguments": 
                  {
                     "to": "mrq2yd2w7btjn43hhk2gfvdyedg1qf9n387h4fn5vfx3vde5evhg668gtc:ed25519",
                     "amount": "165400"
                  },
                  "Height": 0,
                  "ShardIndex": 1,
                  "ShardOrder": 2
               }
            ]
         },
         {
            "Height": 1,
            "PrevBlock": "tnm7p2x5jm82j000000000000000000000000000000000000000",
            "ShardIndex": "#1",
            "Timestamp": 1683270848251,
            "Miner": "m8gmd29r0afkxf8a4cvar2bf0psh1dq5k0pbm1gpggcat7tqfmq072xt20:ed25519",
            "TxnCount": 1,
            "ConfirmTxn": 
            [
               {
                  "InvokeResult": "Success",
                  "InvokeContextType": "RelayInbound",
                  "Target": "efv837mggrshfc5gq3jzayyjcwbyq2vc7fhm5vg1cm43de8mxxyg67dawr:ed25519",
                  "AddressIndex": "@2",
                  "BuildNum": 1,
                  "Timestamp": 1683270843314,
                  "Contract": "Token",
                  "Function": "__relaylambda_2_transfer",
                  "Arguments": {"amount": "128700"},
                  "Height": 1,
                  "ShardIndex": 1,
                  "ShardOrder": 2
               }
            ]
         },
         {
            "Height": 2,
            "PrevBlock": "d4r1a5ga9b3c8000000000000000000000000000000000000000",
            "ShardIndex": "#1",
            "Timestamp": 1683270853251,
            "Miner": "m8gmd29r0afkxf8a4cvar2bf0psh1dq5k0pbm1gpggcat7tqfmq072xt20:ed25519",
            "TxnCount": 1,
            "ConfirmTxn": 
            [
               {
                  "InvokeResult": "Success",
                  "InvokeContextType": "RelayInbound",
                  "Target": "3mfwbdv1wafdhptc5j69t90kz0p78q1xssfyx2j8cjvqsm1056j07953a0:ed25519",
                  "AddressIndex": "@14829735431805717965",
                  "BuildNum": 1,
                  "Timestamp": 1683270843219,
                  "Contract": "Token",
                  "Function": "__relaylambda_2_transfer",
                  "Arguments": {"amount": "152200"},
                  "Height": 2,
                  "ShardIndex": 1,
                  "ShardOrder": 2
               }
            ]
         },
         {
            "Height": 3,
            "PrevBlock": "4apzjfg45tmet000000000000000000000000000000000000000",
            "ShardIndex": "#1",
            "Timestamp": 1683270858251,
            "Miner": "m8gmd29r0afkxf8a4cvar2bf0psh1dq5k0pbm1gpggcat7tqfmq072xt20:ed25519",
            "TxnCount": 0
         },
         {
            "Height": 4,
            "PrevBlock": "rpfwjmdaka4v2000000000000000000000000000000000000000",
            "ShardIndex": "#1",
            "Timestamp": 1683270863251,
            "Miner": "m8gmd29r0afkxf8a4cvar2bf0psh1dq5k0pbm1gpggcat7tqfmq072xt20:ed25519",
            "TxnCount": 1,
            "ConfirmTxn": 
            [
               {
                  "InvokeResult": "Success",
                  "InvokeContextType": "RelayInbound",
                  "Target": "3mfwbdv1wafdhptc5j69t90kz0p78q1xssfyx2j8cjvqsm1056j07953a0:ed25519",
                  "AddressIndex": "@14829735431805717965",
                  "BuildNum": 1,
                  "Timestamp": 1683270858314,
                  "Contract": "Token",
                  "Function": "__relaylambda_2_transfer",
                  "Arguments": {"amount": "110700"},
                  "Height": 4,
                  "ShardIndex": 1,
                  "ShardOrder": 2
               }
            ]
         },
         {
            "Height": 5,
            "PrevBlock": "zfga9xk02hpqw000000000000000000000000000000000000000",
            "ShardIndex": "#1",
            "Timestamp": 1683270868251,
            "Miner": "m8gmd29r0afkxf8a4cvar2bf0psh1dq5k0pbm1gpggcat7tqfmq072xt20:ed25519",
            "TxnCount": 0
         },
         {
            "Height": 0,
            "PrevBlock": "0000000000000000000000000000000000000000000000000000",
            "ShardIndex": "#2",
            "Timestamp": 1683270843281,
            "Miner": "m8gmd29r0afkxf8a4cvar2bf0psh1dq5k0pbm1gpggcat7tqfmq072xt20:ed25519",
            "TxnCount": 1,
            "ConfirmTxn": 
            [
               {
                  "InvokeResult": "Success",
                  "InvokeContextType": "Normal",
                  "Target": "30m6xsfy3s07grseqahq76fbwepq54d36n72t9gf1scfeawm8qxg7j1ssm:ed25519",
                  "AddressIndex": "@4",
                  "BuildNum": 1,
                  "Timestamp": 1683270844582,
                  "Contract": "Token",
                  "Function": "transfer",
                  "Arguments": 
                  {
                     "to": "p8mw97q0ve5zywr12ren88gstekb56539n0ry4s1mya2wftjb0yg760n5g:ed25519",
                     "amount": "143500"
                  },
                  "Height": 0,
                  "ShardIndex": 2,
                  "ShardOrder": 2
               }
            ]
         },
         {
            "Height": 1,
            "PrevBlock": "5hqdv137ec8ep000000000000000000000000000000000000000",
            "ShardIndex": "#2",
            "Timestamp": 1683270848281,
            "Miner": "m8gmd29r0afkxf8a4cvar2bf0psh1dq5k0pbm1gpggcat7tqfmq072xt20:ed25519",
            "TxnCount": 1,
            "ConfirmTxn": 
            [
               {
                  "InvokeResult": "Success",
                  "InvokeContextType": "Normal",
                  "Target": "m8gmd29r0afkxf8a4cvar2bf0psh1dq5k0pbm1gpggcat7tqfmq072xt20:ed25519",
                  "AddressIndex": "@0",
                  "BuildNum": 1,
                  "Timestamp": 1683270844582,
                  "Contract": "Token",
                  "Function": "transfer",
                  "Arguments": 
                  {
                     "to": "780x524p9ym3tdq3tafvqpjdwzbvmf1g8dmphht1d89n8e8qyer07myw94:ed25519",
                     "amount": "173100"
                  },
                  "Height": 1,
                  "ShardIndex": 2,
                  "ShardOrder": 2
               }
            ]
         },
         {
            "Height": 2,
            "PrevBlock": "21kcjfn95786g000000000000000000000000000000000000000",
            "ShardIndex": "#2",
            "Timestamp": 1683270853281,
            "Miner": "m8gmd29r0afkxf8a4cvar2bf0psh1dq5k0pbm1gpggcat7tqfmq072xt20:ed25519",
            "TxnCount": 1,
            "ConfirmTxn": 
            [
               {
                  "InvokeResult": "Success",
                  "InvokeContextType": "Normal",
                  "Target": "30m6xsfy3s07grseqahq76fbwepq54d36n72t9gf1scfeawm8qxg7j1ssm:ed25519",
                  "AddressIndex": "@4",
                  "BuildNum": 1,
                  "Timestamp": 1683270844583,
                  "Contract": "Token",
                  "Function": "transfer",
                  "Arguments": 
                  {
                     "to": "m8gmd29r0afkxf8a4cvar2bf0psh1dq5k0pbm1gpggcat7tqfmq072xt20:ed25519",
                     "amount": "156300"
                  },
                  "Height": 2,
                  "ShardIndex": 2,
                  "ShardOrder": 2
               }
            ]
         },
         {
            "Height": 3,
            "PrevBlock": "7ebn1t3902rc6000000000000000000000000000000000000000",
            "ShardIndex": "#2",
            "Timestamp": 1683270858281,
            "Miner": "m8gmd29r0afkxf8a4cvar2bf0psh1dq5k0pbm1gpggcat7tqfmq072xt20:ed25519",
            "TxnCount": 1,
            "ConfirmTxn": 
            [
               {
                  "InvokeResult": "Success",
                  "InvokeContextType": "RelayInbound",
                  "Target": "m8gmd29r0afkxf8a4cvar2bf0psh1dq5k0pbm1gpggcat7tqfmq072xt20:ed25519",
                  "AddressIndex": "@14829735431805717965",
                  "BuildNum": 1,
                  "Timestamp": 1683270853281,
                  "Contract": "Token",
                  "Function": "__relaylambda_2_transfer",
                  "Arguments": {"amount": "156300"},
                  "Height": 3,
                  "ShardIndex": 2,
                  "ShardOrder": 2
               }
            ]
         },
         {
            "Height": 4,
            "PrevBlock": "wz25b136qm814000000000000000000000000000000000000000",
            "ShardIndex": "#2",
            "Timestamp": 1683270863281,
            "Miner": "m8gmd29r0afkxf8a4cvar2bf0psh1dq5k0pbm1gpggcat7tqfmq072xt20:ed25519",
            "TxnCount": 1,
            "ConfirmTxn": 
            [
               {
                  "InvokeResult": "Success",
                  "InvokeContextType": "Normal",
                  "Target": "m8gmd29r0afkxf8a4cvar2bf0psh1dq5k0pbm1gpggcat7tqfmq072xt20:ed25519",
                  "AddressIndex": "@0",
                  "BuildNum": 1,
                  "Timestamp": 1683270844583,
                  "Contract": "Token",
                  "Function": "transfer",
                  "Arguments": 
                  {
                     "to": "p8mw97q0ve5zywr12ren88gstekb56539n0ry4s1mya2wftjb0yg760n5g:ed25519",
                     "amount": "184600"
                  },
                  "Height": 4,
                  "ShardIndex": 2,
                  "ShardOrder": 2
               }
            ]
         },
         {
            "Height": 5,
            "PrevBlock": "5kdr974xn5jdm000000000000000000000000000000000000000",
            "ShardIndex": "#2",
            "Timestamp": 1683270868281,
            "Miner": "m8gmd29r0afkxf8a4cvar2bf0psh1dq5k0pbm1gpggcat7tqfmq072xt20:ed25519",
            "TxnCount": 0
         },
         {
            "Height": 0,
            "PrevBlock": "0000000000000000000000000000000000000000000000000000",
            "ShardIndex": "#3",
            "Timestamp": 1683270843314,
            "Miner": "m8gmd29r0afkxf8a4cvar2bf0psh1dq5k0pbm1gpggcat7tqfmq072xt20:ed25519",
            "TxnCount": 1,
            "ConfirmTxn": 
            [
               {
                  "InvokeResult": "Success",
                  "InvokeContextType": "Normal",
                  "Target": "p8mw97q0ve5zywr12ren88gstekb56539n0ry4s1mya2wftjb0yg760n5g:ed25519",
                  "AddressIndex": "@8",
                  "BuildNum": 1,
                  "Timestamp": 1683270844582,
                  "Contract": "Token",
                  "Function": "transfer",
                  "Arguments": 
                  {
                     "to": "efv837mggrshfc5gq3jzayyjcwbyq2vc7fhm5vg1cm43de8mxxyg67dawr:ed25519",
                     "amount": "128700"
                  },
                  "Height": 0,
                  "ShardIndex": 3,
                  "ShardOrder": 2
               }
            ]
         },
         {
            "Height": 1,
            "PrevBlock": "6pwdmcs5er2p4000000000000000000000000000000000000000",
            "ShardIndex": "#3",
            "Timestamp": 1683270848314,
            "Miner": "m8gmd29r0afkxf8a4cvar2bf0psh1dq5k0pbm1gpggcat7tqfmq072xt20:ed25519",
            "TxnCount": 1,
            "ConfirmTxn": 
            [
               {
                  "InvokeResult": "Success",
                  "InvokeContextType": "RelayInbound",
                  "Target": "mrq2yd2w7btjn43hhk2gfvdyedg1qf9n387h4fn5vfx3vde5evhg668gtc:ed25519",
                  "AddressIndex": "@14829735431805717965",
                  "BuildNum": 1,
                  "Timestamp": 1683270843251,
                  "Contract": "Token",
                  "Function": "__relaylambda_2_transfer",
                  "Arguments": {"amount": "165400"},
                  "Height": 1,
                  "ShardIndex": 3,
                  "ShardOrder": 2
               }
            ]
         },
         {
            "Height": 2,
            "PrevBlock": "emt63ajdmj2h8000000000000000000000000000000000000000",
            "ShardIndex": "#3",
            "Timestamp": 1683270853314,
            "Miner": "m8gmd29r0afkxf8a4cvar2bf0psh1dq5k0pbm1gpggcat7tqfmq072xt20:ed25519",
            "TxnCount": 1,
            "ConfirmTxn": 
            [
               {
                  "InvokeResult": "Success",
                  "InvokeContextType": "RelayInbound",
                  "Target": "p8mw97q0ve5zywr12ren88gstekb56539n0ry4s1mya2wftjb0yg760n5g:ed25519",
                  "AddressIndex": "@14829735431805717965",
                  "BuildNum": 1,
                  "Timestamp": 1683270843281,
                  "Contract": "Token",
                  "Function": "__relaylambda_2_transfer",
                  "Arguments": {"amount": "143500"},
                  "Height": 2,
                  "ShardIndex": 3,
                  "ShardOrder": 2
               }
            ]
         },
         {
            "Height": 3,
            "PrevBlock": "7vxgxhj6d1khy000000000000000000000000000000000000000",
            "ShardIndex": "#3",
            "Timestamp": 1683270858314,
            "Miner": "m8gmd29r0afkxf8a4cvar2bf0psh1dq5k0pbm1gpggcat7tqfmq072xt20:ed25519",
            "TxnCount": 1,
            "ConfirmTxn": 
            [
               {
                  "InvokeResult": "Success",
                  "InvokeContextType": "Normal",
                  "Target": "mrq2yd2w7btjn43hhk2gfvdyedg1qf9n387h4fn5vfx3vde5evhg668gtc:ed25519",
                  "AddressIndex": "@6",
                  "BuildNum": 1,
                  "Timestamp": 1683270844583,
                  "Contract": "Token",
                  "Function": "transfer",
                  "Arguments": 
                  {
                     "to": "3mfwbdv1wafdhptc5j69t90kz0p78q1xssfyx2j8cjvqsm1056j07953a0:ed25519",
                     "amount": "110700"
                  },
                  "Height": 3,
                  "ShardIndex": 3,
                  "ShardOrder": 2
               }
            ]
         },
         {
            "Height": 4,
            "PrevBlock": "d1n6v1htfw9kp000000000000000000000000000000000000000",
            "ShardIndex": "#3",
            "Timestamp": 1683270863314,
            "Miner": "m8gmd29r0afkxf8a4cvar2bf0psh1dq5k0pbm1gpggcat7tqfmq072xt20:ed25519",
            "TxnCount": 0
         },
         {
            "Height": 5,
            "PrevBlock": "40eyecehfhwkg000000000000000000000000000000000000000",
            "ShardIndex": "#3",
            "Timestamp": 1683270868314,
            "Miner": "m8gmd29r0afkxf8a4cvar2bf0psh1dq5k0pbm1gpggcat7tqfmq072xt20:ed25519",
            "TxnCount": 1,
            "ConfirmTxn": 
            [
               {
                  "InvokeResult": "Success",
                  "InvokeContextType": "RelayInbound",
                  "Target": "p8mw97q0ve5zywr12ren88gstekb56539n0ry4s1mya2wftjb0yg760n5g:ed25519",
                  "AddressIndex": "@14829735431805717965",
                  "BuildNum": 1,
                  "Timestamp": 1683270863281,
                  "Contract": "Token",
                  "Function": "__relaylambda_2_transfer",
                  "Arguments": {"amount": "184600"},
                  "Height": 5,
                  "ShardIndex": 3,
                  "ShardOrder": 2
               }
            ]
         }
      ]
   }
]`;

enum LOG_TYPE {
   RUN = 'Run',
   DEPLOY = 'Deploy',
   SECTION = 'Section',
   TRACE = 'Trace',
   SHARD = 'Shard',
   ADDR = 'Addr',
   TXN = 'Txn',
   BLOCK = 'Block',
   PROFILING = 'Profiling',
}

type VizLog = {
  type: string
  command?: string
  content: any
}
export const Home = () => {
   // PREDA_VIZ_LOG mockdata
   const originData = json.parse(PREDA_VIZ_LOG.replace(/\\/g, '\\\\') || '[]') as VizLog[]
   const shardOrder = originData[0].content?.ShardOrder
  return (
    <div className="home">
      { originData.map((d, i) => {
          const type = d.type.replace(/(\w)/i, (_, $1) => {
            return $1.toLocaleUpperCase();
          });
          const title = `viz.${type.replace(/(\w)/i, (_, $1) => {
            return $1.toLocaleLowerCase();
          })}`;
          if (type === LOG_TYPE.RUN) {
            return (
               <p className="run" key={type + i}>
                  <span className="key">“Script”: </span>
                  <span className="val">“{d.content.script}”</span>
               </p>
            );
          } 
          if (type === LOG_TYPE.DEPLOY) {
            return (
               <DeployBox data={d.content} title={title} key={type + i} />
            );
          } 
          if (type === LOG_TYPE.ADDR) {
            return (
               <AddrBox data={d.content} title={d.command || title} key={type + i} shardOrder={shardOrder} />
            );
          } 
          if (type === LOG_TYPE.SHARD) {
            return (
               <ShardBox data={d.content} title={d.command || title} key={type + i} shardOrder={shardOrder} />
            );
          } 
          if (type === LOG_TYPE.TXN) {
            return (
               <TxnBox data={d.content} title={d.command || title} key={type + i} />
            );
          } 
          if (type === LOG_TYPE.BLOCK) {
            return (
               <BlockBox data={d.content} title={d.command || title} key={type + i} shardOrder={shardOrder} />
            );
          } 
          if (type === LOG_TYPE.PROFILING) {
            return (
               <ProfingBox data={d.content} title={title} key={type + i} />
            );
          } 
          if (type === LOG_TYPE.SECTION) {
            return <p className="section" key={type + i}>{d.content.toString()}</p>
          } 
          if (type === LOG_TYPE.TRACE) {
            return (
              <div className="box"  key={type + i}>
               <p className="box-title">{d.command || title}</p>
               <div className="box-content">
                  <Tree data={(d.content as any).map((r: any) => {
                     if (!~r.father) {
                        r.father = null;
                     }
                     return r;
                  })} name={String(d.command).replace(/\s|\.|#|\[|\]/g, '') + i} />
               </div>
              </div>
            )
          }
          return (
            <div className="box"  key={type + i}>
               <p className="box-title">{title}</p>
               <div className="box-content">
                  <ReactJson
                     src={(JSON.parse(JSON.stringify(d.content)) as object)}
                     style={{ background: "none" }}
                     displayObjectSize={false}
                     enableClipboard={false}
                     displayDataTypes={false}
                     displayArrayKey={false}
                     collapsed={false}
                     name={false}
                     theme="chalk"
                  />
               </div>
            </div>
          )
        })
      }
    </div>
  );
};
