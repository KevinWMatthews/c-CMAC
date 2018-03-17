enable_language(C)

add_library(MockAes128
    "${CMAKE_HOME_DIRECTORY}/libAes128/Aes128.h"
    Mock_Aes128.cpp
)
target_include_directories(MockAes128
    PUBLIC
        "${CMAKE_HOME_DIRECTORY}/libAes128"
)
set_target_properties(MockAes128 PROPERTIES
    LINKER_LANGUAGE C
)
target_link_libraries(MockAes128
    PRIVATE
        CppUTest
        CppUTestExt
)
add_library(MockAes128::MockAes128 ALIAS MockAes128)
