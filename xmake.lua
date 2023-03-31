add_rules("mode.debug", "mode.release")
includes("xmake_rules.lua")

package("ipp")
    if is_plat("windows") then
        add_urls("https://github.com/preda-devteam/preda/releases/download/SFC-Libs/sfc_win_ipp.7z")
        add_versions("1.0", "C22F7310AB7679A0E11A57BB96D6A0483230DA4FB4A0D88D53EF6DB2419C73A4")
    elseif is_plat("linux") then
        add_urls("https://github.com/preda-devteam/preda/releases/download/SFC-Libs/sfc_linux_ipp.7z")
        add_versions("1.0", "004B15DD58EBBF945103786F6BF8509968DEA43A7EC3F01E8551F2463C9D6D3C")
    elseif is_plat("macosx") then
        add_urls("https://github.com/preda-devteam/preda/releases/download/SFC-Libs/sfc_mac_ipp.7z")
        add_versions("1.0", "9417ad9a5bf702c0cc2f41ab3629fac23998a931f5f09c1d0d849f43f577ee9a")
    end
    on_install("windows", "linux", "macosx", function(package)
        if is_plat("windows") then
            os.cp("*", path.join(os.scriptdir(), "SFC", "libs", "win"))
        elseif is_plat("linux") then
            os.cp("*", path.join(os.scriptdir(), "SFC", "libs", "linux"))
        else
            os.cp("*", path.join(os.scriptdir(), "SFC", "libs", "mac"))
        end
    end)
package_end()



-- static library
add_requires("ipp latest")

package("wasmtime")
    if is_plat("windows") then
        add_urls("https://github.com/preda-devteam/preda/releases/download/wasmtime/wasmtime-x86_64-windows-c-api.7z")
        add_versions("1.0", "f6173b17d8848ac8ccddb1e8f5cc7517ad9847a539856216cebce6d1e0cf651b")
    elseif is_plat("linux") then
        add_urls("https://github.com/preda-devteam/preda/releases/download/wasmtime/wasmtime-x86_64-linux-c-api.7z")
        add_versions("1.0", "839899455a9e97fe82b61478f22619ed8877d4dcfc1ae7743026d6197825b80f")
    elseif is_plat("macosx") then
        add_urls("https://github.com/preda-devteam/preda/releases/download/wasmtime/wasmtime-x86_64-macos-c-api.7z")
        add_versions("1.0", "d70c8be5757ac1c45bbd8d1673eb2d5fd51bee2a21bbfe060a9c880ba5a3dd10")
    end
    on_install("windows", "linux", "macosx", function(package)
        os.mkdir(path.join(os.scriptdir(), "oxd_preda", "3rdParty", "wasmtime"))
        os.cp("*", path.join(os.scriptdir(), "oxd_preda", "3rdParty", "wasmtime"))
    end)
package_end()

add_requires("wasmtime latest")

if is_plat("windows") then
    package("mingw64")
        add_urls("https://github.com/preda-devteam/preda/releases/download/mingw64/x86_64-8.1.0-release-win32-seh-rt_v6-rev0.7z")
        add_versions("8.1.0", "73797b9a1d0b007dbdd6f010e6064dc0aa4df835b042f6947f73a3bf9cc348c5")
        on_install(function(package)
            os.mkdir(path.join(os.scriptdir(), "oxd_preda", "bin", "mingw64"))
            os.cp("*", path.join(os.scriptdir(), "oxd_preda", "bin", "mingw64"))
        end)
    package_end()
    add_requires("mingw64 latest")
end

package("emscripten")
    if is_plat("windows") then
        add_urls("https://github.com/preda-devteam/preda/releases/download/emscripten/emscripten-3.1.24-win-x64.7z")
        add_versions("3.1.24", "6497b23c41204c36fe3c332ac147b3176a5764d3d80f6e1c6ddeb7e38b2918fc")
    elseif is_plat("linux") then
        add_urls("https://github.com/preda-devteam/preda/releases/download/emscripten/emscripten-3.1.24-linux-x64.7z")
        add_versions("3.1.24", "624c89303bc6a0d3d512a0d880bc10ffab55c3fc040d45167211de91183e585e")
    elseif is_plat("macosx") then
        add_urls("https://github.com/preda-devteam/preda/releases/download/emscripten/emscripten-3.1.24-mac-x64.7z")
        add_versions("3.1.24", "d9d7397f3a36ad4b57d848ae7aca6d3c929e43850ddc9afd7106453bd3af886c")
    end
    on_install("windows", "linux", "macosx", function(package)
        os.mkdir(path.join(os.scriptdir(), "oxd_preda", "bin", "emscripten"))
        os.mkdir(path.join(os.scriptdir(), "oxd_preda", "bin", "emscripten", "3.1.24"))
        os.cp("*", path.join(os.scriptdir(), "oxd_preda", "bin", "emscripten", "3.1.24"))
    end)
