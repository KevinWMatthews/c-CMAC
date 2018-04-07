enable_language(CXX)

# AES Create params comparator
add_executable(UnitTests_Aes128CreateParamsComparator
    AllTests.cpp
    Test_Aes128CreateParamsComparator.cpp
    "${CMAKE_HOME_DIRECTORY}/mocks/Aes128CreateParamsComparator.h"
    "${CMAKE_HOME_DIRECTORY}/mocks/Aes128CreateParamsComparator.cpp"
)

target_link_libraries(UnitTests_Aes128CreateParamsComparator
    PRIVATE
        CppUTest
        CppUTestExt
        MockAes128::MockAes128
)

target_include_directories(UnitTests_Aes128CreateParamsComparator
    PRIVATE
        "${CMAKE_HOME_DIRECTORY}/mocks"
)

add_test(
    NAME Test_Aes128CreateParamsComparator
    COMMAND UnitTests_Aes128CreateParamsComparator
)


# AES handle comparator
add_executable(UnitTests_Aes128Comparator
    AllTests.cpp
    Test_Aes128Comparator.cpp
    "${CMAKE_HOME_DIRECTORY}/mocks/Aes128Comparator.h"
    "${CMAKE_HOME_DIRECTORY}/mocks/Aes128Comparator.cpp"
)

target_link_libraries(UnitTests_Aes128Comparator
    PRIVATE
        CppUTest
        CppUTestExt
        MockAes128::MockAes128
)

target_include_directories(UnitTests_Aes128Comparator
    PRIVATE
        "${CMAKE_HOME_DIRECTORY}/mocks"
)

add_test(
    NAME Test_Aes128Comparator
    COMMAND UnitTests_Aes128Comparator
)


# AES crypto params comparator
add_executable(UnitTests_Aes128CryptoParamsComparator
    AllTests.cpp
    Test_Aes128CryptoParamsComparator.cpp
    "${CMAKE_HOME_DIRECTORY}/mocks/Aes128Comparator.h"
    "${CMAKE_HOME_DIRECTORY}/mocks/Aes128Comparator.cpp"
    "${CMAKE_HOME_DIRECTORY}/mocks/Aes128CryptoParamsComparator.h"
    "${CMAKE_HOME_DIRECTORY}/mocks/Aes128CryptoParamsComparator.cpp"
)

target_link_libraries(UnitTests_Aes128CryptoParamsComparator
    PRIVATE
        CppUTest
        CppUTestExt
        MockAes128::MockAes128
)

target_include_directories(UnitTests_Aes128CryptoParamsComparator
    PRIVATE
        "${CMAKE_HOME_DIRECTORY}/mocks"
)

add_test(
    NAME Test_Aes128CryptoParamsComparator
    COMMAND UnitTests_Aes128CryptoParamsComparator
)
