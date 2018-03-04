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