package_end()

add_requires("emscripten latest")

package("solc")
    if is_plat("windows") then
        add_urls("https://github.com/ethereum/solidity/releases/download/$(version)/solc-windows.exe")
        add_versions("v0.8.18", "3413d777e5a08e7240c5dc7e6a61afbc5fb78949ba0aa81ca3c9e9ad31d03490")
    elseif is_plat("linux") then
        add_urls("https://github.com/ethereum/solidity/releases/download/$(version)/solc-static-linux")
        add_versions("v0.8.18", "95e6ed4949a63ad89afb443ecba1fb8302dd2860ee5e9baace3e674a0f48aa77")
    elseif is_plat("macosx") then
        add_urls("https://github.com/ethereum/solidity/releases/download/$(version)/solc-macos")
        add_versions("v0.8.18", "8f15287c799ad2b33f241d1252226abda5d4bc3ef6be40b946923178fc57d397")
    end
    on_install("windows", "linux", "macosx", function(package)
        os.mkdir(path.join(os.scriptdir(), "oxd_preda", "bin", "solc"))
        if is_plat("windows") then
            os.cp("./../solc-windows.exe", path.join(os.scriptdir(), "oxd_preda", "bin", "solc"))
        elseif is_plat("linux") then
            os.cp("./../solc-static-linux", path.join(os.scriptdir(), "oxd_preda", "bin", "solc"))
        else
            os.cp("./../solc-macos", path.join(os.scriptdir(), "oxd_preda", "bin", "solc"))
        end
        
    end)
package_end()
-- static library
add_requires("solc v0.8.18")

-- general config for platform
if (is_plat("windows")) then
    set_toolchains("msvc", {vs = "2019"})
    add_defines("UNICODE", "_UNICODE")
    if is_mode("debug") then
        set_runtimes("MTd")
    else
        set_runtimes("MT")
    end
elseif (is_plat("linux")) then
    set_toolchains("gcc-9")
elseif (is_plat("macosx")) then
    add_frameworks("Foundation", "AppKit", "IOKit", "Security")
    add_cxflags("-target x86_64-apple-macos10.14")
    add_shflags("-target x86_64-apple-macos10.14")
end

-- antlr setting for non windows platform
if (not is_plat("windows")) then 
    package("antlr4")
        add_deps("cmake") 
        set_sourcedir(path.join(os.scriptdir(), "oxd_preda", "3rdParty", "antlr4", "runtime", "Cpp"))
        on_install(function (package)
            local configs = { }
            table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:debug() and "Debug" or "Release"))
            table.insert(configs, "-DBUILD_SHARED_LIBS=ON")
            table.insert(configs, "-DCMAKE_COLOR_MAKEFILE=OFF")
            table.insert(configs, "-DCMAKE_COLOR_DIAGNOSTICS=OFF")
            if (is_plat("macosx")) then
                table.insert(configs, "-DCMAKE_OSX_DEPLOYMENT_TARGET=10.14")
            end
            import("package.tools.cmake").install(package, configs)
            os.cp(package:installdir("lib", "*"), "$(projectdir)/build/PREDA/bin/")
        end)
    package_end()
    add_requires("antlr4")
end

