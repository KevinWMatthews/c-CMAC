extern "C"
{
#include "CmacAesOps.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(SetLastBlockComplete)
{
    int ret;

    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(SetLastBlockComplete, xor_block_of_00s_with_key_of_00s)
{
    uint8_t expected[16] = {};
    uint8_t K1[16] = {};
    uint8_t nth_block[16] = {};
    uint8_t actual[16] = {};

    ret = CmacAesOps_SetLastBlockForComplete(nth_block, K1, actual);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
}
