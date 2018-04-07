enable_language(CXX)

add_executable(UnitTests_Aes128Libgcrypt
    AllTests.cpp
    Test_Aes128Libgcrypt.cpp
)

target_link_libraries(UnitTests_Aes128Libgcrypt
    PRIVATE
        CppUTest
        CppUTestExt
        Aes128::Aes128
)

add_test(
    NAME Test_Aes128Libgcrypt
    COMMAND UnitTests_Aes128Libgcrypt
)