target("oxd_libsec")
    set_kind("static")
    set_languages("cxx17")
    set_targetdir(path.join("$(buildir)", "PREDA", "bin"))
    add_packages("ipp SFC-Libs")
    if (is_plat("windows")) then
        add_defines("_CONSOLE")
        add_linkdirs("SFC/libs/win")
        if is_mode("debug") then
            set_basename("oxd_libsec_d")
        end
    elseif (is_plat("linux")) then
        add_rules("linux.link_ipp")
        add_cxflags("-fPIC", "-pthread", "-ldl", "-lX11")
    else
        add_files("SFC/libs/mac/*.a")
        add_files("SFC/core/os/objc_wrap.mm")
    end 
    add_includedirs("SFC")
    add_includedirs("SFC/core/ext/botan/")
    add_includedirs("oxd_libsec/src")
    add_includedirs("oxd_libsec/src/libsodium/libsodium/src/libsodium/include/sodium")
    add_files("SFC/essentials.cpp")
    add_files("SFC/core/ext/botan/botan.cpp")
    add_files("oxd_libsec/src/*.cpp") 
    add_files("oxd_libsec/src/libsodium/*.cpp")
    set_policy("build.merge_archive", true)

if (is_plat("windows")) then
    target("antlr4-runtime")
        set_kind("static")
        set_languages("cxx17")
        set_targetdir(path.join("$(buildir)", "PREDA", "bin"))
        add_defines("ANTLR4CPP_STATIC")
        add_includedirs("oxd_preda/3rdParty/antlr4/runtime/Cpp/runtime/src/support")
        add_includedirs("oxd_preda/3rdParty/antlr4/runtime/Cpp/runtime/src/tree")
        add_includedirs("oxd_preda/3rdParty/antlr4/runtime/Cpp/runtime/src/misc")
        add_includedirs("oxd_preda/3rdParty/antlr4/runtime/Cpp/runtime/src/tree/pattern")
        add_includedirs("oxd_preda/3rdParty/antlr4/runtime/Cpp/runtime/src/dfa")
        add_includedirs("oxd_preda/3rdParty/antlr4/runtime/Cpp/runtime/src")
        add_includedirs("oxd_preda/3rdParty/antlr4/runtime/Cpp/runtime/src/atn")
        add_includedirs("oxd_preda/3rdParty/antlr4/runtime/Cpp/runtime/src/tree/xpath")
        add_files("oxd_preda/3rdParty/antlr4/runtime/Cpp/runtime/src/**.cpp")
end

target("transpiler")
    set_kind("shared")
    set_languages("cxx17")
    add_deps("oxd_libsec")
    set_targetdir(path.join("$(buildir)", "PREDA", "bin"))
    if (is_plat("windows")) then
        add_links("antlr4-runtime")
        add_rules("win.sdk")
    elseif (is_plat("linux")) then
        add_cxflags("-fPIC", "-pthread", {force = true})
        add_shflags("-pthread", "-ldl", "-lX11")
        add_rules("linux.link_ipp")
        add_links("antlr4-runtime")
        before_link(function (target)
            target:add("files", path.join("$(buildir)", "PREDA", "bin", "libantlr4-runtime.a"))
        end)
        set_filename("transpiler.so")
    elseif (is_plat("macosx")) then
        add_links("antlr4-runtime")
        add_files("SFC/libs/mac/*.a")
        set_filename("transpiler.dylib")
    end 
    add_defines("ANTLR4CPP_STATIC")
    add_includedirs("oxd_preda/3rdParty/antlr4/runtime/Cpp/runtime/src")
    add_includedirs("oxd_preda/transpiler")
    add_includedirs("oxd_preda/transpiler/transpiler")
    add_includedirs("oxd_preda/transpiler/antlr_generated")
    add_files("oxd_preda/transpiler/*.cpp")
    add_files("oxd_preda/transpiler/transpiler/*.cpp")
    add_files("oxd_preda/transpiler/antlr_generated/*.cpp")
    set_policy("build.merge_archive", true)

