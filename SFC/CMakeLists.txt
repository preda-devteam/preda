cmake_minimum_required(VERSION 3.18)

# Enable Hot Reload for MSVC compilers if supported.
if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("SFC")
set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

function(win_sdk_rule target)
  if(MSVC)
    # Retrieve the necessary environment variables from the vcvars config
    # include("${CMAKE_CURRENT_LIST_DIR}/path/to/vcvars.cmake")  # Path to your vcvars file
    string(REPLACE "\\" "/" VC_TOOLS_DIR ${CMAKE_VS_PLATFORM_TOOLSET})
    set(vcvars_INCLUDE "${VC_TOOLS_DIR}/Include")
    set(vcvars_LIB "${VC_TOOLS_DIR}/Lib")

    if(vcvars_INCLUDE)
      target_include_directories(${target} PRIVATE ${vcvars_INCLUDE})
      #target_include_directories(${target} SYSTEM PRIVATE ${vcvars_INCLUDE})
      set_target_properties(${target} PROPERTIES InheritWarningLevel TRUE)
    endif()

    target_link_libraries(${target} PRIVATE
      kernel32 user32 gdi32 winspool comdlg32 advapi32 shell32 ole32
      oleaut32 uuid odbc32 odbccp32 comctl32 setupapi shlwapi
    )

    foreach(flags
      CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
      CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO
      CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
      CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
    )
      if(${${flags}} MATCHES "/MD")
        string(REGEX REPLACE "/MD" "/MT" ${${flags}} "${${flags}}")
      endif()
    endforeach()

    if(NOT MINGW)
      target_link_libraries(${target} PRIVATE strsafe)
    endif()
  endif()
endfunction()

function(linux_link_ipp_rule target)
  target_link_libraries(${target} PRIVATE
    pthread dl X11 ippdc ippac90lgc ippcc90lgc ippcc ippch90lgc ippch ippcp
    ippcv90lgc ippcv ippdc90lgc ippdi90lgc ippe ippgen90lgc ippi90lgc
    ippi ippj90lgc ippm90lgc ippr90lgc ipps90lgc ippsc90lgc ippvc90lgc
    ipps ippvm ippcore
  )
endfunction()

function(mac_link_rule target)
  target_link_libraries(${target} PRIVATE
    # "-framework CoreGraphics"
    # "-framework CoreFoundation"
    "-framework IOKit"
    "-framework ApplicationServices"
    "-framework Security"
    # "-framework Foundation"
  )
endfunction()

if(WIN32)
  # Use the USERPROFILE environment variable to get the user's home directory on Windows
  execute_process(COMMAND cmd /c "echo %USERPROFILE%" OUTPUT_VARIABLE HOME_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)
else()
  # For non-Windows platforms, use the HOME environment variable to get the user's home directory
  execute_process(COMMAND bash -c "echo $ENV{HOME}" OUTPUT_VARIABLE HOME_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)
endif()

