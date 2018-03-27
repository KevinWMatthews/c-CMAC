extern "C"
{
#include "CmacAesOps.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(SetLastBlockIncomplete)
{
    int ret;

    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(SetLastBlockIncomplete, pad_and_xor_empty_block_key_zeros)
{
    uint8_t expected[16] = {0x80};
    uint8_t actual[16] = {};
    uint8_t nth_block[16] = {};
    uint8_t K2[16] = {};

    ret = CmacAesOps_SetLastBlockForIncomplete(nth_block, K2, actual);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
}

TEST(SetLastBlockIncomplete, pad_and_xor_empty_block_key_ffs)
{
    uint8_t expected[16] = {
        0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    };
    uint8_t actual[16] = {};
    uint8_t nth_block[16] = {};
    uint8_t K2[16] = {
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    };

    ret = CmacAesOps_SetLastBlockForIncomplete(nth_block, K2, actual);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
}
