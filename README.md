# PREDA: A General Programming Language for Parallel Execution of Smart Contract Transactions

**Parallel Relay-and-Execution Distributed Architecture** (PREDA) is the smart contract language for defining states and transaction logic that are executed on a parallel multi-chain architecture with relayed execution. 

## Table of content

- [Background](#background)
- [Build PREDA](#build-preda)
    - [Init git submodule](#init-git-submodule)
    - [Install Xmake](#install-xmake)
    - [Build](#build)
        - [Windows](#windows)
        - [Linux](#linux)
        - [MacOS](#macos)
- [Package PREDA](#package-preda)
    - [Install package tools](#install-package-tools)
    - [Package preda-toolchain](#package-preda-toolchain)

- [How to use preda-toolchain](#how-to-use-preda-toolchain)
    - [Simple Example](#simple-example)
    - [More tutorials](#more-tutorials)

- [Trouble Shooting](#trouble-shooting)
- [Acknowledgements](#acknowledgements)

## Background

Sharding blockchains allow payment transactions to be executed in parallel by multiple shards of the chains. In this way, sharding blockchains can improve the transaction throughput and state capacity for payment transactions. In order to extend such capability to general smart contract transactions, we introduce PREDA, Parallel Relay Execution Distributed Architecture, and its language to define how contract states can be efficiently divided into shards and how logic flow of contract functions can be executed asynchronously across all shards. Programmers can use PREDA to implement smart contracts and the sharding blockchain systems that support PREDA can execute transactions invoking PREDA smart contracts in parallel.

## Build PREDA

### Init git submodule

```
git submodule update --init
```

### Install Xmake

check <https://xmake.io/#/guide/installation> for more detail

### Build

#### Windows

- install visual studio 2019
- install windows sdk
- at the root of this repo execute:
    - `xmake f -m debug`
    - `xmake`

#### Linux

- install dependencies(for ubuntu you can run `sudo apt install p7zip-full pkg-config cmake libx11-dev uuid-dev libgflags-dev libsnappy-dev zlib1g-dev libbz2-dev liblz4-dev libzstd-dev g++-9 gcc-9`)
- at the root of this repo execute:
    - `xmake f -m debug`
    - `xmake`

#### MacOS

- install 7zip(`brew install p7zip`)
- install xcode and clang
- at the root of this repo execute:
    - `xmake f -m debug`
    - `xmake`

you can find the artifact under the - `build/PREDA` folder

## Package PREDA

### Install package tools

| OS      | Tools          | Links                                               |
| ------- | -------------- | --------------------------------------------------- |
| Windows | **Inno Setup** | https://jrsoftware.org/isinfo.php                   |
| Linux   | **dpkg-deb**   | Come with System                                    |
| Mac     | **Packages**   | http://s.sudre.free.fr/Software/Packages/about.html |

### Package preda-toolchain

at the root of this repo execute `xmake p`, then you can find the package under the - `bundle` folder.

## How to use preda-toolchain

you can run the preda-toolchain after build it or install the preda-toolchain package.

### Simple Example

you can find the preda-toolchain at the `build/PREDA` folder after you build it. 

```bash
➜ cd build/PREDA/bin
➜ pwd                   
~/preda_repo/build/PREDA/bin
➜ ./chsimu ../examples/Ballot.prdts -count:100
...
...
Order: 2, TPS:25250, uTPS:27500
Shd#g:  h:5 txn:0/0/6 addr:0
Shd#0:  h:5 txn:0/0/26 addr:25
Shd#1:  h:5 txn:0/0/26 addr:25
Shd#2:  h:5 txn:0/0/28 addr:25
Shd#3:  h:5 txn:0/0/26 addr:25
Total Txn:0/112
```

### More tutorials

Learn more about how to use it through the documentation at `docs`.

## Trouble Shooting

### why I delete whole directory and clone, compile again, it said that missing "ippccmt.lib"

delete cache files:

Windows: `preda-repo/.xmake` ，`preda-repo/build`，`%localappdata%/.xmake` 

Linux/Mac:`preda-repo/.xmake` ，`preda-repo/build`，`~/.xmake` 

then re-run `xmake`

## Acknowledgements

PREDA uses the following open source libraries as the components. The acknowledgements pertain to the corresponding software license.

### Intel Integrated Performance Primitives
https://www.intel.com/content/www/us/en/developer/tools/oneapi/ipp.html  
License: Intel Simplified Software License  
Copyright 1999-2020 Intel Corporation

### 7-Zip
https://github.com/dantmnf/7-zip  
License: Public Domain  
Author: Igor Pavlov

### TTMath Bignum Library
https://www.ttmath.org/  
License: BSD licence  
Copyright (c) 2006-2012, Tomasz Sowa

### Botan: Crypto and TLS for Modern C++
https://botan.randombit.net/  
License: Simplified BSD License  
(C) 1999-2020 The Botan Authors

### moodycamel::ConcurrentQueue
https://github.com/cameron314/concurrentqueue  
License: Simplified BSD License  
Copyright (c) 2013-2016, Cameron Desrochers

### C++ Mathematical Expression Toolkit Library
http://www.partow.net/programming/exprtk/index.html  
License: MIT License  
Copyright Arash Partow (1999-2018)

### RocksDB
https://github.com/facebook/rocksdb  
License:  GPLv2 and Apache 2.0 License  
Copyright (c) 2011-present, Facebook, Inc

### sparsehash
https://github.com/sparsehash/sparsehash  
License:  BSD-3-Clause license  
Copyright (c) 2007, Google Inc

### zlib
https://github.com/sparsehash/sparsehash  
License:  [zlib License](https://github.com/madler/zlib/blob/master/LICENSE)  
Copyright (C) 1995-2007 Mark Adler

### libsodium
https://github.com/jedisct1/libsodium  
License: ISC License  
Copyright (c) 2013-2015, Frank Denis <j@pureftpd.org>

### ANTLR
https://github.com/antlr/antlr4  
License: BSD-3-Clause license  
Copyright (c) 2012-2022 The ANTLR Project.

### dayjs
https://github.com/iamkun/dayjs  
License: MIT License  
Copyright (c) 2018-present, iamkun

### ejs
https://github.com/mde/ejs  
License: Apache License  
Copyright 2112 mde@fleegix.org

### fs-extra
https://github.com/jprichardson/node-fs-extra  
License: MIT License  
Copyright (c) 2011-2017 JP Richardson

### mustache
https://github.com/janl/mustache.js  
License: MIT License  
Copyright (c) 2010-2015 The mustache.js community
