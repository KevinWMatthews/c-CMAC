enable_language(CXX)

add_executable(UnitTests_CmacOps
    RunAllTests.cpp
    Test_GenerateSubkeys.cpp
    Test_SubkeyOps.cpp
    Test_GetNBlocks.cpp
    Test_GetIsCompleteBlock.cpp
    Test_GetNthBlock.cpp
    Test_SetLastBlockIncomplete.cpp
    Test_ApplyCbcMac.cpp
)

target_include_directories(UnitTests_CmacOps
    PRIVATE
        "${CMAKE_HOME_DIRECTORY}/mocks"
)

target_link_libraries(UnitTests_CmacOps
    PRIVATE
        CppUTest
        CppUTestExt
        CmacOpsLib::CmacOpsLib
        MockAes128::MockAes128
        MockAes128Comparators::MockAes128Comparators
)

add_test(
    NAME Test_CmacOps
    COMMAND UnitTests_CmacOps
)
