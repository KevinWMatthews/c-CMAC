enable_language(CXX)

add_executable(TestApp_AesLibgcrypt
    RunAllTests.cpp
    Test_AesLibgcrypt.cpp
    "${CMAKE_HOME_DIRECTORY}/mocks/Mock_Libgcrypt.cpp"
)

target_link_libraries(TestApp_AesLibgcrypt
    PRIVATE
        CppUTest
        CppUTestExt
        Aes128::Aes128
)

add_test(
    NAME Test_AesLibgcrypt
    COMMAND TestApp_AesLibgcrypt
)
