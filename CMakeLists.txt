cmake_minimum_required(VERSION 3.5)

project(AesCmac VERSION 0.0.1)

enable_language(C)

# Specify CMake version 3.5 to enable:
#   CMP0028 - Double colon in target name means ALIAS or IMPORTED target.
cmake_policy(VERSION 3.5)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

set(CPPUTEST_HOME /usr/local CACHE STRING "Location where CppUTest is installed")
option(COMPILE_TESTS "Compile unit tests" OFF)

add_subdirectory(src)

if(COMPILE_TESTS)
    enable_testing()

    message(STATUS "Searching for CppUTest in CPPUTEST_HOME: ${CPPUTEST_HOME}")
    set(CMAKE_PREFIX_PATH "${CPPUTEST_HOME}")
    find_package(CppUTest 3.8 REQUIRED)

    add_subdirectory(tests)
endif()

message(STATUS "
-------------------------------------------------------
Project options:
    CPPUTEST_HOME:                      ${CPPUTEST_HOME}
    CMAKE_INSTALL_PREFIX:               ${CMAKE_INSTALL_PREFIX}
    CMAKE_PREFIX_PATH:                  ${CMAKE_PREFIX_PATH}
    COMPILE_TESTS:                      ${COMPILE_TESTS}

Compiler options:
    CC:                                 ${CMAKE_C_COMPILER}
    CXX:                                ${CMAKE_CXX_COMPILER}
-------------------------------------------------------"
)
