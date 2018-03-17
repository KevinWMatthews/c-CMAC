enable_language(CXX)

add_executable(UnitTests_AesLibgcrypt
    RunAllTests.cpp
    Test_AesLibgcrypt.cpp
    "${CMAKE_HOME_DIRECTORY}/mocks/Mock_Libgcrypt.cpp"
)

target_link_libraries(UnitTests_AesLibgcrypt
    PRIVATE
        CppUTest
        CppUTestExt
        Aes128::Aes128
)

add_test(
    NAME Test_AesLibgcrypt
    COMMAND UnitTests_AesLibgcrypt
)

add_executable(UnitTests_AesLibgcrypt2
    RunAllTests.cpp
    Test_AesLibgcrypt2.cpp
)

target_link_libraries(UnitTests_AesLibgcrypt2
    PRIVATE
        CppUTest
        CppUTestExt
        Aes128::Aes128
)

add_test(
    NAME Test_AesLibgcrypt2
    COMMAND UnitTests_AesLibgcrypt2
)