target("preda_engine")
    set_kind("shared")
    add_includedirs("oxd_preda/3rdParty/wasmtime/include")
    add_linkdirs("oxd_preda/3rdParty/wasmtime/lib")
    add_includedirs("oxd_preda/3rdParty/evmc/include")
    add_rpathdirs("./")
    set_languages("cxx17")
    add_deps("oxd_libsec")
    set_targetdir(path.join("$(buildir)", "PREDA", "bin"))
    if (is_plat("windows")) then
        add_includedirs("oxd_preda/3rdParty/evmone/win/include")
        add_linkdirs("oxd_preda/3rdParty/evmone/win/lib")
        add_defines("_WINDLL")
        add_cxflags("/bigobj", {force = true})
        add_files("SFC/core/ext/bignum/ttmath/ttmathuint_x86_64_msvc.asm")
        add_rules("win.sdk")
        add_linkdirs("SFC/libs/win")
        add_links("wasmtime.dll")
        add_links("evmone")
    elseif (is_plat("linux")) then
        add_includedirs("oxd_preda/3rdParty/evmone/linux/include")
        add_linkdirs("oxd_preda/3rdParty/evmone/linux/lib")
        add_packages("antlr4") 
        add_cxflags("-fPIC", "-pthread", "-ldl", "-lX11")
        add_rules("linux.link_ipp")
        set_filename("preda_engine.so")
        add_links("wasmtime")
        add_links("evmone")
    elseif (is_plat("macosx")) then
        add_includedirs("oxd_preda/3rdParty/evmone/darwin/include")
        add_linkdirs("oxd_preda/3rdParty/evmone/darwin/lib")
        add_packages("antlr4") 
        add_files("SFC/libs/mac/*.a")
        add_files("SFC/core/os/objc_wrap.mm")
        set_filename("preda_engine.dylib")
        add_links("wasmtime")
        add_links("evmone")
    end 
    add_includedirs("SFC/core/ext/rocksdb")
    add_includedirs("oxd_preda/native/abi")
    add_includedirs("oxd_preda/engine/preda_engine")
    add_files("SFC/core/ext/bignum/big_num.cpp")
    add_files("SFC/core/ext/bignum/precision_num.cpp")
    add_files("SFC/core/ext/lib_inc.c")
    add_files("SFC/core/ext/rocksdb/rocksdb.cpp")
    add_files("SFC/essentials.cpp")
    add_files("oxd_preda/native/types/data_jsonifer.cpp")
    add_files("oxd_preda/native/types/blob.cpp")
    add_files("oxd_preda/native/types/data.cpp")
    add_files("oxd_preda/engine/preda_engine/*.cpp")
    add_files("oxd_preda/engine/evm_engine/*.cpp")
    remove_files("oxd_preda/util/sdkgen/main.cpp")
    remove_files("oxd_preda/engine/preda_engine/RuntimeInterfaceImpl_debug.cpp")
    set_policy("build.merge_archive", true)

target("chain_simulator")
    set_kind("binary")
    set_languages("cxx17")
    set_targetdir(path.join("$(buildir)", "PREDA", "bin"))
    set_basename("chsimu")
    add_deps("oxd_libsec")
    add_defines("_VIZ")
    if (is_plat("windows")) then
        add_rules("win.sdk")
        add_defines("_CONSOLE")
        add_cxflags("/bigobj")
    elseif (is_plat("linux")) then
        add_cxflags("-fPIC", "-pthread")
        add_rules("linux.link_ipp")
    elseif (is_plat("macosx")) then
        add_files("SFC/core/os/objc_wrap.mm")
    end 
    add_includedirs("SFC")
    add_includedirs("SFC/core/ext/exprtk")
    add_includedirs("oxd_preda/native/abi")
    add_includedirs("oxd_preda/simulator")
    add_files("SFC/essentials.cpp")
    add_files("SFC/core/ext/exprtk/exprtk.cpp")
    add_files("oxd_preda/simulator/*.cpp")
    set_policy("build.merge_archive", true)

