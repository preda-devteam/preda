# CMakeList.txt: preda_preoject
#
cmake_minimum_required(VERSION 3.18)

# set(CMAKE_CONFIGURATION_TYPES "Debug;Release;StaticLibDebug;StaticLibRelease" CACHE STRING "" FORCE)
# Enable Hot Reload for MSVC compilers if supported.
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})

project("oxd_libsec")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

function(win_sdk_rule target)
    if(MSVC)
        # Retrieve the necessary environment variables from the vcvars config
        # include("${CMAKE_CURRENT_LIST_DIR}/path/to/vcvars.cmake")  # Path to your vcvars file
        string(REPLACE "\\" "/" VC_TOOLS_DIR ${CMAKE_VS_PLATFORM_TOOLSET})
        set(vcvars_INCLUDE "${VC_TOOLS_DIR}/Include")
        set(vcvars_LIB "${VC_TOOLS_DIR}/Lib")
        set(CMAKE_CXX_FLAGS "")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /EHsc")
        set(CMAKE_CXX_FLAGS_DEBUG "")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd /ZI /Od /RTC1")
        set(CMAKE_CXX_FLAGS_RELEASE "")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /O2 /DNDEBUG")
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

        if(vcvars_INCLUDE)
            target_include_directories(${target} PRIVATE ${vcvars_INCLUDE})

            # target_include_directories(${target} SYSTEM PRIVATE ${vcvars_INCLUDE})
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
            if(${flags} MATCHES "/MD")
                string(REGEX REPLACE "/MD" "/MT" ${flags} "${${flags}}")
            endif()
        endforeach()

        if(NOT MINGW)
            target_link_libraries(${target} PRIVATE strsafe)
        endif()
    endif()
endfunction()

