extern "C"
{
#include "CmacAesOps.h"
}

#include "CppUTest/TestHarness.h"
#include <string.h>

TEST_GROUP(SetLastBlockComplete)
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

TEST(SetLastBlockComplete, xor_block_of_00s_with_key_of_00s)
{
    uint8_t expected[16] = {};

    memset(context.key1, 0, sizeof(context.key1));
    memset(context.nth_block, 0, sizeof(context.nth_block));
    context.is_nth_block_complete = true;

    ret = CmacAesOps_SetLastBlock(&context);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, context.last_block, sizeof(expected) );
}

TEST(SetLastBlockComplete, xor_block_of_ffs_with_key_of_00s)
{
    uint8_t expected[16] = {
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    };

    memset(context.key1, 0, sizeof(context.key1));
    memset(context.nth_block, 0xff, sizeof(context.nth_block));
    context.is_nth_block_complete = true;

    ret = CmacAesOps_SetLastBlock(&context);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, context.last_block, sizeof(expected) );
}

TEST(SetLastBlockComplete, xor_block_of_00s_with_key_of_ffs)
{
    uint8_t expected[16] = {
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    };

    memset(context.key1, 0xff, sizeof(context.key1));
    memset(context.nth_block, 0, sizeof(context.nth_block));
    context.is_nth_block_complete = true;

    ret = CmacAesOps_SetLastBlock(&context);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, context.last_block, sizeof(expected) );
}

TEST(SetLastBlockComplete, xor_set_all_bits)
{
    uint8_t expected[16] = {
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    };

    memset(context.key1, 0x55, sizeof(context.key1));
    memset(context.nth_block, 0xaa, sizeof(context.nth_block));
    context.is_nth_block_complete = true;

    ret = CmacAesOps_SetLastBlock(&context);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, context.last_block, sizeof(expected) );
}
