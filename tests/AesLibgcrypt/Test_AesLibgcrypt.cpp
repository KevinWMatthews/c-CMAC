extern "C"
{
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(AesLibgcrypt)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(AesLibgcrypt, wiring_check)
{
    FAIL("start here");
}
