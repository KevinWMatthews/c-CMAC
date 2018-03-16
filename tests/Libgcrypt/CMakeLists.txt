enable_language(C)

add_executable(TestApp_Libgcrypt
    TestApp_Libgcrypt.c
)
target_link_libraries(TestApp_Libgcrypt
    PRIVATE
        libgcrypt::libgcrypt
)
