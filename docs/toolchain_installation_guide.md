# PREDA-Toolchain Installation Guide

## 1. System Requirements

- **Windows:** Windows 10 (21H2) or above 
- **Linux:** Ubuntu 18.04.6 LTS or above 
- **macOS:** Ventura or above

## 2.Prerequisites

### 2.1 Windows

- Visual Studio Code 1.53 or above (must be installed using the installer, portable version not supported)

### 2.2 Linux

- Visual Studio Code 1.53 or above (must be installed using the .deb package)
- g++ 8.1 or above

### 2.3 macOS

- Visual Studio Code 1.53 or above
- Install 'code' command in PATH (Follow instructions here: https://code.visualstudio.com/docs/setup/mac#_launching-from-the-command-line)

## 3. Downloads

Download [PREDA-Toolchain](https://github.com/preda-devteam/preda/releases/latest) - PREDA Language Preview Toolchain

## 4. Installation Steps

### 4.1 Windows

Run installer and follow the prompts through the install.

### 4.2 Linux

**Run the following command to install the .deb package.**

```bash
sudo dpkg -i preda-toolchain_*_amd64.deb
```

**Register PREDA Language Toolchain VS Code plugin.**

```bash
bash /opt/PREDA/scripts/register.sh
```

### 4.3 macOS

Open installer package and follow the instructions.

## 5. Samples Contract and Documents

The **examples** subfolder of the installation folder includes several sample files for you to start with.

There are two documents in the **doc** subfolder:

- **PREDA Language Specification.** Reference manual for PREDA language.
- **Chain Simulator Script Manual.** User Manual for writing PREDA test scripts in VS Code to compile / deploy / run contracts using Chain Simulator

For a guide on how to use the PREDA Language Preview Toolchain plugin for VS Code, check the plugin's **Details** page in VS Code.

## 6. Troubleshooting

**Visual Studio Code is not installed**

Visit https://code.visualstudio.com/Download and download the installer for your platform.

**g++ version is too low (Linux)**

First Install g++-9

```bash
sudo apt-get install g++-9
```

Then set g++-9 as the default g++

```bash
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 100
```
