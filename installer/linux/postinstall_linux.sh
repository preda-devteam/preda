#! /bin/bash -e

bold=$(tput bold)
normal=$(tput sgr0)

ldconfig
chmod -R 777 /opt/PREDA
echo "PREDA Installed. Please run '${bold}bash /opt/PREDA/scripts/register_linux.sh${normal}' to register PREDA extension on VSCode."
echo "you can run '${bold}code /opt/PREDA/examples${normal}' open example folder."