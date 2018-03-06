enable_language(CXX)

add_executable(TestApp_ByteArrayOps
    RunAllTests.cpp
    Test_CircularShiftLeftOne.cpp
    Test_LogicalShiftLeftOne.cpp
    Test_Xor.cpp
)

target_link_libraries(TestApp_ByteArrayOps
    PRIVATE
        CppUTest
        CppUTestExt
        ByteArrayOpsLib::ByteArrayOpsLib
)

add_test(
    NAME Test_ByteArrayOps
    COMMAND TestApp_ByteArrayOps
)
