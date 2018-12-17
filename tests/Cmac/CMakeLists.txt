enable_language(CXX)

add_executable(Test_Cmac
    RunAllTests.cpp
    Test_CmacAes.cpp
)

target_link_libraries(Test_Cmac
    PRIVATE
        CppUTest
        CppUTestExt
        CmacLib::CmacLib
)

add_test(
    NAME Test_Cmac
    COMMAND Test_Cmac
)
