enable_language(C)

add_library(Aes128
    Aes128.h
    Aes128_Libgcrypt.c
)
target_include_directories(Aes128
    PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}"
)
set_target_properties(Aes128 PROPERTIES
    LINKER_LANGUAGE C
)
target_link_libraries(Aes128
    PRIVATE
        libgcrypt::libgcrypt
)
add_library(Aes128::Aes128 ALIAS Aes128)
