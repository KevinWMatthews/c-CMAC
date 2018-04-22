extern "C"
{
#include "CmacAesOps.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(GetBlockByNumber)
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

IGNORE_TEST(GetBlockByNumber, return_null_for_zero_length_message)
{
    ret = CmacAesOps_GetBlockByNumber(&context);
    LONGS_EQUAL( 0, ret );
    // I don't like this.
    // POINTERS_EQUAL( NULL, context->)
}
