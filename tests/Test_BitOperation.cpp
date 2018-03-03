extern "C"
{
#include "BitOperation.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(LeftShiftOne)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(LeftShiftOne, shift_on_zero_byte_has_no_effect)
{
    uint8_t expected[1] = {0};
    uint8_t input[1] = {0};
    uint8_t output[1] = {0};
    int ret;

    ret = BitOperation_CircularShiftLeft( 1, input, sizeof(input), output, sizeof(output) );

    MEMCMP_EQUAL( expected, output, sizeof(expected) );
    LONGS_EQUAL( 0, ret );
}
