extern "C"
{
#include "CmacOps.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(CalculateNBlocks)
{
    size_t n_blocks;
    size_t message_length;
    int ret;

    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(CalculateNBlocks, zero_length_message_has_one_block)
{
    message_length = 0;
    n_blocks = calculate_n_blocks(message_length);
    LONGS_EQUAL( 1, n_blocks );
}
