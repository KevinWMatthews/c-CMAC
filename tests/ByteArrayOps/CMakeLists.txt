enable_language(CXX)

add_executable(UnitTests_ByteArrayOps
    AllTests.cpp
    Test_CircularShiftLeftOne.cpp
    Test_LogicalShiftLeftOne.cpp
    Test_Xor.cpp
)

target_link_libraries(UnitTests_ByteArrayOps
    PRIVATE
        CppUTest
        CppUTestExt
        ByteArrayOpsLib::ByteArrayOpsLib
)

add_test(
    NAME Test_ByteArrayOps
    COMMAND UnitTests_ByteArrayOps
)
