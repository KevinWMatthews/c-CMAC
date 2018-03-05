extern "C"
{
#include "AesCmac.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(CalculateNBlocks)
{
    size_t n_blocks;

    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(CalculateNBlocks, has_zero_blocks_with_message_length_zero)
{
    size_t message_length = 0;
    n_blocks = calculate_n_blocks(message_length);
    LONGS_EQUAL( 0, message_length );
}
