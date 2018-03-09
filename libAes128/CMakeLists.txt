enable_language(C)

add_library(Aes128
    "${CMAKE_CURRENT_LIST_DIR}/Aes128.h"
    "${CMAKE_CURRENT_LIST_DIR}/Aes128.c"
)
target_include_directories(Aes128
    PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}"
)
set_target_properties(Aes128 PROPERTIES
    LINKER_LANGUAGE C
)
add_library(Aes128::Aes128 ALIAS Aes128)
