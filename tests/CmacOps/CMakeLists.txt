enable_language(CXX)

add_executable(Test_CmacOps
    RunAllTests.cpp
    Test_GenerateSubkeys.cpp
    Test_SubkeyOps.cpp
    Test_GetNBlocks.cpp
    Test_GetIsCompleteBlock.cpp
    Test_GetNthBlock.cpp
    Test_SetLastBlockIncomplete.cpp
    Test_SetLastBlockComplete.cpp
    Test_ApplyCbcMac.cpp
)

target_include_directories(Test_CmacOps
    PRIVATE
        "${CMAKE_HOME_DIRECTORY}/mocks"
)

target_link_libraries(Test_CmacOps
    PRIVATE
        CppUTest
        CppUTestExt
        CmacOpsLib::CmacOpsLib
        MockAes128::MockAes128
        MockAes128Comparators::MockAes128Comparators
)

add_test(
    NAME Test_CmacOps
    COMMAND Test_CmacOps
)
