enable_language(CXX)

add_executable(UnitTests_Aes128CreateParamsComparator
    RunAllTests.cpp
    Test_Aes128CreateParamsComparator.cpp
    "${CMAKE_HOME_DIRECTORY}/mocks/Aes128CreateParamsComparator.cpp"
)

target_link_libraries(UnitTests_Aes128CreateParamsComparator
    PRIVATE
        CppUTest
        CppUTestExt
        Aes128::Aes128
)

target_include_directories(UnitTests_Aes128CreateParamsComparator
    PRIVATE
        "${CMAKE_HOME_DIRECTORY}/mocks"
)

add_test(
    NAME Test_Aes128CreateParamsComparator
    COMMAND UnitTests_Aes128CreateParamsComparator
)


add_executable(UnitTests_Aes128CryptoParamsComparator
    RunAllTests.cpp
    Test_Aes128CryptoParamsComparator.cpp
    "${CMAKE_HOME_DIRECTORY}/mocks/Aes128CryptoParamsComparator.cpp"
    "${CMAKE_HOME_DIRECTORY}/mocks/Aes128CreateParamsComparator.cpp"
)

target_link_libraries(UnitTests_Aes128CryptoParamsComparator
    PRIVATE
        CppUTest
        CppUTestExt
        Aes128::Aes128
)

target_include_directories(UnitTests_Aes128CryptoParamsComparator
    PRIVATE
        "${CMAKE_HOME_DIRECTORY}/mocks"
)

add_test(
    NAME Test_Aes128CryptoParamsComparator
    COMMAND UnitTests_Aes128CryptoParamsComparator
)
