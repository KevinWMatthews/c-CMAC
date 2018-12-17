enable_language(CXX)

add_executable(Test_Aes128Libgcrypt
    RunAllTests.cpp
    Test_Aes128Libgcrypt.cpp
)

target_link_libraries(Test_Aes128Libgcrypt
    PRIVATE
        CppUTest
        CppUTestExt
        Aes128::Aes128
)

add_test(
    NAME Test_Aes128Libgcrypt
    COMMAND Test_Aes128Libgcrypt
)
