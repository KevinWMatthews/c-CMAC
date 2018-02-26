enable_language(C)
enable_language(CXX)

add_library(AesCmacProduction
    "${CMAKE_HOME_DIRECTORY}/include/AesCmac.h"
)
target_include_directories(AesCmacProduction
    PUBLIC
        "${CMAKE_HOME_DIRECTORY}/include"
)
SET_TARGET_PROPERTIES(AesCmacProduction PROPERTIES LINKER_LANGUAGE C)

add_library(ProductionLib::ProductionLib ALIAS AesCmacProduction)

add_executable(TestApp_AesCmac
    RunAllTests.cpp
    Test_AesCmac.cpp
    Test_AesCmacSubkeys.cpp
)

target_link_libraries(TestApp_AesCmac
    PRIVATE
        CppUTest
        ProductionLib::ProductionLib
)

add_test(
    NAME Test_AesCmac
    COMMAND TestApp_AesCmac
)
