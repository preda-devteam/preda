cmake_minimum_required(VERSION 3.18)

# Enable Hot Reload for MSVC compilers if supported.
if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("SFC")

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
set(ipp_dir ${PROJECT_SOURCE_DIR}/libs)

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

# add_library()