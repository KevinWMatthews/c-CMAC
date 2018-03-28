extern "C"
{
#include "CmacAesOps.h"
}

#include "CppUTest/TestHarness.h"
#include <string.h>

TEST_GROUP(SetLastBlockIncomplete)
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

TEST(SetLastBlockIncomplete, pad_and_xor_zero_length_block_with_key_of_00s)
{
    uint8_t expected[16] = {0x80};

    memset(context.key2, 0, sizeof(context.key2));
    memset(context.nth_block, 0, sizeof(context.nth_block));
    context.is_nth_block_complete = false;

    //TODO we need the length of the last block for this to work.
    ret = CmacAesOps_SetLastBlock(&context);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, context.last_block, sizeof(expected) );
}

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

