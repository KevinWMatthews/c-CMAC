extern "C"
{
#include "CmacOps.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(SetLastBlock)
{
    int ret;

    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(SetLastBlock, pad_and_xor_incomplete_block_zeros)
{
    uint8_t M_n[16] = {};
    uint8_t K2[16] = {};
    uint8_t M_last[16] = {};
    uint8_t expected[16] = {0x80};

    ret = CmacOps_SetLastBlockForIncomplete(M_n, K2, M_last);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, M_last, sizeof(expected) );
}

TEST(SetLastBlock, pad_and_xor_incomplete_block_ffs)
{
    uint8_t M_n[16] = {};
    uint8_t K2[16] = {
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    };
    uint8_t M_last[16] = {};
    uint8_t expected[16] = {
        0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    };

    ret = CmacOps_SetLastBlockForIncomplete(M_n, K2, M_last);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, M_last, sizeof(expected) );
}

