extern "C"
{
#include "CmacAesOps.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(ApplyCbcMac)
{
    CMAC_AES_CONTEXT context;
    int ret;

    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(ApplyCbcMac, apply_to_zero_length_message)
{
    ret = CmacAesOps_ApplyCbcMac(&context, NULL, 0);

    LONGS_EQUAL( 0, ret );
}
