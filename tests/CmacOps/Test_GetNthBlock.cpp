extern "C"
{
#include "CmacAesOps.h"
}

#include "CppUTest/TestHarness.h"
#include <string.h>

TEST_GROUP(GetNthBlock)
{
    int ret;
    size_t M_len;
    size_t block_num;

    size_t bytes_in_msg;

    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(GetNthBlock, zero_length_message_returns_block_of_zeros)
{
    uint8_t M[16] = {0};
    uint8_t M_n[16] = {0};
    uint8_t expected[16] = {0};
    memset(M_n, 0x55, sizeof(M_n));     // M_n is set to garbage

    M_len = 0;

    ret = CmacAesOps_GetNthBlock(M, M_len, M_n);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, M_n, sizeof(expected) );
}

TEST(GetNthBlock, get_one_byte_and_zeros_for_message_with_one_byte)
{
    uint8_t expected[16] = {};
    uint8_t msg[16] = {};
    uint8_t nth_block[16] = {};
    int i;

    for (i = 0; i < 15; i++)
    {
        msg[i] = 0xa0 + i;
        expected[i] = 0xa0 + i;
    }
    memset(nth_block, 0x55, sizeof(nth_block));

    bytes_in_msg = 15;

    ret = CmacAesOps_GetNthBlock(msg, bytes_in_msg, nth_block);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, nth_block, sizeof(expected) );
}

TEST(GetNthBlock, get_15_bytes_and_zeros_for_message_with_15_bytes)
{
    uint8_t expected[16] = {};
    uint8_t msg[16] = {};
    uint8_t nth_block[16] = {};
    int i;
    for (i = 0; i < 15; i++)
    {
        msg[i] = 0xa0 + i;
        expected[i] = 0xa0 + i;
    }
    memset(nth_block, 0x55, sizeof(nth_block));

    bytes_in_msg = 15;

    ret = CmacAesOps_GetNthBlock(msg, bytes_in_msg, nth_block);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, nth_block, sizeof(expected) );
}

TEST(GetNthBlock, get_complete_first_block_for_message_with_16_bytes)
{
    uint8_t expected[16] = {};
    uint8_t msg[16] = {};
    uint8_t nth_block[16] = {};
    int i;
    for (i = 0; i < 16; i++)
    {
        expected[i] = 0xa0 + i;
        msg[i] = 0xa0 + i;
    }
    memset(nth_block, 0x55, sizeof(nth_block));

    bytes_in_msg = 16;

    ret = CmacAesOps_GetNthBlock(msg, bytes_in_msg, nth_block);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, nth_block, sizeof(expected) );
}

TEST(GetNthBlock, get_single_byte_and_zeros_for_message_with_one_block_plus_one_byte)
{
    uint8_t expected[CMAC_AES_BLOCK_LENGTH] = {};
    uint8_t msg[CMAC_AES_BLOCK_LENGTH+1] = {};
    uint8_t nth_block[CMAC_AES_BLOCK_LENGTH] = {};
    int i;
    for (i = 0; i < 16; i++)
    {
        msg[i] = 0xa0 + i;
    }
    for (i = 0; i < 1; i++)
    {
        expected[i] = 0xb0 + i;
        msg[i+16] = 0xb0 + i;
    }
    memset(nth_block, 0x55, sizeof(nth_block));

    bytes_in_msg = 17;

    ret = CmacAesOps_GetNthBlock(msg, bytes_in_msg, nth_block);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, nth_block, sizeof(expected) );
}
