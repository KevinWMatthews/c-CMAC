extern "C"
{
#include "CmacAesOps.h"
}

#include "CppUTest/TestHarness.h"
#include <string.h>

TEST_GROUP(GetNthBlock)
{
    size_t bytes_in_msg;
    size_t num_blocks;
    size_t num_trailing_bytes;
    int ret;

    void setup()
    {
    }

    void teardown()
    {
    }
};

void set_up_message(uint8_t *msg, size_t bytes_in_msg)
{
    int i;

    for (i = 0; i < bytes_in_msg; i++)
    {
        msg[i] = i;
    }
}

// Set the first nibble to something that is unique to the block number.
// This allows us to easily distinguish between various blocks as well as
// an empty byte.
uint8_t set_first_nibble_from_block_number(size_t num_blocks)
{
    return (num_blocks-1) * 0x10;
}

// Set up what we expect the Nth block to be.
// Pass in the buffer expected and the number of the Nth block.
void incomplete_nth_block_set_up_expected(uint8_t expected[16], size_t num_blocks, size_t num_trailing_bytes)
{
    int i;

    for (i = 0; i < num_trailing_bytes; i++)
    {
        expected[i] = set_first_nibble_from_block_number(num_blocks) + i;
    }
}

void complete_nth_block_set_up_expected(uint8_t expected[16], size_t num_blocks)
{
    int i;

    for (i = 0; i < 16; i++)
    {
        expected[i] = set_first_nibble_from_block_number(num_blocks) + i;
    }
}

// Fill it with garbage so that we can tell if it changed
void set_up_actual_nth_block(uint8_t nth_block[16])
{
    memset(nth_block, 0x55, 16);
}


TEST(GetNthBlock, get_all_zeros_from_zero_length_message)
{
    uint8_t expected[16] = {0};
    uint8_t nth_block[16] = {0};
    uint8_t *msg = NULL;

    bytes_in_msg = 0;
    num_blocks = 1;     // Special case
    num_trailing_bytes = 0;

    // Message is NULL
    // Expected is all zeros
    set_up_actual_nth_block(nth_block);

    ret = CmacAesOps_GetNthBlock(msg, bytes_in_msg, nth_block);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, nth_block, sizeof(expected) );
}

TEST(GetNthBlock, get_single_trailing_byte_from_a_incomplete_one_block_message)
{
    uint8_t expected[16] = {0xff};
    uint8_t actual[16] = {};
    uint8_t msg[1] = {0xff};

    bytes_in_msg = sizeof(msg);
    num_blocks = 1;
    num_trailing_bytes = 1;

    ret = CmacAesOps_GetNthBlock(msg, bytes_in_msg, actual);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
}

TEST(GetNthBlock, get_several_trailing_bytes_from_incomplete_one_block_message)
{
    uint8_t expected[16] = {};
    uint8_t actual[16] = {};
    uint8_t msg[15] = {};

    bytes_in_msg = sizeof(msg);
    num_blocks = 1;
    num_trailing_bytes = 15;

    set_up_message(msg, bytes_in_msg);
    incomplete_nth_block_set_up_expected(expected, num_blocks, num_trailing_bytes);
    set_up_actual_nth_block(actual);

    ret = CmacAesOps_GetNthBlock(msg, bytes_in_msg, actual);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
}

TEST(GetNthBlock, get_complete_block_from_complete_one_block_message)
{
    uint8_t expected[16] = {};
    uint8_t actual[16] = {};
    uint8_t msg[16] = {};

    bytes_in_msg = sizeof(msg);
    num_blocks = 1;
    num_trailing_bytes = 0;

    set_up_message(msg, bytes_in_msg);
    complete_nth_block_set_up_expected(expected, num_blocks);
    set_up_actual_nth_block(actual);

    ret = CmacAesOps_GetNthBlock(msg, bytes_in_msg, actual);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
}

TEST(GetNthBlock, get_trailing_bytes_from_incomplete_two_block_message)
{
    uint8_t expected[CMAC_AES_BLOCK_LENGTH] = {};
    uint8_t actual[CMAC_AES_BLOCK_LENGTH] = {};
    uint8_t msg[CMAC_AES_BLOCK_LENGTH + 1] = {};

    bytes_in_msg = sizeof(msg);
    num_blocks = 2;
    num_trailing_bytes = 1;

    set_up_message(msg, bytes_in_msg);
    incomplete_nth_block_set_up_expected(expected, num_blocks, num_trailing_bytes);
    set_up_actual_nth_block(actual);

    ret = CmacAesOps_GetNthBlock(msg, bytes_in_msg, actual);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
}

TEST(GetNthBlock, get_complete_last_block_from_complete_two_block_message)
{
    uint8_t expected[CMAC_AES_BLOCK_LENGTH] = {};
    uint8_t actual[CMAC_AES_BLOCK_LENGTH] = {};
    uint8_t msg[CMAC_AES_BLOCK_LENGTH * 2] = {};

    bytes_in_msg = sizeof(msg);
    num_blocks = 2;
    num_trailing_bytes = 0;

    set_up_message(msg, bytes_in_msg);
    complete_nth_block_set_up_expected(expected, num_blocks);
    set_up_actual_nth_block(actual);

    ret = CmacAesOps_GetNthBlock(msg, bytes_in_msg, actual);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
}

TEST(GetNthBlock, get_trailing_bytes_from_incomplete_three_block_message)
{
    uint8_t expected[CMAC_AES_BLOCK_LENGTH] = {};
    uint8_t actual[CMAC_AES_BLOCK_LENGTH] = {};
    uint8_t msg[CMAC_AES_BLOCK_LENGTH * 2 + 1] = {};

    bytes_in_msg = sizeof(msg);
    num_blocks = 3;
    num_trailing_bytes = 1;

    set_up_message(msg, bytes_in_msg);
    incomplete_nth_block_set_up_expected(expected, num_blocks, num_trailing_bytes);
    set_up_actual_nth_block(actual);

    ret = CmacAesOps_GetNthBlock(msg, bytes_in_msg, actual);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
}

TEST(GetNthBlock, get_complete_last_block_from_complete_three_block_message)
{
    uint8_t expected[CMAC_AES_BLOCK_LENGTH] = {};
    uint8_t actual[CMAC_AES_BLOCK_LENGTH] = {};
    uint8_t msg[CMAC_AES_BLOCK_LENGTH * 3] = {};

    bytes_in_msg = sizeof(msg);
    num_blocks = 3;
    num_trailing_bytes = 0;

    set_up_message(msg, bytes_in_msg);
    complete_nth_block_set_up_expected(expected, num_blocks);
    set_up_actual_nth_block(actual);

    ret = CmacAesOps_GetNthBlock(msg, bytes_in_msg, actual);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
}

TEST(GetNthBlock, do_not_segfault_with_null_message)
{
    uint8_t expected[16] = {0};
    uint8_t nth_block[16] = {0};
    uint8_t *msg = NULL;

    bytes_in_msg = 1;   // Not valid - msg pointer is NULL
    num_blocks = 1;     // Special case
    num_trailing_bytes = 0;

    // Message is NULL
    // Expected is all zeros
    set_up_actual_nth_block(nth_block);

    ret = CmacAesOps_GetNthBlock(msg, bytes_in_msg, nth_block);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, nth_block, sizeof(expected) );
}
