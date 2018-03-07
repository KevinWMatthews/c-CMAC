enable_language(CXX)

add_executable(TestApp_CmacOps
    RunAllTests.cpp
    Test_AesCmacSubkeys.cpp
    Test_GetNBlocks.cpp
    Test_SetIsCompleteBlock.cpp
    Test_GetNthBlock.cpp
    Test_SetLastBlock.cpp
    Test_ApplyCbcMac.cpp
    "${CMAKE_HOME_DIRECTORY}/mocks/Aes.cpp"
    "${CMAKE_HOME_DIRECTORY}/mocks/Aes128Comparator.cpp"
)

target_link_libraries(TestApp_CmacOps
    PRIVATE
        CppUTest
        CppUTestExt
        CmacOpsLib::CmacOpsLib
)

add_test(
    NAME Test_CmacOps
    COMMAND TestApp_CmacOps
)
