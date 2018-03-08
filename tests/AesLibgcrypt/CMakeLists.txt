enable_language(CXX)

add_executable(TestApp_AesLibgcrypt
    RunAllTests.cpp
    Test_AesLibgcrypt.cpp
)

target_link_libraries(TestApp_AesLibgcrypt
    PRIVATE
        CppUTest
        CppUTestExt
        ${LIBGCRYPT_LIBS}
)

add_test(
    NAME Test_AesLibgcrypt
    COMMAND TestApp_AesLibgcrypt
)
