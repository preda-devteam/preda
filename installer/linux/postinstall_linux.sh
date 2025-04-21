#! /bin/bash -e

bold=$(tput bold)
normal=$(tput sgr0)
install_path=/opt/PREDA
ldconfig
chmod -R 777 ${install_path}
cp -a ${install_path}/bin/libantlr4-runtime.so* /usr/lib/
valid_option=false
while [ "$valid_option" = false ]; do
    echo "${bold}Do you want to install Wasmtime:${normal}"
    echo "0=Yes"
    echo "1=No"

    read -p "${bold}Please input option:${bold}" option

    if [ "$option" = "0" ]; then
        echo '{"wasm": true}' > ${install_path}/bin/config.json
        valid_option=true
    elif [ "$option" = "1" ]; then
        echo '{"wasm": false}' > ${install_path}/bin/config.json
        valid_option=true
    else
        echo "${bold}invalid option, please input '0' or '1'${normal}"
    fi
done

echo "PREDA Installed. Please run '${bold}bash ${install_path}/scripts/register_linux.sh${normal}' to register PREDA extension on VSCode."
echo "you can run '${bold}code ${install_path}/examples${normal}' open example folder or '${bold} code ${install_path}/docs/toolchain_user_manual.md${normal}' open user manual."