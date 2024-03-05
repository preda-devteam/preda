#! /bin/bash
version=$1
name=preda-toolchain
# cur_dir=$(dirname "$(readlink -f "$0")")
echo $(pwd)
set -e
pkg=$(ls -t ./bundle/$name*.pkg |head -n 1)
echo ${pkg}
if [ -f ${pkg} ];then

    if [ -d ./bundle/${name} ];then
        rm -rf ./bundle/${name}
    fi
    mkdir -p ./bundle/${name}/docs
    cp ${pkg} ./bundle/${name}/
    cp -r ./docs/*.pdf ./bundle/${name}/docs
    cp installer/mac/{register_mac.sh,wasmtime_install.sh} ./bundle/${name}/
    hdiutil create -volname ${name}_${version} -fs HFS+ -imagekey zlib-level=9 -srcfolder ./bundle/$name ./bundle/${name}_${version}.dmg
    Rez -append installer/mac/logo.rsrc -o ./bundle/${name}_${version}.dmg
    SetFile -a C ./bundle/${name}_${version}.dmg
else
    echo "can not find preda-toolchain.pkg in $(pwd)/bundle"
fi
