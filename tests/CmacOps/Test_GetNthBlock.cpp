extern "C"
{
#include "CmacAesOps.h"
}

#include "CppUTest/TestHarness.h"
#include <string.h>

TEST_GROUP(GetNthBlock)
{
    size_t bytes_in_msg;
    int ret;

    void setup()
    {
    }

    void teardown()
    {
    }
};

// Set the first nibble to something that is unique to the block number.
// This allows us to easily distinguish between various blocks as well as
// an empty byte.
uint8_t get_first_nibble(size_t block_number)
{
    return 0xa0;        // Pick your favorite number
}

void set_up_message(uint8_t *msg, size_t bytes_in_msg)
{
    int i;

    for (i = 0; i < bytes_in_msg; i++)
    {
        msg[i] = i;
    }
}

// Set up what we expect the Nth block to be.
// Pass in the buffer expected and the number of the Nth block.
void set_up_expected_nth_block(uint8_t expected[16], size_t block_num, size_t num_trailing_bytes)
{
    int i;

    for (i = 0; i < num_trailing_bytes; i++)
    {
        expected[i] = i;
    }
}

// Fill it with garbage so that we know it changed
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

    set_up_message(msg, bytes_in_msg);
    set_up_expected_nth_block(expected, 1, 0);
    set_up_actual_nth_block(nth_block);

    ret = CmacAesOps_GetNthBlock(msg, bytes_in_msg, nth_block);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, nth_block, sizeof(expected) );
}

TEST(GetNthBlock, get_trailing_byte_from_a_single_byte_message)
{
    uint8_t expected[16] = {};
    uint8_t actual[16] = {};
    uint8_t msg[1] = {};
    bytes_in_msg = sizeof(msg);

    set_up_message(msg, bytes_in_msg);
    set_up_expected_nth_block(expected, 1, 1);
    set_up_actual_nth_block(actual);

    ret = CmacAesOps_GetNthBlock(msg, bytes_in_msg, actual);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
}

TEST(GetNthBlock, get_trailing_bytes_from_incomplete_one_block_message)
{
    uint8_t expected[16] = {};
    uint8_t actual[16] = {};
    uint8_t msg[15] = {};
    bytes_in_msg = sizeof(msg);

    set_up_message(msg, bytes_in_msg);
    set_up_expected_nth_block(expected, 1, 15);
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

    int i;
    for (i = 0; i < 16; i++)
    {
        expected[i] = 0xa0 + i;
        msg[i] = 0xa0 + i;
    }
    memset(actual, 0x55, sizeof(actual));

    ret = CmacAesOps_GetNthBlock(msg, bytes_in_msg, actual);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
}

TEST(GetNthBlock, get_trailing_bytes_from_incomplete_two_block_message)
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

TEST(GetNthBlock, get_complete_last_block_from_complete_two_block_message)
{
    uint8_t expected[CMAC_AES_BLOCK_LENGTH] = {};
    uint8_t nth_block[CMAC_AES_BLOCK_LENGTH] = {};
    uint8_t msg[CMAC_AES_BLOCK_LENGTH*2] = {};
    int i;
    for (i = 0; i < 16; i++)
    {
        msg[i] = 0xa0 + i;
    }
    for (i = 0; i < 16; i++)
    {
        expected[i] = 0xb0 + i;
        msg[i+16] = 0xb0 + i;
    }
    memset(nth_block, 0x55, sizeof(nth_block));

    bytes_in_msg = 32;

    ret = CmacAesOps_GetNthBlock(msg, bytes_in_msg, nth_block);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, nth_block, sizeof(expected) );
}
