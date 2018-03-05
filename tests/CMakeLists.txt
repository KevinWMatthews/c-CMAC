enable_language(C)
enable_language(CXX)

# Do we include AesCmac.h here?
add_library(AesCmacProduction
    "${CMAKE_HOME_DIRECTORY}/src/AesCmac.c"
    "${CMAKE_HOME_DIRECTORY}/include/AesCmac.h"
    "${CMAKE_HOME_DIRECTORY}/include/AesCmacSubkeys.h"
    "${CMAKE_HOME_DIRECTORY}/src/AesCmacSubkeys.c"
    "${CMAKE_HOME_DIRECTORY}/src/BitOperation.c"
)
target_include_directories(AesCmacProduction
    PUBLIC
        "${CMAKE_HOME_DIRECTORY}/include"
        "${CMAKE_HOME_DIRECTORY}/mocks"
)
SET_TARGET_PROPERTIES(AesCmacProduction PROPERTIES LINKER_LANGUAGE C)

add_library(ProductionLib::ProductionLib ALIAS AesCmacProduction)

add_executable(TestApp_AesCmac
    RunAllTests.cpp
    Test_AesCmac.cpp
    Test_AesCmacSubkeys.cpp
    Test_CalculateNBlocks.cpp
    Test_CircularShiftLeftOne.cpp
    Test_LogicalShiftLeftOne.cpp
    Test_Xor.cpp
    "${CMAKE_HOME_DIRECTORY}/mocks/Aes.cpp"
)

target_link_libraries(TestApp_AesCmac
    PRIVATE
        CppUTest
        CppUTestExt
        ProductionLib::ProductionLib
)

add_test(
    NAME Test_AesCmac
    COMMAND TestApp_AesCmac
)
