enable_language(CXX)

add_executable(UnitTests_CmacOps
    RunAllTests.cpp
    Test_AesCmacSubkeys.cpp
    Test_GetNBlocks.cpp
    Test_GetIsCompleteBlock.cpp
    Test_GetNthBlock.cpp
    Test_SetLastBlock.cpp
    Test_ApplyCbcMac.cpp
    "${CMAKE_HOME_DIRECTORY}/mocks/Aes.cpp"
    "${CMAKE_HOME_DIRECTORY}/mocks/Aes128Comparator.cpp"
)

target_link_libraries(UnitTests_CmacOps
    PRIVATE
        CppUTest
        CppUTestExt
        CmacOpsLib::CmacOpsLib
)

add_test(
    NAME Test_CmacOps
    COMMAND UnitTests_CmacOps
)
