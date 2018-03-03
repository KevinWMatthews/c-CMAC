extern "C"
{
#include "BitOperation.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(LeftShiftOne)
{
    int ret;

    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(LeftShiftOne, one_byte_shift_all_zeros)
{
    uint8_t expected[1] = {0};
    uint8_t input[1] = {0};
    uint8_t output[1] = {0};

    ret = BitOperation_CircularShiftLeft( 1, input, sizeof(input), output, sizeof(output) );

    MEMCMP_EQUAL( expected, output, sizeof(expected) );
    LONGS_EQUAL( 0, ret );
}

TEST(LeftShiftOne, one_byte_shift_a_single_bit)
{
    uint8_t expected[1] = {0b10};
    uint8_t input[1] = {0b1};
    uint8_t output[1] = {0};

    ret = BitOperation_CircularShiftLeft( 1, input, sizeof(input), output, sizeof(output) );

    MEMCMP_EQUAL( expected, output, sizeof(expected) );
    LONGS_EQUAL( 0, ret );
}

TEST(LeftShiftOne, one_byte_single_bit_wraps_around)
{
    uint8_t expected[1] = {0b1};
    uint8_t input[1] = {0x80};
    uint8_t output[1] = {0};

    ret = BitOperation_CircularShiftLeft( 1, input, sizeof(input), output, sizeof(output) );

    MEMCMP_EQUAL( expected, output, sizeof(expected) );
    LONGS_EQUAL( 0, ret );
}

TEST(LeftShiftOne, one_byte_does_not_clear_bits)
{
    uint8_t expected[1] = {0xff};
    uint8_t input[1] = {0xff};
    uint8_t output[1] = {0};

    ret = BitOperation_CircularShiftLeft( 1, input, sizeof(input), output, sizeof(output) );

    MEMCMP_EQUAL( expected, output, sizeof(expected) );
    LONGS_EQUAL( 0, ret );
}
