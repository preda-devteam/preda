# CMakeList.txt: preda_preoject
#
cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

include(../CMake_rules.txt)
project(chain_simulator)

# add options for macros
option(ENABLE_VERIFY_SIG OFF)
option(ENABLE_AFFINITY_SET OFF)

# ############## build chain_simulator #################
file(GLOB_RECURSE CHAIN_SIMULATOR_FILE
  ../../SFC/core/ext/bignum/big_num.*
  ../../SFC/core/ext/bignum/precision_num.*
  ../../SFC/core/ext/botan/botan.*
  ../../SFC/core/ext/lib_inc.c
  ../../SFC/core/ext/bignum/ttmath/ttmathuint_x86_64_msvc.asm
  ../../SFC/essentials.cpp
  main.cpp
)
file(GLOB_RECURSE TEST EXCLUDE contracts/scope.*
  contracts/*.prdts
  contracts/*.prd
)
file(GLOB SIMULATOR 
	chain_simu.h
	chain_simu.cpp
	core_contracts.h
	core_contracts.cpp
	shard_data.h
	shard_data.cpp
	simu_global.h
	simu_global.cpp
	simu_script.h
	simu_script.cpp
	simu_shard.h
	simu_shard.cpp
)
file(GLOB ANTLR_GENERATED
  antlr_generated/*.cpp
  antlr_generated/*.h
)
file(GLOB proj_win
  proj.win/*.h
  proj.win/preda.ico
  proj.win/*.rc
)
file(GLOB RVM ../native/abi/*.h ../native/abi/*.cpp)
file(GLOB RVM_TYPE ../native/types/*.h ../native/types/*.cpp)
source_group("test" FILES ${TEST})
source_group("simulator" FILES ${SIMULATOR})
source_group("simulator/antlr_generated" FILES ${ANTLR_GENERATED})
source_group("Source Files" FILES ${proj_win})

# source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/../native PREFIX "rvm" FILES ${RVM})
source_group("rvm" FILES ${RVM})
source_group("rvm/types" FILES ${RVM_TYPE})
source_group("main" FILES ${CHAIN_SIMULATOR_FILE})
add_executable(chain_simulator ${CHAIN_SIMULATOR_FILE} ${TEST} ${SIMULATOR} ${ANTLR_GENERATED} ${RVM} ${RVM_TYPE} ${proj_win})

# Add macro definitions based on options
if(ENABLE_VERIFY_SIG)
    target_compile_definitions(chain_simulator PRIVATE VERIFY_SIG=1)
endif()

if(ENABLE_AFFINITY_SET)
    target_compile_definitions(chain_simulator PRIVATE AFFINITY_SET=1)
endif()

target_sources(chain_simulator PRIVATE
  ../../SFC/essentials.cpp
  ../../SFC/core/ext/lib_inc.c
)
target_link_directories(chain_simulator PRIVATE ../../oxd_libsec/lib)
target_include_directories(chain_simulator PRIVATE ../3rdParty/antlr4/runtime/Cpp/runtime/src)
target_link_libraries(chain_simulator PRIVATE "oxd_libsec$<$<CONFIG:Debug>:_d>")

if(WIN32)
  target_sources(chain_simulator PRIVATE ../../SFC/core/ext/bignum/ttmath/ttmathuint_x86_64_msvc.asm)
  set_source_files_properties(../../SFC/core/ext/bignum/ttmath/ttmathuint_x86_64_msvc.asm PROPERTIES LANGUAGE ASM_MASM)
  target_link_directories(chain_simulator PRIVATE ../../SFC/libs/win)
  target_link_libraries(chain_simulator PRIVATE ${IPP_LIB} antlr4-runtime)
  win_sdk_rule(chain_simulator)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi /W3 /sdl /MP /Gy /O2 /Oi /GL /GS /FC /permissive /bigobj")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /ZI /JMC /W3 /MP /sdl /RTC1 /Od /GS /FC /permissive /bigobj")
  set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /OPT:ICF /OPT:REF /DEBUG /LTCG:incremental")
endif()
elseif(UNIX AND NOT APPLE)
  add_dependencies(chain_simulator antlr4_shared)
  linux_link_ipp_rule(chain_simulator)
  target_link_directories(chain_simulator PRIVATE ../../SFC/libs/linux)
  target_link_libraries(chain_simulator PRIVATE ${IPP_LIB} antlr4_shared)
  target_compile_options(chain_simulator PRIVATE -fPIC -pthread)
  if(CMAKE_BUILD_TYPE MATCHES Debug)
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,${CMAKE_SOURCE_DIR}/bin/bin_debug/")
  else()
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,${CMAKE_SOURCE_DIR}/bin/bin_release/")
  endif()
elseif(APPLE)
  add_dependencies(chain_simulator antlr4_shared)
  target_sources(chain_simulator PRIVATE ../../SFC/core/os/objc_wrap.mm)
  target_link_libraries(chain_simulator
    PRIVATE
    ${IPP_LIB}
	antlr4_shared
  )
  mac_link_rule(chain_simulator)
  if(CMAKE_BUILD_TYPE MATCHES Debug)
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,${CMAKE_SOURCE_DIR}/bin/bin_debug/")
  else()
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,${CMAKE_SOURCE_DIR}/bin/bin_release/")
  endif()
endif()

target_compile_definitions(chain_simulator PRIVATE _VIZ _CONSOLE ANTLR4CPP_STATIC NOGDI)
set_target_properties(chain_simulator PROPERTIES OUTPUT_NAME "chsimu")
set_property(TARGET chain_simulator PROPERTY CXX_STANDARD 17)
set_target_properties(chain_simulator PROPERTIES LINK_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}")
set_target_properties(chain_simulator PROPERTIES CMAKE_POLICY_DEFAULT_CMP0069 NEW)
set_target_properties(chain_simulator PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/bin_$<LOWER_CASE:$<CONFIG>>/$<0:>
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/bin_$<LOWER_CASE:$<CONFIG>>/$<0:>
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/bin_$<LOWER_CASE:$<CONFIG>>/$<0:>
)

if(CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET chain_simulator PROPERTY CXX_STANDARD 17)
  cmake_policy(SET CMP0057 NEW)
endif()
