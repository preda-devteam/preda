# CMakeList.txt: preda_preoject
#
cmake_minimum_required(VERSION 3.18)

# Enable Hot Reload for MSVC compilers if supported.
if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

include(../CMake_rules.txt)
project("preda_engine")
file(GLOB_RECURSE PREDA_ENGINE_FILES
  preda_engine/ContractData*
  preda_engine/PredaCompiledContracts.*
  preda_engine/SymbolDBForTranspiler.*
)
file(GLOB_RECURSE ROCKSDB
  ../../SFC/core/ext/rocksdb/rocksdb.*
)
source_group("SFC" FILES
  ../../SFC/core/ext/bignum/big_num.cpp
  ../../SFC/core/ext/bignum/precision_num.cpp
  ../../SFC/core/ext/lib_inc.c
  ../../SFC/essentials.cpp
)
file(GLOB_RECURSE EVMEngine
  evm_engine/*
)
file(GLOB COMPILE_ENV ../bin/compile_env/contract_template.cpp)
file(GLOB_RECURSE native ../native/*)
file(GLOB_RECURSE PREDA_ENGINE_FILES_RVM
  preda_engine/RvmAssetDelegate.*
  preda_engine/RvmContractDelegate.*
)
file(GLOB_RECURSE ExecutionEngine
  preda_engine/ContractRuntime*
  preda_engine/ExecutionEngine.*
  preda_engine/WASMRuntime.*
)
file(GLOB_RECURSE RuntimeInterface
  preda_engine/bigint.*
  preda_engine/runtime_interface.h
  preda_engine/RuntimeInterfaceImpl.*
)
file(GLOB main preda_engine/main.cpp ../../SFC/core/ext/bignum/ttmath/ttmathuint_x86_64_msvc.asm)
source_group("compile_environment" FILES ${COMPILE_ENV})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/evm_engine PREFIX "EVMEngine" FILES ${EVMEngine})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/../native PREFIX "native" FILES ${native})
source_group("PredaEngine/ContractDatabase/RvmDelegate" FILES ${PREDA_ENGINE_FILES_RVM})
source_group("PredaEngine/ContractDatabase" FILES ${PREDA_ENGINE_FILES})
source_group("PredaEngine/ExecutionEngine/RuntimeInterface" FILES ${RuntimeInterface})
source_group("PredaEngine/ExecutionEngine" FILES ${ExecutionEngine})
source_group("rocksdb" FILES ${ROCKSDB})
source_group("Source Files" FILES "${main}")
add_library(preda_engine SHARED ${main} ${PREDA_ENGINE_FILES} ${PREDA_ENGINE_FILES_RVM} ${EVMEngine} ${native} ${ExecutionEngine} ${RuntimeInterface} ${ROCKSDB})
target_sources(preda_engine
  PRIVATE
  ../../SFC/core/ext/bignum/big_num.cpp
  ../../SFC/core/ext/bignum/precision_num.cpp
  ../../SFC/core/ext/lib_inc.c
  ../../SFC/core/ext/rocksdb/rocksdb.cpp
  ../../SFC/essentials.cpp
  ../native/types/data_jsonifer.cpp
  ../native/types/blob.cpp
  ../native/types/data.cpp
)
target_include_directories(preda_engine
  PRIVATE
  ../3rdParty/wasmtime/include
  ../3rdParty/evmc/include
)

set_target_properties(preda_engine PROPERTIES
  BUILD_WITH_INSTALL_RPATH TRUE
  INSTALL_RPATH "."
)
target_link_directories(preda_engine PRIVATE
  ../3rdParty/wasmtime/lib
  ../../oxd_libsec/lib
)
target_link_libraries(preda_engine PRIVATE "oxd_libsec$<$<CONFIG:Debug>:_d>")

if(WIN32)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} /DEBUG:FULL /INCREMENTAL")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE_INIT} /DEBUG:FULL /OPT:REF /OPT:ICF /LTCG:incremental")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi /W3 /MP /sdl /Gy /O2 /Oi /GL /GS /FC /bigobj")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /ZI /JMC /W3 /MP /sdl /RTC1 /Od /GS /FC /bigobj")
  endif()

  target_include_directories(preda_engine
    PRIVATE
    ../3rdParty/evmone/win/include
  )
  target_link_directories(preda_engine
    PRIVATE
    ../3rdParty/evmone/win/lib
    ../../SFC/libs/win
  )
  target_link_libraries(preda_engine
    PRIVATE
    wasmtime.dll.lib
    evmone
    ${IPP_LIB}
  )
  target_compile_definitions(preda_engine PRIVATE _WINDLL)
  target_sources(preda_engine
    PRIVATE
    ../../SFC/core/ext/bignum/ttmath/ttmathuint_x86_64_msvc.asm
  )
  set_source_files_properties(../../SFC/core/ext/bignum/ttmath/ttmathuint_x86_64_msvc.asm PROPERTIES LANGUAGE ASM_MASM)
  win_sdk_rule(preda_engine)
  add_custom_command(TARGET preda_engine POST_BUILD
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ../3rdParty/evmone/win/bin/evmone.dll ${CMAKE_SOURCE_DIR}/bin/bin_$<LOWER_CASE:$<CONFIG>>/$<0:>
    COMMAND ${CMAKE_COMMAND} -E copy ../3rdParty/wasmtime/lib/wasmtime.dll ${CMAKE_SOURCE_DIR}/bin/bin_$<LOWER_CASE:$<CONFIG>>/$<0:>
  )
elseif(UNIX AND NOT APPLE)
  linux_link_ipp_rule(preda_engine)
  target_include_directories(preda_engine
    PRIVATE
    ../3rdParty/evmone/linux/include
  )
  target_link_directories(preda_engine
    PRIVATE
    ../3rdParty/evmone/linux/lib
    ../../SFC/libs/linux
  )

  target_compile_options(preda_engine
    PRIVATE
    -fPIC
    -pthread
  )
  target_link_libraries(preda_engine
    PRIVATE
    wasmtime
    evmone
    ${IPP_LIB}
  )
  set_target_properties(preda_engine PROPERTIES
    PREFIX ""
    SUFFIX ".so"
  )
  add_custom_command(TARGET preda_engine POST_BUILD
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} -E chdir ./ cp -a ../3rdParty/evmone/linux/lib/libevmone.* ${CMAKE_SOURCE_DIR}/bin/bin_$<LOWER_CASE:$<CONFIG>>/$<0:>
    COMMAND ${CMAKE_COMMAND} -E chdir ./ cp -a ../3rdParty/wasmtime/lib/libwasmtime.so ${CMAKE_SOURCE_DIR}/bin/bin_$<LOWER_CASE:$<CONFIG>>/$<0:>
  )
elseif(APPLE)
  set(BUILD_SHARED_LIBS ON)
  target_include_directories(preda_engine
    PRIVATE
    ../3rdParty/evmone/darwin/include
  )
  target_link_directories(preda_engine
    PRIVATE
    ../../SFC/libs/mac
    ../3rdParty/evmone/darwin/lib
  )
  target_sources(preda_engine
    PRIVATE
    ../../SFC/core/os/objc_wrap.mm
  )
  target_link_libraries(preda_engine
    PRIVATE
    wasmtime
    evmone
    ${IPP_LIB}
  )
  mac_link_rule(preda_engine)
  set_target_properties(preda_engine PROPERTIES
    PREFIX ""
    SUFFIX ".dylib"
  )
  add_custom_command(TARGET preda_engine POST_BUILD
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} -E chdir ./ cp -a ../3rdParty/evmone/darwin/lib/libevmone.* ${CMAKE_SOURCE_DIR}/bin/bin_$<LOWER_CASE:$<CONFIG>>/$<0:>
    COMMAND ${CMAKE_COMMAND} -E chdir ./ cp -a ../3rdParty/wasmtime/lib/libwasmtime.* ${CMAKE_SOURCE_DIR}/bin/bin_$<LOWER_CASE:$<CONFIG>>/$<0:>
  )
endif()

set_target_properties(preda_engine PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/bin_$<LOWER_CASE:$<CONFIG>>/$<0:>
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/bin_$<LOWER_CASE:$<CONFIG>>/$<0:>
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/bin_$<LOWER_CASE:$<CONFIG>>/$<0:>
)

# set_policy(CMP0069 NEW)
set_property(TARGET preda_engine PROPERTY CXX_STANDARD 17)
set_property(TARGET preda_engine PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET preda_engine PROPERTY CXX_EXTENSIONS ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# ################### COMPILE_ENV file source ########################
file(GLOB_RECURSE COMPILE_ENV_BUILTIN
  ../bin/compile_env/include/address_blob_hash_types.h
  ../bin/compile_env/include/arraytype.h
  ../bin/compile_env/include/biginttype.h
  ../bin/compile_env/include/define_struct.h
  ../bin/compile_env/include/enumtype.h
  ../bin/compile_env/include/inttypes.h
  ../bin/compile_env/include/maptype.h
  ../bin/compile_env/include/stringtype.h
  ../bin/compile_env/include/structtype.h
  ../bin/compile_env/include/typeidentifier.h
  ../bin/compile_env/include/tokentype.h
  ../bin/compile_env/include/floattypes.h
  ../bin/compile_env/include/*.h
)
file(GLOB COMPILE_ENV
  ../bin/compile_env/include/interface.h
  ../bin/compile_env/contract_template.h
  ../bin/compile_env/include/exceptions.h
  ../bin/compile_env/include/runtime_interface.h
  ../bin/compile_env/include/common.h
  ../bin/compile_env/include/relay.h
  ../bin/compile_env/include/contexts.h
  ../bin/compile_env/*.h
)
file(GLOB COMPILE_ENV_MAIN
  mockup/main.cpp
)
source_group("Source Files" FILES ${COMPILE_ENV})
source_group("Source Files/builtin_types" FILES ${COMPILE_ENV_BUILTIN})
add_library(compile_env ${COMPILE_ENV} ${COMPILE_ENV_BUILTIN} ${COMPILE_ENV_MAIN})
set_target_properties(compile_env PROPERTIES
  EXCLUDE_FROM_ALL true
  EXCLUDE_FROM_DEFAULT_BUILD true
)