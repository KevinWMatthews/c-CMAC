extern "C"
{
#include "BitOperation.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(LogicalShiftLeftOne)
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
TEST(LogicalShiftLeftOne, one_byte_shift_all_zeros)
{
    uint8_t input[1]    = {0};
    uint8_t expected[1] = {0};
    uint8_t actual[1] = {0};

    ret = BitOperation_LogicalShiftLeftOne( input, sizeof(input), actual, sizeof(actual) );

    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
    LONGS_EQUAL( 0, ret );
}

TEST(LogicalShiftLeftOne, one_byte_shift_a_single_bit)
{
    uint8_t input[1]    = {0b01};
    uint8_t expected[1] = {0b10};
    uint8_t actual[1] = {0};

    ret = BitOperation_LogicalShiftLeftOne( input, sizeof(input), actual, sizeof(actual) );

    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
    LONGS_EQUAL( 0, ret );
}

TEST(LogicalShiftLeftOne, one_byte_single_bit_does_not_wrap_around)
{
    uint8_t input[1]    = {0x80};
    uint8_t expected[1] = {0x00};
    uint8_t actual[1] = {0};

    ret = BitOperation_LogicalShiftLeftOne( input, sizeof(input), actual, sizeof(actual) );

    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
    LONGS_EQUAL( 0, ret );
}

TEST(LogicalShiftLeftOne, one_byte_clears_lsbit_only)
{
    uint8_t input[1]    = {0xff};
    uint8_t expected[1] = {0xfe};
    uint8_t actual[1] = {0};

    ret = BitOperation_LogicalShiftLeftOne( input, sizeof(input), actual, sizeof(actual) );

    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
    LONGS_EQUAL( 0, ret );
}

/*
 * Two bytes
 */
TEST(LogicalShiftLeftOne, two_bytes_shift_all_zeros)
{
    uint8_t input[2]    = {0};
    uint8_t expected[2] = {0};
    uint8_t actual[2] = {0};

    ret = BitOperation_LogicalShiftLeftOne( input, sizeof(input), actual, sizeof(actual) );

    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
    LONGS_EQUAL( 0, ret );
}

TEST(LogicalShiftLeftOne, two_bytes_shift_a_single_bit)
{
    uint8_t input[2]    = {0b01, 0b01};
    uint8_t expected[2] = {0b10, 0b10};
    uint8_t actual[2] = {0};

    ret = BitOperation_LogicalShiftLeftOne( input, sizeof(input), actual, sizeof(actual) );

    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
    LONGS_EQUAL( 0, ret );
}

TEST(LogicalShiftLeftOne, two_bytes_shift_a_bit_between_bytes)
{
    uint8_t input[2]    = {0x00, 0x80};
    uint8_t expected[2] = {0x01, 0x00};
    uint8_t actual[2] = {0};

    ret = BitOperation_LogicalShiftLeftOne( input, sizeof(input), actual, sizeof(actual) );

    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
    LONGS_EQUAL( 0, ret );
}

TEST(LogicalShiftLeftOne, two_bytes_single_bit_does_not_wrap_around)
{
    uint8_t input[2]    = {0x80, 0x00};
    uint8_t expected[2] = {0x00, 0x00};
    uint8_t actual[2] = {0};

    ret = BitOperation_LogicalShiftLeftOne( input, sizeof(input), actual, sizeof(actual) );

    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
    LONGS_EQUAL( 0, ret );
}

TEST(LogicalShiftLeftOne, two_bytes_clears_lsbit_only)
{
    uint8_t input[2]    = {0xff, 0xff};
    uint8_t expected[2] = {0xff, 0xfe};
    uint8_t actual[2] = {0};

    ret = BitOperation_LogicalShiftLeftOne( input, sizeof(input), actual, sizeof(actual) );

    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
    LONGS_EQUAL( 0, ret );
}

/*
 * Three bytes
 */
TEST(LogicalShiftLeftOne, three_bytes_shift_all_zeros)
{
    uint8_t input[3]    = {0};
    uint8_t expected[3] = {0};
    uint8_t actual[3] = {0};

    ret = BitOperation_LogicalShiftLeftOne( input, sizeof(input), actual, sizeof(actual) );

    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
    LONGS_EQUAL( 0, ret );
}

TEST(LogicalShiftLeftOne, three_bytes_shift_a_single_bit)
{
    uint8_t input[3]    = {0b01, 0b01, 0b01};
    uint8_t expected[3] = {0b10, 0b10, 0b10};
    uint8_t actual[3] = {0};

    ret = BitOperation_LogicalShiftLeftOne( input, sizeof(input), actual, sizeof(actual) );

    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
    LONGS_EQUAL( 0, ret );
}

TEST(LogicalShiftLeftOne, three_bytes_shift_a_bit_between_bytes)
{
    uint8_t input[3]    = {0x00, 0x80, 0x80};
    uint8_t expected[3] = {0x01, 0x01, 0x00};
    uint8_t actual[3] = {0};

    ret = BitOperation_LogicalShiftLeftOne( input, sizeof(input), actual, sizeof(actual) );

    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
    LONGS_EQUAL( 0, ret );
}

TEST(LogicalShiftLeftOne, three_bytes_single_bit_does_not_wrap_around)
{
    uint8_t input[3]    = {0x80, 0x00, 0x00};
    uint8_t expected[3] = {0x00, 0x00, 0x00};
    uint8_t actual[3] = {0};

    ret = BitOperation_LogicalShiftLeftOne( input, sizeof(input), actual, sizeof(actual) );

    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
    LONGS_EQUAL( 0, ret );
}

TEST(LogicalShiftLeftOne, three_bytes_clears_lsbit_only)
{
    uint8_t input[3]    = {0xff, 0xff, 0xff};
    uint8_t expected[3] = {0xff, 0xff, 0xfe};
    uint8_t actual[3] = {0};

    ret = BitOperation_LogicalShiftLeftOne( input, sizeof(input), actual, sizeof(actual) );

    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
    LONGS_EQUAL( 0, ret );
}


/*
 * Real-world examples
 */
// This doesn't have the leading bit set
TEST(LogicalShiftLeftOne, example_from_rfc_4493)
{
    uint8_t input[16] = {
        0x7d, 0xf7, 0x6b, 0x0c, 0x1a, 0xb8, 0x99, 0xb3, 0x3e, 0x42, 0xf0, 0x47, 0xb9, 0x1b, 0x54, 0x6f,
    };
    uint8_t expected[16] = {
        0xfb, 0xee, 0xd6, 0x18, 0x35, 0x71, 0x33, 0x66, 0x7c, 0x85, 0xe0, 0x8f, 0x72, 0x36, 0xa8, 0xde,
    };
    uint8_t actual[16] = {0};

    ret = BitOperation_LogicalShiftLeftOne( input, sizeof(input), actual, sizeof(actual) );

    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
    LONGS_EQUAL( 0, ret );
}
