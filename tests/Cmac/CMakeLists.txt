enable_language(CXX)

add_executable(TestApp_Cmac
    RunAllTests.cpp
    Test_AesCmac.cpp
    "${CMAKE_HOME_DIRECTORY}/mocks/Aes.cpp"
    "${CMAKE_HOME_DIRECTORY}/mocks/Aes128Comparator.cpp"
)

target_link_libraries(TestApp_Cmac
    PRIVATE
        CppUTest
        CppUTestExt
        CmacLib::CmacLib
)

add_test(
    NAME Test_Cmac
    COMMAND TestApp_Cmac
)
