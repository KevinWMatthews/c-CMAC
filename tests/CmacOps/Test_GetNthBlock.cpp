extern "C"
{
#include "CmacOps.h"
}

#include "CppUTest/TestHarness.h"
#include <string.h>

TEST_GROUP(GetNthBlock)
{
    int ret;
    size_t M_len;
    size_t block_num;

    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(GetNthBlock, returns_zeros_for_zero_length_message)
{
    uint8_t M[16] = {0};
    uint8_t M_n[16] = {0};
    uint8_t expected[16] = {0};

    M_len = 0;
    block_num = 1;

    ret = CmacOps_GetNthBlock(M, M_len, block_num, M_n);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, M_n, sizeof(expected) );
}

TEST(GetNthBlock, clear_M_n_for_zero_length_message)
{
    uint8_t M[16] = {0};
    uint8_t M_n[16] = {};
    uint8_t expected[16] = {0};

    M_len = 0;
    block_num = 1;
    memset(M_n, 0x55, sizeof(M_n));

    ret = CmacOps_GetNthBlock(M, M_len, block_num, M_n);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, M_n, sizeof(expected) );
}

TEST(GetNthBlock, fail_if_block_number_is_not_in_message)
{
    uint8_t M[16] = {0};
    uint8_t M_n[16] = {};

    M_len = 0;
    block_num = 2;      // Off the end of the message
    memset(M_n, 0x55, sizeof(M_n));

    ret = CmacOps_GetNthBlock(M, M_len, block_num, M_n);

    LONGS_EQUAL( -1, ret );
}
