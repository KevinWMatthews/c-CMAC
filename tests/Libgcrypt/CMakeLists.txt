enable_language(C)
enable_language(CXX)

# Add unit tests
add_executable(Test_Libgcrypt
    RunAllTests.cpp
    Test_Libgcrypt_Init.cpp
    Libgcrypt_TestHelper.h
    Test_Libgcrypt_CreateCipherHandle.cpp
    Test_Libgcrypt_AesEncrypt.cpp
)

target_link_libraries(Test_Libgcrypt
    PRIVATE
        CppUTest
        CppUTestExt
        libgcrypt::libgcrypt
)

add_test(
    NAME Test_Libgcrypt
    COMMAND Test_Libgcrypt
)


# Add test application
add_executable(TestApp_Libgcrypt
    TestApp_Libgcrypt.c
)
target_link_libraries(TestApp_Libgcrypt
    PRIVATE
        libgcrypt::libgcrypt
)
