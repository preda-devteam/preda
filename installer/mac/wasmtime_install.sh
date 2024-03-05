#! ENV /bin/bash
bold=$(tput bold)
normal=$(tput sgr0)
if [ "$EUID" -ne 0 ]; then
    echo "Please run this script with sudo or as root."
    exit 1
fi
valid_option=false
while [ "$valid_option" = false ]; do
    echo "${bold}Do you want to install Wasmtime:${normal}"
    echo "0=Yes"
    echo "1=No"

    printf "${bold}Please input option:${bold}"
    read option
    #read -p "${bold}Please input option:${bold}" option

    if [ "$option" = "0" ]; then
        echo '{"wasm": true}' > /Applications/PREDA/bin/config.json
        valid_option=true
    elif [ "$option" = "1" ]; then
        echo '{"wasm": false}' > /Applications/PREDA/bin/config.json
        valid_option=true
    else
        echo "${bold}invalid option, please input '0' or '1'${normal}"
    fi
done

