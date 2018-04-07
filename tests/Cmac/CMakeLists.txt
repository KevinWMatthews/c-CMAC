enable_language(CXX)

add_executable(UnitTests_Cmac
    AllTests.cpp
    Test_CmacAes.cpp
)

target_link_libraries(UnitTests_Cmac
    PRIVATE
        CppUTest
        CppUTestExt
        CmacLib::CmacLib
)

add_test(
    NAME Test_Cmac
    COMMAND UnitTests_Cmac
)
