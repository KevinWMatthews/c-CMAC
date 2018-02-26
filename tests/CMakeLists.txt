enable_language(CXX)

add_executable(TestApp_AesCmac
    RunAllTests.cpp
    Test_AesCmac.cpp
)

target_link_libraries(TestApp_AesCmac PRIVATE CppUTest)

add_test(
    NAME Test_AesCmac
    COMMAND TestApp_AesCmac
)