set(DOWNLOAD_DIR "${HOME_DIR}/.cmake")
file(MAKE_DIRECTORY ${DOWNLOAD_DIR})
option(DOWNLOAD_IPP "download ipp packages" OFF)
option(DOWNLOAD_MKL "download mkl packages" OFF)
option(INCLUDE_TEST_PROJECT "include_SFC_test for devs" OFF)
set(ipp_dir ${PROJECT_SOURCE_DIR}/libs)
message(STATUS "The option DOWNLOAD_IPP is ${DOWNLOAD_IPP}, to enable with: -DDOWNLOAD_IPP=ON")
message(STATUS "The option DOWNLOAD_IPP is ${DOWNLOAD_MKL}, to enable with: -DDOWNLOAD_MKL=ON")
message(STATUS "The option INCLUDE_TEST_PROJECT is ${INCLUDE_TEST_PROJECT}, to enable with: -DINCLUDE_TEST_PROJECT=ON")
if(DOWNLOAD_IPP)
  message(STATUS "DOWNLOAD_IPP is ${DOWNLOAD_IPP}")

  if(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
    message("CMAKE_HOST_SYSTEM_NAME: ${CMAKE_HOST_SYSTEM_NAME}, begin download ipp package")
    set(URL "https://github.com/preda-devteam/preda/releases/download/SFC-Libs/sfc_win_ipp.7z")
    set(SHA256 "C22F7310AB7679A0E11A57BB96D6A0483230DA4FB4A0D88D53EF6DB2419C73A4")
    file(DOWNLOAD ${URL} ${DOWNLOAD_DIR}/sfc_win_ipp.7z SHOW_PROGRESS EXPECTED_HASH SHA256=${SHA256})
    file(ARCHIVE_EXTRACT INPUT ${DOWNLOAD_DIR}/sfc_win_ipp.7z DESTINATION ${ipp_dir}/win)
  elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
    message("CMAKE_HOST_SYSTEM_NAME: ${CMAKE_HOST_SYSTEM_NAME}, begin download ipp package")
    set(URL "https://github.com/preda-devteam/preda/releases/download/SFC-Libs/sfc_linux_ipp.7z")
    set(SHA256 "004B15DD58EBBF945103786F6BF8509968DEA43A7EC3F01E8551F2463C9D6D3C")
    file(DOWNLOAD ${URL} ${DOWNLOAD_DIR}/sfc_linux_ipp.7z SHOW_PROGRESS EXPECTED_HASH SHA256=${SHA256})
    file(ARCHIVE_EXTRACT INPUT ${DOWNLOAD_DIR}/sfc_linux_ipp.7z DESTINATION ${ipp_dir}/linux)
  elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
    message("CMAKE_HOST_SYSTEM_NAME: ${CMAKE_HOST_SYSTEM_NAME}, begin download ipp package")
    set(URL "https://github.com/preda-devteam/preda/releases/download/SFC-Libs/sfc_mac_ipp.7z")
    set(SHA256 "9417AD9A5BF702C0CC2F41AB3629FAC23998A931F5F09C1D0D849F43F577EE9A")
    file(DOWNLOAD ${URL} ${DOWNLOAD_DIR}/sfc_mac_ipp.7z SHOW_PROGRESS EXPECTED_HASH SHA256=${SHA256})
    file(ARCHIVE_EXTRACT INPUT ${DOWNLOAD_DIR}/sfc_mac_ipp.7z DESTINATION ${ipp_dir}/mac)
  else()
    message("current OS platform unkonw, download ipp latest failed.....")
  endif()
endif()

if(DOWNLOAD_MKL)
  message(STATUS "DOWNLOAD_MKL is ${DOWNLOAD_MKL}")

  if(WIN32)
    message("CMAKE_HOST_SYSTEM_NAME: Windows, begin download mkl package")
    set(URL "https://github.com/preda-devteam/preda/releases/download/SFC-Libs/sfc_win_mkl.7z")
    set(SHA256 "D8C3EA14A0562FB49BB48FE6B52A9D33285D706989C5946DB0A67CFCEBD24AE8")
    file(DOWNLOAD ${URL} ${DOWNLOAD_DIR}/sfc_win_mkl.7z SHOW_PROGRESS EXPECTED_HASH SHA256=${SHA256})
    file(ARCHIVE_EXTRACT INPUT ${DOWNLOAD_DIR}/sfc_win_mkl.7z DESTINATION ${ipp_dir}/win)
  elseif(UNIX AND NOT APPLE)
    message("CMAKE_HOST_SYSTEM_NAME: Linux, begin download mkl package")
    set(URL "https://github.com/preda-devteam/preda/releases/download/SFC-Libs/sfc_linux_mkl.7z")
    set(SHA256 "ACF7B599CC3A601C913A24A724CD353C23C2D8378502313D40ECA2669A91943E")
    file(DOWNLOAD ${URL} ${DOWNLOAD_DIR}/sfc_linux_mkl.7z SHOW_PROGRESS EXPECTED_HASH SHA256=${SHA256})
    file(ARCHIVE_EXTRACT INPUT ${DOWNLOAD_DIR}/sfc_linux_mkl.7z DESTINATION ${ipp_dir}/linux)
  elseif(APPLE)
    message("CMAKE_HOST_SYSTEM_NAME: Darwin, begin download mkl package")
    set(URL "https://github.com/preda-devteam/preda/releases/download/SFC-Libs/sfc_mac_mkl.7z")
    set(SHA256 "70C62852229377128E664EC1A48F04C725BE1A9C731869C83DA12AA6B24DC6BB")
    file(DOWNLOAD ${URL} ${DOWNLOAD_DIR}/sfc_mac_mkl.7z SHOW_PROGRESS EXPECTED_HASH SHA256=${SHA256})
    file(ARCHIVE_EXTRACT INPUT ${DOWNLOAD_DIR}/sfc_mac_mkl.7z DESTINATION ${ipp_dir}/mac)
  endif()
endif()

file(GLOB_RECURSE CORE_SOURCE_FILE 
    core/ext/bignum/big_num.*
    core/ext/bignum/precision_*
    core/ext/botan/botan.*
    core/ext/ipp/ipp_*.*
    core/ext/rocksdb/rocksdb.*
    core/ext/rocksdb/rocksdb_serving.*
    core/ext/mkl/mkl_linequ.h
    core/ext/mkl/mkl_rng.h
    core/ext/exprtk/exprtk.*
    core/ext/lib_*.c
    core/inet/*.cpp
    core/inet/*.h
    core/os/*.cpp
    core/os/*.h
    core/rt/*.cpp
    core/rt/*.h
)
file(GLOB WEBP_FILES
    core/ext/ipp/libwebp/webp_*.h
    core/ext/ipp/libwebp/webp_inc*.c
) 
file(GLOB TEST_SOURCE_FILE
    testcases/tests/test_*.cpp
    testcases/tests/entrypoint.cpp
    testcases/tests/experiments.cpp
    testcases/tests/test.h
)
file(GLOB MASM_FILES core/ext/bignum/ttmath/ttmathuint_x86_64_msvc.asm)
file(GLOB EXCLUDE_FILES
    core/ext/exprtk/exprtk/exprtk.hpp
    core/ext/ipp/ipp_canvas.h
    core/ext/ipp/ipp_config.h
    core/ext/ipp/ipp_image.h
    core/ext/rocksdb/rocksdb.inc
    core/inet/tinyhttpd_websocket.cpp
    core/inet/tinyhttpd_websocket.h
    core/os/thread_primitive.h
    core/os/user_inputs.cpp
    core/os/user_inputs.h
    core/rt/buffer_type.h
    core/rt/runtime_base.h
    core/rt/small_math.h
    core/rt/string_type.h
    core/rt/string_type_ops.h
    core/rt/type_traits.h
    core/ext/ipp/libwebp/webp_config.h
    core/ext/ipp/libwebp/webp_header.h
    core/ext/bignum/ttmath/ttmathuint_x86_64_msvc.asm 
)
list(APPEND SFC_FILES ${CORE_SOURCE_FILE} ${TEST_SOURCE_FILE} ${WEBP_FILES} ${MASM_FILES})

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
  file(GLOB MAIN_FILE testcases/proj.win/main.cpp)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
  file(GLOB MAIN_FILE testcases/proj.linux/main.cpp)
  # list(REMOVE_ITEM SFC_FILES ${EXCLUDE_FILES})
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
  file(GLOB MAIN_FILE 
    testcases/proj.mac/tester/main.cpp
    core/os/objc_wrap.mm
    )
# elseif(CMAKE_SYSTEM_NAME MATCHES "iOS")
# elseif(CMAKE_SYSTEM_NAME MATCHES "Android")
endif()

source_group("Tests" FILES ${TEST_SOURCE_FILE})
source_group("Win" FILES ${MAIN_FILE})
source_group("source" FILES ${CORE_SOURCE_FILE})
source_group("source/libwebp" FILES ${WEBP_FILES})
list(APPEND SFC_FILES ${MAIN_FILE})

if(INCLUDE_TEST_PROJECT)
  add_executable(test ${SFC_FILES})
  if(WIN32)
      enable_language(ASM_MASM)
      file(GLOB ipp_lib ${ipp_dir}/win/ipp*.lib)
      # get os arch 32bit or 64bit
      if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        file(GLOB mkl_lib ${ipp_dir}/win/mkl_x64*.lib)
      else()
        file(GLOB mkl_lib ${ipp_dir}/win/mkl_w32*.lib)
      endif()
      win_sdk_rule(test)
      if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
          set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi /bigobj /W3 /Gy /Oi /GL /FC /O2")
          set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /ZI /MP /RTC1 /bigobj /permissive /W3 /FC /Od /JMC")
          set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /OPT:ICF /OPT:REF /DEBUG /LTCG:incremental /ignore:4204")
          set_target_properties(test PROPERTIES
              MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug,StaticLibDebug>:Debug>"
          )
          set_source_files_properties(testcases/tests/test_perf.cpp PROPERTIES
              COMPILE_OPTIONS "/Ob0"
          )
      endif()
      target_link_directories(test PRIVATE ./libs/win)
      target_link_libraries(test PRIVATE ${ipp_lib} ${mkl_lib})
      target_compile_definitions(test PRIVATE
          _CONSOLE
          _UNICODE
          UNICODE
          PLATFORM_INTEL_IPP_WEBP_CODEC
          PLATFORM_INTEL_IPP_EXR_CODEC
          $<$<CONFIG:Debug>:PLATFORM_DISABLE_INTEL_IPP>
          $<$<CONFIG:Debug>:_DEBUG>

      )
  elseif(UNIX AND NOT APPLE)
      set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fpermissive")
      set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fpermissive")
      target_compile_options(test PRIVATE 
        -pthread
        -ldl 
        -lX11 
      )
      linux_link_ipp_rule(test)
      target_link_directories(test PRIVATE ${ipp_dir}/linux)
      target_link_libraries(test PRIVATE 
        mkl_intel_lp64
        mkl_sequential
        mkl_core
      )
      target_compile_definitions(test PRIVATE
        _CONSOLE
        _UNICODE
        UNICODE
        PLATFORM_INTEL_IPP_WEBP_CODEC
        PLATFORM_INTEL_IPP_EXR_CODEC
        # $<$<CONFIG:Debug>:PLATFORM_DISABLE_INTEL_IPP>
        # $<$<CONFIG:Debug>:_DEBUG>
        # $<$<CONFIG:Debug>:-test:multithread>
      )
  elseif(APPLE)
      set(CMAKE_OSX_DEPLOYMENT_TARGET 10.14)
      mac_link_rule(test)
      target_link_libraries(test PRIVATE
        mkl_core
        mkl_intel_lp64
        mkl_sequential
      )
      target_link_directories(test PRIVATE libs/mac)
      # target_compile_options(test PRIVATE 
      #   -std=c++14
      # )
  endif()
endif()