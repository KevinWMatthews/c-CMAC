cmake_minimum_required(VERSION 3.5)

project(AesCmac VERSION 0.0.1)

enable_language(C)

# Specify CMake version 3.5 to enable:
#   CMP0028 - Double colon in target name means ALIAS or IMPORTED target.
cmake_policy(VERSION 3.5)

# Search CMAKE_MODULE_PATH for Find<library>.cmake files
set(CMAKE_MODULE_PATH "${CMAKE_HOME_DIRECTORY}/cmake/modules")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

option(USE_LIBGCRYPT "Use libgcrypt for AES-128" ON)
set(LIBGCRYPT_HOME /usr/local CACHE PATH "Location where libgcrypt is installed")
if (USE_LIBGCRYPT)
    list(APPEND CMAKE_PREFIX_PATH "${LIBGCRYPT_HOME}")
endif()

option(COMPILE_TESTS "Compile unit tests" OFF)
set(CPPUTEST_HOME /usr/local CACHE PATH "Location where CppUTest is installed")
if(COMPILE_TESTS)
    list(APPEND CMAKE_PREFIX_PATH "${CPPUTEST_HOME}")
endif()

if(USE_LIBGCRYPT)
    find_package(libgcrypt 1.8.2 REQUIRED)
    add_subdirectory(libAes128)
    #TODO add_subdirectory for tests
endif()

add_subdirectory(src)

if(COMPILE_TESTS)
    enable_testing()
    find_package(CppUTest 3.8 REQUIRED)
    add_subdirectory(tests)
endif()
