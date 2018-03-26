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

TEST(SetLastBlockIncomplete, pad_and_xor_completely_empty_block)
{
    uint8_t M_n[16] = {};
    uint8_t K2[16] = {};
    uint8_t M_last[16] = {};
    uint8_t expected[16] = {0x80};

    ret = CmacAesOps_SetLastBlockForIncomplete(M_n, K2, M_last);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, M_last, sizeof(expected) );
}

// This doesn't enforce the correct behavior - this block is complete.
// Test the entire block so we can be sure that we operate on all bits.
TEST(SetLastBlockIncomplete, pad_and_xor_incomplete_block_of_ffs)
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

    ret = CmacAesOps_SetLastBlockForIncomplete(M_n, K2, M_last);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, M_last, sizeof(expected) );
}