# ################ build oxd_libsec.lib##########################
file(GLOB ESSENTIALS_SOURCES ../SFC/essentials.*)
file(GLOB BOTAN_SOURCES ../SFC/core/ext/botan/botan.*)
file(GLOB OXD_LIBSEC_SOURCES src/*.cpp src/*.h)
file(GLOB_RECURSE LIBSODIUM_SOURCES src/libsodium/libsodium/src/libsodium/*.c)
file(GLOB OXD_LIBSEC_HEAD src/*.h)
file(GLOB MAIN_FILES
    src/keccak256.cpp
    test/proj.win/main.cpp
	test/keypair_gen.cpp
    oxd_libsec.h
    test/sec_tests.*
)
set(GROUP_FILE ${OXD_LIBSEC_HEAD})
source_group("SFC" FILES ${BOTAN_SOURCES} ${ESSENTIALS_SOURCES})
source_group(TREE ${PROJECT_SOURCE_DIR}/src PREFIX "sec" FILES ${OXD_LIBSEC_SOURCES} ${GROUP_FILE} ${LIBSODIUM_SOURCES})
source_group("main" FILES ${MAIN_FILES})

add_library(oxd_libsec STATIC
    ${ESSENTIALS_SOURCES}
    ${BOTAN_SOURCES}
    ${OXD_LIBSEC_SOURCES}
    ${LIBSODIUM_SOURCES}
)
include_directories(./src/libsodium/libsodium/src/libsodium/include/sodium)

add_definitions(-DSODIUM_STATIC)

option(INCLUDE_TEST_PROJECT "oxd_libsec_test for devs" OFF)
message(STATUS "INCLUDE_TEST_PROJECT is ${INCLUDE_TEST_PROJECT}, to enable with: -DINCLUDE_TEST_PROJECT=ON")

if(WIN32)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi /sdl /Gy /permissive /O2 /Oi /GL /FC")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /ZI /JMC /sdl /RTC1 /permissive /Od /bigobj /FC")
    endif()

    file(GLOB WIN_IPP_LIBS ../SFC/libs/win/ipp*.lib)
    link_directories(../SFC/libs/win)
    link_libraries(${WIN_IPP_LIBS})
    win_sdk_rule(oxd_libsec)
    set_target_properties(oxd_libsec PROPERTIES
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug,StaticLibDebug>:Debug>"
    )
    target_compile_definitions(oxd_libsec PRIVATE -DUNICODE -D_UNICODE _CONSOLE)
    set_target_properties(oxd_libsec PROPERTIES InheritWarningLevel TRUE)

    # ##################### add libsec_test to build as exe ###################################
    if(INCLUDE_TEST_PROJECT)
        if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
            set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF /LTCG:incremental")
            set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi /W3 /sdl /Gy /permissive /O2 /Oi /GL /FC")
            set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /ZI /JMC /W3 /sdl /RTC1 /permissive /Od /bigobj /FC")
        endif()

        add_executable(libsec_test
            ${ESSENTIALS_SOURCES}
            ${BOTAN_SOURCES}
            ${OXD_LIBSEC_SOURCES}
            ${LIBSODIUM_SOURCES}
            ${MAIN_FILES}
        )
        target_sources(libsec_test PRIVATE
            test/sec_tests.cpp
            test/proj.win/main.cpp
        )
        win_sdk_rule(libsec_test)
        set_target_properties(libsec_test PROPERTIES
            MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug,StaticLibDebug>:Debug>"
        )
        target_compile_definitions(libsec_test PRIVATE -DUNICODE -D_UNICODE _CONSOLE OXD_LIBSEC_TESTPROJ)
        set_target_properties(libsec_test PROPERTIES InheritWarningLevel TRUE)
        set_target_properties(libsec_test PROPERTIES OUTPUT_NAME "oxd_libsec")
    endif()
elseif(UNIX AND NOT APPLE)
    target_link_directories(oxd_libsec PRIVATE ../SFC/libs/linux)
    file(GLOB LINUX_IPP_LIBS ../SFC/libs/linux/*.a)
    target_link_libraries(oxd_libsec PRIVATE
        pthread dl X11
    )
    add_compile_options(-fPIC -pthread -ldl -lX11)
    if(NOT CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
        target_link_libraries(oxd_libsec PRIVATE ${LINUX_IPP_LIBS})
    else()
        target_compile_definitions(oxd_libsec PRIVATE PLATFORM_DISABLE_INTEL_IPP)
    endif()
    ########################## add libsec_test executable target ###################################
    if(INCLUDE_TEST_PROJECT)
        link_directories(../SFC/libs/linux)
        link_libraries(${LINUX_IPP_LIBS})
        file(GLOB EXCLUDE_SOURCE_FILES test/proj.win/main.cpp)
        list(REMOVE_ITEM MAIN_FILES ${EXCLUDE_SOURCE_FILES})
        add_executable(libsec_test
            ${ESSENTIALS_SOURCES}
            ${BOTAN_SOURCES}
            ${OXD_LIBSEC_SOURCES}
            ${LIBSODIUM_SOURCES}
            ${MAIN_FILES}
        )
        target_sources(libsec_test PRIVATE
            test/sec_tests.cpp
            test/sec_tests.h
            test/keypair_gen.cpp
            test/proj.linux/main.cpp
        )
        target_link_directories(libsec_test PRIVATE ../SFC/libs/linux)
        target_link_libraries(libsec_test PRIVATE
            pthread dl X11
        )
        target_link_libraries(libsec_test PRIVATE ${LINUX_IPP_LIBS})
        set_target_properties(libsec_test PROPERTIES OUTPUT_NAME "libsec_test")
        set_target_properties(libsec_test PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/$<0:>
            LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/$<0:>
            RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/$<0:>
        )
    endif()
elseif(APPLE)
    file(GLOB MAC_LIBS ../SFC/libs/mac/*.a)
    target_link_directories(oxd_libsec PRIVATE ../SFC/libs/mac)
    list(APPEND OXD_LIBSEC_SOURCES ../SFC/core/os/objc_wrap.mm)
    target_link_libraries(oxd_libsec PRIVATE ${MAC_LIBS})
    set(CMAKE_OSX_DEPLOYMENT_TARGET 10.14)
    if(INCLUDE_TEST_PROJECT)
        link_directories(../SFC/libs/mac)
        link_libraries(${MAC_LIBS})
        file(GLOB EXCLUDE_SOURCE_FILES test/proj.win/main.cpp)
        list(REMOVE_ITEM MAIN_FILES ${EXCLUDE_SOURCE_FILES})
        add_executable(libsec_test
            ${ESSENTIALS_SOURCES}
            ${BOTAN_SOURCES}
            ${OXD_LIBSEC_SOURCES}
            ${LIBSODIUM_SOURCES}
            ${MAIN_FILES}
        )
        target_sources(libsec_test PRIVATE
            test/sec_tests.cpp
            test/sec_tests.h
            test/keypair_gen.cpp
            test/proj.mac/main.cpp
        )
        target_link_directories(libsec_test PRIVATE ../SFC/libs/mac)
        target_link_libraries(libsec_test PRIVATE ${MAC_LIBS})
        target_link_libraries(libsec_test PRIVATE
            "-framework CoreGraphics"
            "-framework CoreFoundation"
            "-framework IOKit"
            "-framework ApplicationServices"
            "-framework Security"
            "-framework Foundation"
        )
        set_target_properties(libsec_test PROPERTIES OUTPUT_NAME "libsec_test")
        set_target_properties(libsec_test PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/$<0:>
            LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/$<0:>
            RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/$<0:>
        )
    endif()
endif()

# set oxd_libsec name as oxd_libsec_d in debug mode
set_target_properties(oxd_libsec PROPERTIES DEBUG_POSTFIX "_d")
set_target_properties(oxd_libsec PROPERTIES OUTPUT_NAME "oxd_libsec")
set_target_properties(oxd_libsec PROPERTIES ENABLE_EXPORTS ON)
set_target_properties(oxd_libsec PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(oxd_libsec PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/$<0:>
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/$<0:>
)
