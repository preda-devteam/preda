import React from "react";
import ReactJson from "@dioxide-js/react-json-view";
import json from "json-bigint";
import Tree from "../../component/Tree";

import './style.scss';
import { DeployBox, AddrBox, ShardBox, TxnBox, BlockBox, ProfingBox } from "@/component/BoxItem";

const { useEffect, useState } = React;
const mockdata = 
[
   {
      "type": "Run",
      "content": 
      {
         "ShardOrder": 2,
         "script": "c:\\Users\\IDEA\\Documents\\GitHub\\oxd_preda\\simulator\\contracts\\Ballot.prdts"
      }
   },
   {
      "type": "Deploy",
      "content": 
      [
         {
            "source" : "Kitty.prd",
            "contract": "KittyBreeding",
            "engine": "PREDA_NATIVE",
            "hash": "mj00d647524yjt0kq8j3w52ef567yv2wb9ty8jtmpw82matt7vd0",
            "finalized": false,
            "implments": [],
            "scopes": 
            {
               "global": "HasState|HasFunction",
               "shard": "HasState|HasFunction",
               "address": "HasState|HasFunction"
            },
            "stateVariables":
            [
               {
                  "name" : "A",
                  "scope" : "address",
                  "dataType" : "UINT"
               },
               {
                  "name" : "B",
                  "scope" : "global",
                  "dataType" : "Map (String : Hash)"
               },
               {
                  "name" : "C",
                  "scope" : "shard",
                  "dataType" : "Array (String)"
               }
            ],
            "structs":
            [
               {
                  "name" : "S",
                  "layout" : [
                     {
                        "identifier" : "S1",
                        "dataType" : "int"
                     },
                     {
                        "identifier" : "S2",
                        "dataType" : "Map (String : Array (Address))"
                     },
                     {
                        "identifier" : "S3",
                        "dataType" : "Struct"
                     }
                  ]
               },
               {
                  "name" : "S1",
                  "layout" : [
                     {
                        "identifier" : "S1",
                        "dataType" : "int"
                     },
                     {
                        "identifier" : "S2",
                        "dataType" : "Map (String : Array (Address))"
                     },
                     {
                        "identifier" : "S3",
                        "dataType" : "Struct"
                     }
                  ]
               }
            ],
            "scatteredMaps": {},
            "enumerators":  
            [
	{
	  "name":"E",
                   "value" : ["E1", "E2", "E3"]
            	},
	{
	  "name":"B",
                   "value" : ["B1", "B2", "B3"]
            	}	
            ],
            "interfaces": {},
            "functions": 
            [
               {
                  "name": "mint",
                  "flag": "InvokeByNormalTransaction|EmitRelayInAddressScope|GlobalStateDependency",
                  "scope": "global",
                  "opcode": 0
               },
               {
                  "name": "breed",
                  "flag": "InvokeByNormalTransaction|EmitRelayInAddressScope|GlobalStateDependency",
                  "scope": "address",
                  "opcode": 1
               },
               {
                  "name": "registerNewBorns",
                  "flag": "InvokeByNormalTransaction|EmitRelayInGlobalScope",
                  "scope": "shard",
                  "opcode": 2
               },
               {
                  "name": "__relaylambda_3",
                  "flag": "InvokeByRelayTransaction",
                  "scope": "address",
                  "opcode": 3
               },
               {
                  "name": "__relaylambda_4",
                  "flag": "InvokeByRelayTransaction|EmitRelayInAddressScope|GlobalStateDependency",
                  "scope": "address",
                  "opcode": 4
               },
               {
                  "name": "__relaylambda_5",
                  "flag": "InvokeByRelayTransaction|EmitRelayInAddressScope|GlobalStateDependency",
                  "scope": "global",
                  "opcode": 5
               },
               {
                  "name": "__relaylambda_6",
                  "flag": "InvokeByRelayTransaction|EmitRelayInAddressScope",
                  "scope": "address",
                  "opcode": 6
               },
               {
                  "name": "__relaylambda_7",
                  "flag": "InvokeByRelayTransaction",
                  "scope": "address",
                  "opcode": 7
               },
               {
                  "name": "__relaylambda_8",
                  "flag": "InvokeByRelayTransaction",
                  "scope": "address",
                  "opcode": 8
               }
            ]
         }
      ]
   },
   {
      "type": "Addr",
      "command": "viz.addr @0",
      "content": 
      [
         {
            "Address": "d5tbzx0kbcwvste7t69d6hwackc5nrhf7a3hjfrk6ye3m54dvns578436g:ed25519",
            "AddressIndex": "@0",
            "ShardIndex": "#1",
            "States": 
            [
               {"Contract": "Ballot", "State": {"weight": 1, "voted_case": 1}},
               {"Contract": "Token", "State": {"balance": "50000000000000"}}
            ]
         }
      ]
   },
   {
      "type": "Trace",
      "command": "viz.trace txn5",
      "content": 
      [
         {
            "tx_id": 1,
            "tx_info": 
            {
               "InvokeContextType": "Normal",
               "Target": "d5tbzx0kbcwvste7t69d6hwackc5nrhf7a3hjfrk6ye3m54dvns578436g:ed25519",
               "AddressIndex": "@0",
               "BuildNum": 1,
               "Timestamp": 1670209209448,
               "Contract": "Ballot",
               "Function": "finalize",
               "Height": 3,
               "ShardIndex": 1,
               "ShardOrder": 2
            },
            "father": -1
         },
         {
            "tx_id": 2,
            "tx_info": 
            {
               "InvokeContextType": "RelayInbound",
               "Initiator": "d5tbzx0kbcwvste7t69d6hwackc5nrhf7a3hjfrk6ye3m54dvns578436g:ed25519",
               "OriginateHeight": 3,
               "OriginateShardIndex": 1,
               "OriginateShardOrder": 2,
               "BuildNum": 1,
               "Timestamp": 1670209221404,
               "Contract": "Ballot",
               "Function": "__relaylambda_4",
               "Height": 4,
               "ShardIndex": "g",
               "ShardOrder": 2
            },
            "father": 1
         },
         {
            "tx_id": 3,
            "tx_info": 
            {
               "InvokeContextType": "Scheduled",
               "Initiator": "d5tbzx0kbcwvste7t69d6hwackc5nrhf7a3hjfrk6ye3m54dvns578436g:ed25519",
               "OriginateHeight": 4,
               "OriginateShardIndex": "g",
               "OriginateShardOrder": 2,
               "BuildNum": 1,
               "Timestamp": 1670209226404,
               "Contract": "Ballot",
               "Function": "__relaylambda_5",
               "Height": 4,
               "ShardIndex": 1,
               "ShardOrder": 2
            },
            "father": 2
         },
         {
            "tx_id": 4,
            "tx_info": 
            {
               "InvokeContextType": "Scheduled",
               "Initiator": "d5tbzx0kbcwvste7t69d6hwackc5nrhf7a3hjfrk6ye3m54dvns578436g:ed25519",
               "OriginateHeight": 4,
               "OriginateShardIndex": "g",
               "OriginateShardOrder": 2,
               "BuildNum": 1,
               "Timestamp": 1670209226404,
               "Contract": "Ballot",
               "Function": "__relaylambda_5",
               "Height": 4,
               "ShardIndex": 2,
               "ShardOrder": 2
            },
            "father": 2
         },
         {
            "tx_id": 5,
            "tx_info": 
            {
               "InvokeContextType": "Scheduled",
               "Initiator": "d5tbzx0kbcwvste7t69d6hwackc5nrhf7a3hjfrk6ye3m54dvns578436g:ed25519",
               "OriginateHeight": 4,
               "OriginateShardIndex": "g",
               "OriginateShardOrder": 2,
               "BuildNum": 1,
               "Timestamp": 1670209226404,
               "Contract": "Ballot",
               "Function": "__relaylambda_5",
               "Height": 4,
               "ShardIndex": 3,
               "ShardOrder": 2
            },
            "father": 2
         },
         {
            "tx_id": 6,
            "tx_info": 
            {
               "InvokeContextType": "Scheduled",
               "Initiator": "d5tbzx0kbcwvste7t69d6hwackc5nrhf7a3hjfrk6ye3m54dvns578436g:ed25519",
               "OriginateHeight": 4,
               "OriginateShardIndex": "g",
               "OriginateShardOrder": 2,
               "BuildNum": 1,
               "Timestamp": 1670209226404,
               "Contract": "Ballot",
               "Function": "__relaylambda_5",
               "Height": 4,
               "ShardIndex": 0,
               "ShardOrder": 2
            },
            "father": 2
         },
         {
            "tx_id": 7,
            "tx_info": 
            {
               "InvokeContextType": "RelayInbound",
               "Initiator": "d5tbzx0kbcwvste7t69d6hwackc5nrhf7a3hjfrk6ye3m54dvns578436g:ed25519",
               "OriginateHeight": 4,
               "OriginateShardIndex": 1,
               "OriginateShardOrder": 2,
               "BuildNum": 1,
               "Timestamp": 1670209226404,
               "Contract": "Ballot",
               "Function": "__relaylambda_6",
               "Arguments": {"shardVotes": [0, 0, 3]},
               "Height": 5,
               "ShardIndex": "g",
               "ShardOrder": 2
            },
            "father": 3
         },
         {
            "tx_id": 8,
            "tx_info": 
            {
               "InvokeContextType": "RelayInbound",
               "Initiator": "d5tbzx0kbcwvste7t69d6hwackc5nrhf7a3hjfrk6ye3m54dvns578436g:ed25519",
               "OriginateHeight": 4,
               "OriginateShardIndex": 2,
               "OriginateShardOrder": 2,
               "BuildNum": 1,
               "Timestamp": 1670209226404,
               "Contract": "Ballot",
               "Function": "__relaylambda_6",
               "Arguments": {"shardVotes": [2, 1, 0]},
               "Height": 5,
               "ShardIndex": "g",
               "ShardOrder": 2
            },
            "father": 4
         },
         {
            "tx_id": 9,
            "tx_info": 
            {
               "InvokeContextType": "RelayInbound",
               "Initiator": "d5tbzx0kbcwvste7t69d6hwackc5nrhf7a3hjfrk6ye3m54dvns578436g:ed25519",
               "OriginateHeight": 4,
               "OriginateShardIndex": 3,
               "OriginateShardOrder": 2,
               "BuildNum": 1,
               "Timestamp": 1670209226404,
               "Contract": "Ballot",
               "Function": "__relaylambda_6",
               "Arguments": {"shardVotes": [0, 2, 1]},
               "Height": 5,
               "ShardIndex": "g",
               "ShardOrder": 2
            },
            "father": 5
         },
         {
            "tx_id": 10,
            "tx_info": 
            {
               "InvokeContextType": "RelayInbound",
               "Initiator": "d5tbzx0kbcwvste7t69d6hwackc5nrhf7a3hjfrk6ye3m54dvns578436g:ed25519",
               "OriginateHeight": 4,
               "OriginateShardIndex": 0,
               "OriginateShardOrder": 2,
               "BuildNum": 1,
               "Timestamp": 1670209226404,
               "Contract": "Ballot",
               "Function": "__relaylambda_6",
               "Arguments": {"shardVotes": [0, 2, 1]},
               "Height": 5,
               "ShardIndex": "g",
               "ShardOrder": 2
            },
            "father": 6
         }
      ]
   },
   {
      "type": "Block",
      "command": "viz.block #0",
      "content": 
      [
         {
            "Height": 0,
            "PrevBlock": "0000000000000000000000000000000000000000000000000000",
            "ShardIndex": "#0",
            "Timestamp": 1670209206404,
            "Miner": "d5tbzx0kbcwvste7t69d6hwackc5nrhf7a3hjfrk6ye3m54dvns578436g:ed25519",
            "TxnCount": 0
         },
         {
            "Height": 1,
            "PrevBlock": "xkhrf474nszvw000000000000000000000000000000000000000",
            "ShardIndex": "#0",
            "Timestamp": 1670209211404,
            "Miner": "d5tbzx0kbcwvste7t69d6hwackc5nrhf7a3hjfrk6ye3m54dvns578436g:ed25519",
            "TxnCount": 0
         },
         {
            "Height": 2,
            "PrevBlock": "x0pfq3vay2knc000000000000000000000000000000000000000",
            "ShardIndex": "#0",
            "Timestamp": 1670209216404,
            "Miner": "d5tbzx0kbcwvste7t69d6hwackc5nrhf7a3hjfrk6ye3m54dvns578436g:ed25519",
            "TxnCount": 3,
            "ConfirmTxn": 
            [
               {
                  "InvokeResult": "Success",
                  "GasBurnt": 1,
                  "InvokeContextType": "Normal",
                  "Target": "7hxtdr1s59xw5af9ynm6ghqf6ppv14hmctbw8736ck102xbd9eds6m8ef4:ed25519",
                  "AddressIndex": "@3",
                  "BuildNum": 1,
                  "Timestamp": 1670209209354,
                  "Contract": "Ballot",
                  "Function": "vote",
                  "Arguments": {"proposal_index": 2, "case_num": 1},
                  "Height": 2,
                  "ShardIndex": 0,
                  "ShardOrder": 2
               },
               {
                  "InvokeResult": "Success",
                  "GasBurnt": 1,
                  "InvokeContextType": "Normal",
                  "Target": "00dzss3pgp0vjjg04yawgxx1z2a1wc524rkzaet6n1bek864tbv16164sg:ed25519",
                  "AddressIndex": "@4",
                  "BuildNum": 1,
                  "Timestamp": 1670209209354,
                  "Contract": "Ballot",
                  "Function": "vote",
                  "Arguments": {"proposal_index": 1, "case_num": 1},
                  "Height": 2,
                  "ShardIndex": 0,
                  "ShardOrder": 2
               },
               {
                  "InvokeResult": "Success",
                  "GasBurnt": 1,
                  "InvokeContextType": "Normal",
                  "Target": "658rgdnxvykneq5fm55k6cq60mdd5s3zx78nhbw4h14znszt9j58646wkm:ed25519",
                  "AddressIndex": "@5",
                  "BuildNum": 1,
                  "Timestamp": 1670209209354,
                  "Contract": "Ballot",
                  "Function": "vote",
                  "Arguments": {"proposal_index": 1, "case_num": 1},
                  "Height": 2,
                  "ShardIndex": 0,
                  "ShardOrder": 2
               }
            ]
         }
      ]
   },
   {
      "type": "Block",
      "command": "viz.block #2:1",
      "content": 
      [
         {
            "Height": 1,
            "PrevBlock": "xkhrf474nszvw000000000000000000000000000000000000000",
            "ShardIndex": "#2",
            "Timestamp": 1670209211404,
            "Miner": "d5tbzx0kbcwvste7t69d6hwackc5nrhf7a3hjfrk6ye3m54dvns578436g:ed25519",
            "TxnCount": 0
         }
      ]
   },
   {
      "type": "Txn",
      "command": "viz.txn txn1",
      "content": 
      [
         {
            "InvokeContextType": "Normal",
            "Target": "d5tbzx0kbcwvste7t69d6hwackc5nrhf7a3hjfrk6ye3m54dvns578436g:ed25519",
            "AddressIndex": "@0",
            "BuildNum": 1,
            "Timestamp": 1670209209301,
            "Contract": "Ballot",
            "Function": "init",
            "InvokeResult": "Success",
            "Arguments": {"names": ["Spring", "Yarn", "Combat"]},
            "Height": 0,
            "ShardIndex": 1,
            "ShardOrder": 2
         }
      ]
   },
   {
      "type": "Txn",
      "command": "viz.txn txn2[]",
      "content": 
      [
         {
            "InvokeContextType": "Normal",
            "Target": "d5tbzx0kbcwvste7t69d6hwackc5nrhf7a3hjfrk6ye3m54dvns578436g:ed25519",
            "AddressIndex": "@0",
            "BuildNum": 1,
            "Timestamp": 1670209209354,
            "Contract": "Ballot",
            "Function": "vote",
            "InvokeResult": "Success",
            "Arguments": {"proposal_index": 2, "case_num": 1},
            "Height": 2,
            "ShardIndex": 1,
            "ShardOrder": 2
         },
         {
            "InvokeContextType": "Normal",
            "Target": "qya8a6f9w2ycsah7wgdyc7n5c72sd20t1g24b099pp3d9v6ksawt7xx28r:ed25519",
            "AddressIndex": "@1",
            "BuildNum": 1,
            "Timestamp": 1670209209354,
            "Contract": "Ballot",
            "Function": "vote",
            "InvokeResult": "Success",
            "Arguments": {"proposal_index": 1, "case_num": 1},
            "Height": 2,
            "ShardIndex": 2,
            "ShardOrder": 2
         },
         {
            "InvokeContextType": "Normal",
            "Target": "gjc4jh910hbxad3tn0264t9xagrdsrsqy45n51pavm9drswetj0q65fmjc:ed25519",
            "AddressIndex": "@2",
            "BuildNum": 1,
            "Timestamp": 1670209209354,
            "Contract": "Ballot",
            "Function": "vote",
            "InvokeResult": "Success",
            "Arguments": {"proposal_index": 1, "case_num": 1},
            "Height": 2,
            "ShardIndex": 3,
            "ShardOrder": 2
         },
         {
            "InvokeContextType": "Normal",
            "Target": "7hxtdr1s59xw5af9ynm6ghqf6ppv14hmctbw8736ck102xbd9eds6m8ef4:ed25519",
            "AddressIndex": "@3",
            "BuildNum": 1,
            "Timestamp": 1670209209354,
            "Contract": "Ballot",
            "Function": "vote",
            "InvokeResult": "Success",
            "Arguments": {"proposal_index": 2, "case_num": 1},
            "Height": 2,
            "ShardIndex": 0,
            "ShardOrder": 2
         },
         {
            "InvokeContextType": "Normal",
            "Target": "00dzss3pgp0vjjg04yawgxx1z2a1wc524rkzaet6n1bek864tbv16164sg:ed25519",
            "AddressIndex": "@4",
            "BuildNum": 1,
            "Timestamp": 1670209209354,
            "Contract": "Ballot",
            "Function": "vote",
            "InvokeResult": "Success",
            "Arguments": {"proposal_index": 1, "case_num": 1},
            "Height": 2,
            "ShardIndex": 0,
            "ShardOrder": 2
         },
         {
            "InvokeContextType": "Normal",
            "Target": "658rgdnxvykneq5fm55k6cq60mdd5s3zx78nhbw4h14znszt9j58646wkm:ed25519",
            "AddressIndex": "@5",
            "BuildNum": 1,
            "Timestamp": 1670209209354,
            "Contract": "Ballot",
            "Function": "vote",
            "InvokeResult": "Success",
            "Arguments": {"proposal_index": 1, "case_num": 1},
            "Height": 2,
            "ShardIndex": 0,
            "ShardOrder": 2
         },
         {
            "InvokeContextType": "Normal",
            "Target": "94zvha23xzcc0m987np0e0847x1me7qp72bt8s8jmpbqta5bs52n61gk04:ed25519",
            "AddressIndex": "@6",
            "BuildNum": 1,
            "Timestamp": 1670209209354,
            "Contract": "Ballot",
            "Function": "vote",
            "InvokeResult": "Success",
            "Arguments": {"proposal_index": 0, "case_num": 1},
            "Height": 2,
            "ShardIndex": 2,
            "ShardOrder": 2
         },
         {
            "InvokeContextType": "Normal",
            "Target": "wb2s0az0sgy44pbw3v4hatpwm6vgc5d0ad0287y8spt1yagg4tnn6t8bpm:ed25519",
            "AddressIndex": "@7",
            "BuildNum": 1,
            "Timestamp": 1670209209354,
            "Contract": "Ballot",
            "Function": "vote",
            "InvokeResult": "Success",
            "Arguments": {"proposal_index": 2, "case_num": 1},
            "Height": 2,
            "ShardIndex": 3,
            "ShardOrder": 2
         },
         {
            "InvokeContextType": "Normal",
            "Target": "02kesb1f2mbf4j561b0n3b73evxjst90rkfw86wtj4vbh5esv0cm6s4xj8:ed25519",
            "AddressIndex": "@8",
            "BuildNum": 1,
            "Timestamp": 1670209209354,
            "Contract": "Ballot",
            "Function": "vote",
            "InvokeResult": "Success",
            "Arguments": {"proposal_index": 0, "case_num": 1},
            "Height": 2,
            "ShardIndex": 2,
            "ShardOrder": 2
         },
         {
            "InvokeContextType": "Normal",
            "Target": "t8tjthk6fkb6da6j2mjansqackxwn5jss97tdmq0c860vthvfbqv6h2mkw:ed25519",
            "AddressIndex": "@9",
            "BuildNum": 1,
            "Timestamp": 1670209209354,
            "Contract": "Ballot",
            "Function": "vote",
            "InvokeResult": "Success",
            "Arguments": {"proposal_index": 1, "case_num": 1},
            "Height": 2,
            "ShardIndex": 3,
            "ShardOrder": 2
         },
         {
            "InvokeContextType": "Normal",
            "Target": "ykb16zkm3nk5ejh7np83f2tfg3x9bnbpbhg3v2qhdqddbhtvhfg26nsw2g:ed25519",
            "AddressIndex": "@10",
            "BuildNum": 1,
            "Timestamp": 1670209209354,
            "Contract": "Ballot",
            "Function": "vote",
            "InvokeResult": "Success",
            "Arguments": {"proposal_index": 2, "case_num": 1},
            "Height": 2,
            "ShardIndex": 1,
            "ShardOrder": 2
         },
         {
            "InvokeContextType": "Normal",
            "Target": "tqhmw4kzfyy2pgygqdxf928an5sgv3h6tk5r4a7hnmae4jvsscc578h47r:ed25519",
            "AddressIndex": "@11",
            "BuildNum": 1,
            "Timestamp": 1670209209354,
            "Contract": "Ballot",
            "Function": "vote",
            "InvokeResult": "Success",
            "Arguments": {"proposal_index": 2, "case_num": 1},
            "Height": 2,
            "ShardIndex": 1,
            "ShardOrder": 2
         }
      ]
   },
   {
      "type": "Shard",
      "command": "viz.shard #all Ballot",
      "content": 
      [
         {
            "ShardIndex": "#0",
            "States": [{"Contract": "Ballot", "State": {"votedWeights": [0, 2, 1]}}]
         },
         {
            "ShardIndex": "#1",
            "States": [{"Contract": "Ballot", "State": {"votedWeights": [0, 0, 3]}}]
         },
         {
            "ShardIndex": "#2",
            "States": [{"Contract": "Ballot", "State": {"votedWeights": [2, 1, 0]}}]
         },
         {
            "ShardIndex": "#3",
            "States": [{"Contract": "Ballot", "State": {"votedWeights": [0, 2, 1]}}]
         }
      ]
   },
   {
      "type": "Shard",
      "command": "viz.shard #g",
      "content": 
      [
         {
            "ShardIndex": "#g",
            "States": 
            [
               {
                  "Contract": "Ballot",
                  "State": 
                  {
                     "controller": "0000000000000000000000000000000000000000000000000000000000:unknown",
                     "current_case": 1,
                     "proposals": 
                     [
                        {"name": "Spring", "totalVotedWeight": 2},
                        {"name": "Yarn", "totalVotedWeight": 5},
                        {"name": "Combat", "totalVotedWeight": 5}
                     ],
                     "last_result": {"topVoted": "Yarn", "case": 1},
                     "shardGatherRatio": 2147483648
                  }
               }
            ]
         }
      ]
   },
   {
      "type": "Shard",
      "command": "viz.shard #0",
      "content": 
      [
         {
            "ShardIndex": "#0",
            "States": [{"Contract": "Ballot", "State": {"votedWeights": [0, 2, 1]}}]
         }
      ]
   },
   {
      "type": "Profing",
      "content": 
      [
         {
           BlockHeight: 4,
           TxnCount: 999999,
           TPS: 466.86,
           ShardIndex: 1,
         },
         {
           BlockHeight: 5,
           TxnCount: 999999,
           TPS: 466.86,
           ShardIndex: 1,
         }
       ]
   },
];

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
   const originData = (PREDA_VIZ_LOG || []) as VizLog[]
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
                     src={(d.content as object)}
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
