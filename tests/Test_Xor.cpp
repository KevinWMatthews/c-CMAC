extern "C"
{
#include "BitOperation.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(Xor)
{
    int ret;

    void setup()
    {
    }

    void teardown()
    {
    }
};

/*
 * One byte
 */
TEST(Xor, xor_all_zeros)
{
    uint8_t expected[1] = {0};
    uint8_t input1[1] = {0};
    uint8_t input2[1] = {0};
    uint8_t output[1] = {0};

    ret = BitOperation_Xor(input1, input2, 1, output);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, output, sizeof(expected) );
}

TEST(Xor, xor_all_ones)
{
    uint8_t expected[1] = {0};
    uint8_t input1[1] = {0xff};
    uint8_t input2[1] = {0xff};
    uint8_t output[1] = {0};

    ret = BitOperation_Xor(input1, input2, 1, output);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, output, sizeof(expected) );
}

TEST(Xor, xor_set_bits_from_first_input)
{
    uint8_t expected[1] = {0xff};
    uint8_t input1[1] = {0xff};
    uint8_t input2[1] = {0x00};
    uint8_t output[1] = {0};

    ret = BitOperation_Xor(input1, input2, 1, output);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, output, sizeof(expected) );
}

TEST(Xor, xor_set_bits_from_second_input)
{
    uint8_t expected[1] = {0xff};
    uint8_t input1[1] = {0x00};
    uint8_t input2[1] = {0xff};
    uint8_t output[1] = {0};

    ret = BitOperation_Xor(input1, input2, 1, output);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, output, sizeof(expected) );
}

TEST(Xor, xor_set_bits_from_both_inputs)
{
    uint8_t expected[1] = {0xff};
    uint8_t input1[1] = {0xaa};
    uint8_t input2[1] = {0x55};
    uint8_t output[1] = {0};

    ret = BitOperation_Xor(input1, input2, 1, output);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, output, sizeof(expected) );
}

/*
 * Two bytes
 */
TEST(Xor, xor_on_two_bytes_of_zeros)
{
    uint8_t expected[2] = {0};
    uint8_t input1[2] = {0};
    uint8_t input2[2] = {0};
    uint8_t output[2] = {0};

    ret = BitOperation_Xor(input1, input2, 2, output);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, output, sizeof(expected) );
}

TEST(Xor, xor_on_two_bytes_of_ones)
{
    uint8_t expected[2] = {0};
    uint8_t input1[2] = {0xff, 0xff};
    uint8_t input2[2] = {0xff, 0xff};
    uint8_t output[2] = {0};

    ret = BitOperation_Xor(input1, input2, 2, output);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, output, sizeof(expected) );
}

// Should we perform separate operations on each nibble?
TEST(Xor, xor_on_two_bytes_operates_on_both_bytes)
{
    uint8_t expected[2] = {0x00, 0xff};
    uint8_t input1[2] = {0xff, 0x00};
    uint8_t input2[2] = {0xff, 0xff};
    uint8_t output[2] = {0};

    ret = BitOperation_Xor(input1, input2, 2, output);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, output, sizeof(expected) );
}
