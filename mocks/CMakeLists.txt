enable_language(C)
enable_language(CXX)

add_library(MockAes128
    "${CMAKE_HOME_DIRECTORY}/libAes128/Aes128.h"
    MockAes128.h
    MockAes128.cpp
)
target_include_directories(MockAes128
    PUBLIC
        "${CMAKE_HOME_DIRECTORY}/libAes128"
)
set_target_properties(MockAes128 PROPERTIES
    LINKER_LANGUAGE C
    COMPILE_FLAGS "-include CppUTest/MemoryLeakDetectorMallocMacros.h"
)
target_link_libraries(MockAes128
    PRIVATE
        CppUTest
        CppUTestExt
)
add_library(MockAes128::MockAes128 ALIAS MockAes128)

add_library(MockAes128Comparators
    "Aes128CreateParamsComparator.h"
    "Aes128CryptoParamsComparator.h"
    "Aes128Comparator.h"
    "Aes128CreateParamsComparator.cpp"
    "Aes128CryptoParamsComparator.cpp"
    "Aes128Comparator.cpp"
)
target_include_directories(MockAes128Comparators
    PUBLIC
        "${CMAKE_CURRENT_LISTS_DIRECTORY}"
)
set_target_properties(MockAes128Comparators PROPERTIES
    LINKER_LANGUAGE CXX
)
target_link_libraries(MockAes128Comparators
    PRIVATE
        CppUTest
        CppUTestExt
        MockAes128::MockAes128
)
add_library(MockAes128Comparators::MockAes128Comparators ALIAS MockAes128Comparators)
