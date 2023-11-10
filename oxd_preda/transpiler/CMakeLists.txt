# CMakeList.txt: preda_preoject
#
cmake_minimum_required(VERSION 3.18)

# Enable Hot Reload for MSVC compilers if supported.
if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

include(../CMake_rules.txt)
project("transpiler")

# ############### build transpiler ###############
file(GLOB TRANSPILER_SOURCES
  ./*.cpp
  ./*.h
)
file(GLOB_RECURSE TRANSPILER_FILES
  ./transpiler/*.cpp
  ./transpiler/*.h
)
file(GLOB_RECURSE ANTLR_GEN
  ./antlr_generated/*.cpp
  ./antlr_generated/*.h
)
source_group("transpiler" FILES ${TRANSPILER_FILES})
source_group("antlr_generated" FILES ${ANTLR_GEN})
add_library(transpiler SHARED ${TRANSPILER_SOURCES} ${TRANSPILER_FILES} ${ANTLR_GEN})

# find_library(ANTLR4 antlr4-runtime ${CMAKE_SOURCE_DIR}/bin/bin_${CMAKE_BUILD_TYPE}/$<0:>)
if(WIN32)
  add_dependencies(transpiler antlr4-runtime)
  target_link_directories(transpiler PRIVATE
    ../../SFC/libs/win

    # ${CMAKE_SOURCE_DIR}/bin/bin_$<CONFIG>/$<0:>
  )
  target_link_libraries(transpiler PRIVATE
    antlr4-runtime
  )
  target_compile_definitions(transpiler PRIVATE ANTLR4CPP_STATIC _MBCS)
  win_sdk_rule(transpiler)

  if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} /DEBUG:FULL /INCREMENTAL")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE_INIT} /DEBUG:FULL /OPT:REF /OPT:ICF /LTCG:incremental")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi /W3 /sdl /Gy /Gd /Oi /FC /permissive- /GL")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /ZI /JMC /sdl /MP /permissive- /FC")
  endif()

  set_property(TARGET transpiler PROPERTY CXX_STANDARD 14)
elseif(UNIX AND NOT APPLE)
  add_dependencies(transpiler antlr4_shared)
  target_include_directories(transpiler PRIVATE
    ../../SFC/libs/linux
  )
  target_compile_options(transpiler PRIVATE -fPIC -pthread -ldl -lX11)
  target_link_directories(transpiler PRIVATE ${CMAKE_BINARY_DIR}/bin)
  target_link_libraries(transpiler PRIVATE
    antlr4_shared
    ${IPP_LIB}
  )
  set_target_properties(transpiler PROPERTIES
    PREFIX ""
    SUFFIX ".so"
  )
  add_custom_command(TARGET transpiler POST_BUILD
    COMMENT "Copy antlr4_shared library to libdirectory......"
    COMMAND ${CMAKE_COMMAND} -E chdir ./ cp -a ${CMAKE_HOME_DIRECTORY}/dist/libantlr4-runtime.so* ${CMAKE_SOURCE_DIR}/bin/bin_$<LOWER_CASE:$<CONFIG>>/$<0:>
  )
elseif(APPLE)
  file(GLOB MAC_SOURCE_FILE ../../SFC/libs/mac/*.a)
  add_dependencies(transpiler antlr4_shared)
  target_link_libraries(transpiler PRIVATE
    antlr4_shared
    ${MAC_SOURCE_FILE}
  )

  # target_sources(transpiler PRIVATE ${MAC_SOURCE_FILE})
  set_target_properties(transpiler PROPERTIES
    PREFIX ""
    SUFFIX ".dylib"
  )
  mac_link_rule(transpiler)
  add_custom_command(TARGET transpiler POST_BUILD
    COMMENT "Copy antlr4_shared library to libdirectory......"
    COMMAND ${CMAKE_COMMAND} -E chdir ./ cp -a ${CMAKE_HOME_DIRECTORY}/dist/libantlr4-runtime.* ${CMAKE_SOURCE_DIR}/bin/bin_$<LOWER_CASE:$<CONFIG>>/$<0:>
  )
endif()

target_include_directories(transpiler PRIVATE
  ../3rdParty/antlr4/runtime/Cpp/runtime/src
)

target_sources(transpiler PRIVATE ${TRANSPILER_SOURCES})
set_target_properties(transpiler PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/bin_$<LOWER_CASE:$<CONFIG>>/$<0:>
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/bin_$<LOWER_CASE:$<CONFIG>>/$<0:>
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/bin_$<LOWER_CASE:$<CONFIG>>/$<0:>
)

# target_link_libraries(transpiler PRIVATE antlr4-runtime)
set_property(TARGET transpiler PROPERTY CMAKE_POLICY_DEFAULT_CMP0079 NEW)
