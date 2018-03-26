extern "C"
{
#include "CmacAesOps.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(SetLastBlockComplete)
{
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
    uint8_t K1[16] = {};
    uint8_t nth_block[16] = {};
    uint8_t actual[16] = {};

    ret = CmacAesOps_SetLastBlockForComplete(nth_block, K1, actual);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
}

TEST(SetLastBlockComplete, xor_block_of_ffs_with_key_of_00s)
{
    uint8_t expected[16] = {
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    };
    uint8_t K1[16] = {};
    uint8_t nth_block[16] = {
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    };
    uint8_t actual[16] = {};

    ret = CmacAesOps_SetLastBlockForComplete(nth_block, K1, actual);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
}

TEST(SetLastBlockComplete, xor_block_of_00s_with_key_of_ffs)
{
    uint8_t expected[16] = {
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    };
    uint8_t K1[16] = {
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    };
    uint8_t nth_block[16] = {};
    uint8_t actual[16] = {};

    ret = CmacAesOps_SetLastBlockForComplete(nth_block, K1, actual);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
}

TEST(SetLastBlockComplete, xor_set_all_bits)
{
    uint8_t expected[16] = {
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    };
    uint8_t K1[16] = {
        0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
        0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
    };
    uint8_t nth_block[16] = {
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
    };
    uint8_t actual[16] = {};

    ret = CmacAesOps_SetLastBlockForComplete(nth_block, K1, actual);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
}
