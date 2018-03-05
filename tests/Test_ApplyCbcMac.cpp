extern "C"
{
#include "AesCmac.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(ApplyCbcMac)
{
    size_t n_blocks;
    bool is_complete_block_flag;
    int ret;

    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(ApplyCbcMac, apply_to_zero_length_message)
{
    uint8_t key[16] = {};
    uint8_t X[16] = {};
    uint8_t Y[16] = {};
    uint8_t expected_X[16] = {0};
    uint8_t expected_Y[16] = {0};

    // A zero-length message is treated as having n=1.
    // See RFC 4493, step 3.
    ret = apply_cbc_mac(key, NULL, 1, X, Y);

    LONGS_EQUAL( 0, ret );

    // Change nothing?
    MEMCMP_EQUAL( expected_X, X, sizeof(expected_X) );
    MEMCMP_EQUAL( expected_Y, Y, sizeof(expected_Y) );
}

TEST(ApplyCbcMac, finish_zero_length_message_part_1)
{
    uint8_t M_last[16] = {0x80};
    uint8_t X[16] = {};
    uint8_t Y[16] = {};
    uint8_t expected[16] = {0x80};

    ret = finish_cbc_mac_1(M_last, X, Y);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, Y, sizeof(expected) );
}

IGNORE_TEST(ApplyCbcMac, finish_zero_length_message_part_2)
{
    uint8_t key[16] = {};
    uint8_t Y[16] = {};
    uint8_t T[16] = {};
    uint8_t expected[16] = {};

    ret = finish_cbc_mac_2(key, Y, T);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, T, sizeof(expected) );
}
