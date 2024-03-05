# CMakeList.txt: preda_preoject
#
cmake_minimum_required(VERSION 3.18)

# Enable Hot Reload for MSVC compilers if supported.
if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("bundle_package")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if(MSVC)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
add_subdirectory(SFC)
add_subdirectory(oxd_libsec)
add_subdirectory(oxd_preda)

# ################ build package to installer ########################
option(BUNDLE_OPS "default is OFF" OFF)
message(STATUS "BUNDLE_OPS is ${BUNDLE_OPS}....")

if(BUNDLE_OPS)
  set(BUNDLE_PATH ${CMAKE_SOURCE_DIR}/bundle)
  set(AppVersion "0.1.0" CACHE STRING "setup bundle package AppVersion")
  # configure_file(${CMAKE_SOURCE_DIR}/bin/bin_$<CONFIG> ${CMAKE_SOURCE_DIR}/bin CONFIGURE_DEPENDS)
  file(GLOB VSIX_FILES "${CMAKE_SOURCE_DIR}/*.vsix")
  set(LATEST_VSIX_FILE "")

  if(UNIX)
    foreach(VSIX_FILE ${VSIX_FILES})
      # 比较文件的修改时间, 如果是第一个文件，则直接赋值
      if(LATEST_VSIX_FILE STREQUAL "")
        set(LATEST_VSIX_FILE ${VSIX_FILE})
      else()
        # 获取当前最新文件和当前文件的修改时间
        file(TIMESTAMP LATEST_VSIX_FILE_TIME ${LATEST_VSIX_FILE} "%Y-%m-%d %H:%M:%S")
        # message("bbbbb ${LATEST_VSIX_FILE_TIME}")
        file(TIMESTAMP CURRENT_FILE_TIME ${VSIX_FILE} "%Y-%m-%d %H:%M:%S")

        # 比较修改时间，更新最新文件路径
        if(CURRENT_FILE_TIME STRGREATER LATEST_VSIX_FILE_TIME)
          set(LATEST_VSIX_FILE ${VSIX_FILE})
        endif()
      endif()
    endforeach()
  elseif(WIN32)
    foreach(VSIX_FILE ${VSIX_FILES})
      file(TIMESTAMP ${VSIX_FILE} VSIX_FILE_TIMESTAMP)
      set(VSIX_FILE_TIMESTAMPS "${VSIX_FILE_TIMESTAMPS}\n${VSIX_FILE_TIMESTAMP}#${VSIX_FILE}")
    endforeach()

    string(REGEX REPLACE "\n+" ";" FILE_TIMESTAMPS_LIST ${VSIX_FILE_TIMESTAMPS})
    list(SORT FILE_TIMESTAMPS_LIST)
    list(GET FILE_TIMESTAMPS_LIST -1 LATEST_VSIX_FILE)
    string(REGEX MATCH "[^#]*$" LATEST_VSIX_FILE ${LATEST_VSIX_FILE})
    string(SUBSTRING ${LATEST_VSIX_FILE} 0 -1 LATEST_VSIX_FILE)
  endif()

  message("Latest .vsix file: ${LATEST_VSIX_FILE}")
  add_custom_target(bundle_package
    COMMENT "Starting to build package, this will tack a few minutes....."
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${BUNDLE_PATH}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BUNDLE_PATH}
  )

  add_dependencies(bundle_package preda_engine transpiler chain_simulator)

  if(WIN32)
    file(GLOB_RECURSE PS1 LIST_DIRECTORIES FALSE ${CMAKE_CURRENT_SOURCE_DIR}/installer/win/*.ps1)
    file(GLOB SOLC LIST_DIRECTORIES FALSE ${CMAKE_CURRENT_SOURCE_DIR}/oxd_preda/bin/solc/solc*.exe)
    add_custom_command(TARGET bundle_package POST_BUILD
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      COMMAND ${CMAKE_COMMAND} -E make_directory ${BUNDLE_PATH}/PREDA/bin
      COMMAND ${CMAKE_COMMAND} -E make_directory ${BUNDLE_PATH}/PREDA/examples
      # COMMAND ${CMAKE_COMMAND} -E make_directory ${BUNDLE_PATH}/PREDA/solc
      COMMAND ${CMAKE_COMMAND} -E make_directory ${BUNDLE_PATH}/PREDA/scripts
      COMMAND ${CMAKE_COMMAND} -E make_directory ${BUNDLE_PATH}/PREDA/extensions
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/oxd_preda/bin/compile_env ${BUNDLE_PATH}/PREDA/compile_env
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/oxd_preda/simulator/contracts ${BUNDLE_PATH}/PREDA/examples
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/docs ${BUNDLE_PATH}/PREDA/docs
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/oxd_preda/bin/emscripten ${BUNDLE_PATH}/PREDA/emscripten
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/oxd_preda/bin/mingw64 ${BUNDLE_PATH}/PREDA/mingw64
      # COMMAND ${CMAKE_COMMAND} -E copy ${SOLC} ${BUNDLE_PATH}/PREDA/solc
      COMMAND ${CMAKE_COMMAND} -E copy ${PS1} ${BUNDLE_PATH}/PREDA/scripts
      COMMAND ${CMAKE_COMMAND} -E copy ${LATEST_VSIX_FILE} ${BUNDLE_PATH}/PREDA/extensions/preda.vsix
      COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/bin/bin_$<LOWER_CASE:$<CONFIG>>/preda_engine.dll ${BUNDLE_PATH}/PREDA/bin
      COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/bin/bin_$<LOWER_CASE:$<CONFIG>>/transpiler.dll ${BUNDLE_PATH}/PREDA/bin
      COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/bin/bin_$<LOWER_CASE:$<CONFIG>>/wasmtime.dll ${BUNDLE_PATH}/PREDA/bin
      COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/bin/bin_$<LOWER_CASE:$<CONFIG>>/evmone.dll ${BUNDLE_PATH}/PREDA/bin
      COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/bin/bin_$<LOWER_CASE:$<CONFIG>>/chsimu.exe ${BUNDLE_PATH}/PREDA/bin
      # COMMAND ${CMAKE_COMMAND} -E chdir . xcopy /Y /I  bin\\bin_$<LOWER_CASE:$<CONFIG>>\\*.dll bundle\\PREDA\\bin
    )
    set(iscc "C:\\Program Files (x86)\\Inno Setup 6\\ISCC.exe")
    add_custom_command(TARGET bundle_package POST_BUILD
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      COMMENT "Building package...."
      COMMAND ${iscc} /Qp /DVERSION="${AppVersion}" ./installer/win/Preda.iss
    )
  elseif(UNIX AND NOT APPLE)
    add_custom_command(TARGET bundle_package POST_BUILD
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      COMMENT "prepare bundle env, copying directory to bundle_path.............."
      COMMAND ${CMAKE_COMMAND} -E make_directory ${BUNDLE_PATH}/preda-toolchain/usr/lib
      COMMAND ${CMAKE_COMMAND} -E make_directory ${BUNDLE_PATH}/preda-toolchain/opt/PREDA/bin
      COMMAND ${CMAKE_COMMAND} -E make_directory ${BUNDLE_PATH}/preda-toolchain/DEBIAN
      COMMAND ${CMAKE_COMMAND} -E make_directory ${BUNDLE_PATH}/preda-toolchain/opt/PREDA/scripts
      COMMAND ${CMAKE_COMMAND} -E make_directory ${BUNDLE_PATH}/preda-toolchain/opt/PREDA/extensions
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/oxd_preda/bin/compile_env ${BUNDLE_PATH}/preda-toolchain/opt/PREDA/compile_env
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/oxd_preda/simulator/contracts ${BUNDLE_PATH}/preda-toolchain/opt/PREDA/examples
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/oxd_preda/bin/emscripten ${BUNDLE_PATH}/preda-toolchain/opt/PREDA/emscripten
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/docs ${BUNDLE_PATH}/preda-toolchain/opt/PREDA/docs
      # COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/oxd_preda/bin/solc ${BUNDLE_PATH}/preda-toolchain/opt/PREDA/solc
      COMMAND ${CMAKE_COMMAND} -E chdir ./ cp -a ${CMAKE_SOURCE_DIR}/bin/bin_$<LOWER_CASE:$<CONFIG>>/* ${BUNDLE_PATH}/preda-toolchain/opt/PREDA/bin
      COMMAND ${CMAKE_COMMAND} -E chdir ./ cp -a ${CMAKE_CURRENT_SOURCE_DIR}/installer/linux/* ${BUNDLE_PATH}/preda-toolchain/opt/PREDA/scripts
      COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/installer/linux/postinstall_linux.sh ${BUNDLE_PATH}/preda-toolchain/DEBIAN/postinst
      COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/installer/linux/control_linux ${BUNDLE_PATH}/preda-toolchain/DEBIAN/control
      COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_HOME_DIRECTORY}/dist/libantlr4-runtime.so.4.9.3 ${BUNDLE_PATH}/preda-toolchain/usr/lib
      COMMAND ${CMAKE_COMMAND} -E copy ${LATEST_VSIX_FILE} ${BUNDLE_PATH}/preda-toolchain/opt/PREDA/extensions/preda.vsix
    )
    add_custom_command(TARGET bundle_package POST_BUILD
      COMMENT "starting bundle package......."
      COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_CURRENT_SOURCE_DIR}/bundle chmod 0555 ./preda-toolchain/DEBIAN/postinst
      COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_CURRENT_SOURCE_DIR}/bundle sed -i 's/^Version.*/Version: ${AppVersion}/g' ./preda-toolchain/DEBIAN/control
      COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_CURRENT_SOURCE_DIR}/bundle dpkg-deb --build preda-toolchain preda-toolchain_${AppVersion}_amd64.deb
    )
  elseif(APPLE)
    add_custom_command(TARGET bundle_package POST_BUILD
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}

      COMMENT "prepare bundle env, copying directory to bundle_path.............."
      COMMAND ${CMAKE_COMMAND} -E make_directory ${BUNDLE_PATH}/PREDA/bin
      COMMAND ${CMAKE_COMMAND} -E make_directory ${BUNDLE_PATH}/PREDA/examples
      # COMMAND ${CMAKE_COMMAND} -E make_directory ${BUNDLE_PATH}/PREDA/solc
      COMMAND ${CMAKE_COMMAND} -E make_directory ${BUNDLE_PATH}/PREDA/scripts
      COMMAND ${CMAKE_COMMAND} -E make_directory ${BUNDLE_PATH}/PREDA/extensions
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/oxd_preda/bin/compile_env ${BUNDLE_PATH}/PREDA/compile_env
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/oxd_preda/simulator/contracts ${BUNDLE_PATH}/PREDA/examples
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/oxd_preda/bin/emscripten ${BUNDLE_PATH}/PREDA/emscripten
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/docs ${BUNDLE_PATH}/PREDA/docs
      # COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/oxd_preda/bin/solc ${BUNDLE_PATH}/PREDA/solc
      COMMAND ${CMAKE_COMMAND} -E chdir ./ cp -a ${CMAKE_CURRENT_SOURCE_DIR}/bin/bin_$<LOWER_CASE:$<CONFIG>>/* ${BUNDLE_PATH}/PREDA/bin
      COMMAND ${CMAKE_COMMAND} -E chdir ./ cp -a ${CMAKE_CURRENT_SOURCE_DIR}/installer/mac/* ${BUNDLE_PATH}/PREDA/scripts/
      COMMAND ${CMAKE_COMMAND} -E copy ${LATEST_VSIX_FILE} ${BUNDLE_PATH}/PREDA/extensions/preda.vsix
    )
    add_custom_command(TARGET bundle_package POST_BUILD
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      COMMENT "starting bundle package......."
      COMMAND ${CMAKE_COMMAND} -E chdir ./ bash ${BUNDLE_PATH}/PREDA/scripts/bundle_mac.sh
      COMMAND ${CMAKE_COMMAND} -E chdir ./ packagesbuild ${BUNDLE_PATH}/PREDA/scripts/Preda.pkgproj -F ${CMAKE_CURRENT_SOURCE_DIR}
    )
  endif()

  set_target_properties(bundle_package PROPERTIES
    EXCLUDE_FROM_ALL true
    EXCLUDE_FROM_DEFAULT_BUILD true
  )

else()
  message("Bundle option is OFF, please set -DBUNDLE_OPS=ON to run bundle....")
endif()