target("3rdParty")
    set_kind("phony")
    before_build(function(target)
        os.mkdir("$(buildir)/PREDA")
        os.mkdir("$(buildir)/PREDA/bin")
    end)
    after_build(function(target) 
        os.mkdir("$(buildir)/PREDA/scripts")
        os.mkdir("$(buildir)/PREDA/extensions")
        os.mkdir("$(buildir)/PREDA/examples")
        os.mkdir("$(buildir)/PREDA/solc")
        os.cp("oxd_preda/bin/compile_env", "$(buildir)/PREDA")
        os.cp("oxd_preda/bin/emscripten", "$(buildir)/PREDA")
        os.cp("oxd_preda/simulator/contracts/*", "$(buildir)/PREDA/examples")
        os.cp("preda*.vsix", "$(buildir)/PREDA/extensions/preda.vsix")
        os.cp("oxd_preda/bin/solc/solc*", "$(buildir)/PREDA/solc")
        if (is_plat("windows")) then
            os.cp("oxd_preda/3rdParty/evmone/win/bin/evmone.dll", "$(buildir)/PREDA/bin")
            os.cp("oxd_preda/3rdParty/wasmtime/lib/wasmtime.dll", "$(buildir)/PREDA/bin")
            os.cp("oxd_preda/bin/mingw64", "$(buildir)/PREDA")
            os.cp("installer/win/*.ps1", "$(buildir)/PREDA/scripts")
        elseif (is_plat("linux")) then
            os.cp("oxd_preda/3rdParty/wasmtime/lib/libwasmtime.so", "$(buildir)/PREDA/bin")
            os.cp("oxd_preda/3rdParty/evmone/linux/lib/libevmone*", "$(buildir)/PREDA/bin")
            os.cp("installer/linux/*", "$(buildir)/PREDA/scripts")
            os.run("chmod -R 755 $(buildir)/PREDA/emscripten/3.1.24")
        elseif (is_plat("macosx")) then
            os.cp("oxd_preda/3rdParty/wasmtime/lib/libwasmtime.dylib", "$(buildir)/PREDA/bin")
            os.cp("oxd_preda/3rdParty/evmone/darwin/lib/libevmone*", "$(buildir)/PREDA/bin")
            os.cp("installer/mac/*", "$(buildir)/PREDA/scripts")
            os.run("chmod -R 755 $(buildir)/PREDA/emscripten/3.1.24")
        end 
    end)

target("package")
    set_kind("phony")
    add_deps("oxd_libsec")
    add_links("antlr4-runtime")
    on_package(function (target)
        if is_plat("windows") then
            os.rm("$(buildir)/PREDA/bin/*.lib")
            os.rm("$(buildir)/PREDA/bin/*.pdb")
            os.rm("$(buildir)/PREDA/bin/*.ilk")
            os.rm("$(buildir)/PREDA/bin/*.exp")
            os.execv("iscc", {"./installer/win/Preda.iss"})
        elseif is_plat("linux") then
            os.rm("$(projectdir)/bundle")
            os.mkdir("$(projectdir)/bundle")
            os.mkdir("$(projectdir)/bundle/preda-toolchain")
            os.mkdir("$(projectdir)/bundle/preda-toolchain/usr")
            os.mkdir("$(projectdir)/bundle/preda-toolchain/usr/lib")
            os.mkdir("$(projectdir)/bundle/preda-toolchain/opt")
            os.mkdir("$(projectdir)/bundle/preda-toolchain/opt/PREDA")
            os.mkdir("$(projectdir)/bundle/preda-toolchain/DEBIAN")
            os.cp("$(projectdir)/build/PREDA/*", "$(projectdir)/bundle/preda-toolchain/opt/PREDA")
            os.cp("$(projectdir)/installer/linux/postinstall_linux.sh", "$(projectdir)/bundle/preda-toolchain/DEBIAN/postinst")
            os.cp("$(projectdir)/installer/linux/control_linux", "$(projectdir)/bundle/preda-toolchain/DEBIAN/control")
            os.cp("$(projectdir)/build/PREDA/bin/libantlr4-runtime.so.4.9.3", "$(projectdir)/bundle/preda-toolchain/usr/lib/libantlr4-runtime.so.4.9.3")
            os.rm("$(projectdir)/bundle/preda-toolchain/opt/PREDA/bin/*.a")
            os.cd("$(projectdir)/bundle")
            os.run("chmod 0555 preda-toolchain/DEBIAN/postinst")
            os.execv("dpkg-deb",  {"--build", "preda-toolchain", "preda-toolchain_0.1.0.0_amd64.deb"})
        elseif is_plat("macosx") then
            os.rm("$(projectdir)/bundle")
            os.mkdir("$(projectdir)/bundle")
            os.mkdir("$(projectdir)/bundle/PREDA")
            os.cp("$(buildir)/PREDA/*", "$(projectdir)/bundle/PREDA")
            os.rm("$(projectdir)/bundle/PREDA/bin/*.a")
            os.run("bash $(projectdir)/bundle/PREDA/scripts/bundle_mac.sh")
            os.run("packagesbuild $(projectdir)/bundle/PREDA/scripts/Preda.pkgproj -F $(projectdir)")
        end
    end)
