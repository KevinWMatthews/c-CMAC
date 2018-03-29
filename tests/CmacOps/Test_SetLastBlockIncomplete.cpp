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

    context.is_nth_block_complete = false;
    memset(context.key2, 0, sizeof(context.key2));
    memset(context.nth_block, 0, sizeof(context.nth_block));

    ret = CmacAesOps_SetLastBlock(&context);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, context.last_block, sizeof(expected) );
}

TEST(SetLastBlockIncomplete, pad_and_xor_zero_length_block_with_key_of_ffs)
{
    uint8_t expected[16] = {
        0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    };

    context.is_nth_block_complete = false;
    memset(context.key2, 0xff, sizeof(context.key2));
    memset(context.nth_block, 0, sizeof(context.nth_block));

    ret = CmacAesOps_SetLastBlock(&context);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, context.last_block, sizeof(expected) );
}

TEST(SetLastBlockIncomplete, pad_and_xor_single_byte_with_key_of_00s)
{
    uint8_t expected[16] = {0x55, 0x80};

    context.is_nth_block_complete = false;
    memset(context.key2, 0, sizeof(context.key2));
    memset(context.nth_block, 0, sizeof(context.nth_block));
    context.nth_block[0] = 0x55;
    context.nth_block_len = 1;

    ret = CmacAesOps_SetLastBlock(&context);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, context.last_block, sizeof(expected) );
}

TEST(SetLastBlockIncomplete, pad_and_xor_single_byte_with_key_of_ffs)
{
    uint8_t expected[16] = {
        0xaa, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    };

    context.is_nth_block_complete = false;
    memset(context.key2, 0xff, sizeof(context.key2));
    context.nth_block_len = 1;
    memset(context.nth_block, 0x55,context.nth_block_len);

    ret = CmacAesOps_SetLastBlock(&context);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, context.last_block, sizeof(expected) );
}

TEST(SetLastBlockIncomplete, pad_and_xor_larget_incomplete_block_with_key_of_ffs)
{
    uint8_t expected[16] = {
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x7f,
    };

    context.is_nth_block_complete = false;
    memset(context.key2, 0xff, sizeof(context.key2));

    context.nth_block_len = sizeof(context.nth_block) - 1;
    memset(context.nth_block, 0x55, context.nth_block_len);

    ret = CmacAesOps_SetLastBlock(&context);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, context.last_block, sizeof(expected) );
}
