extern "C"
{
#include "Aes128.h"
#include "Mock_Aes128.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(Aes128HandleCopier)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(Aes128HandleCopier, wiring_check)
{
    FAIL("start here");
}
