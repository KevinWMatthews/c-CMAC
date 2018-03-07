extern "C"
{
#include "CmacOps.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(GetIsCompleteBlock)
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

TEST(GetIsCompleteBlock, message_length_zero_is_not_complete_block)
{
    is_complete_block_flag = true;      // Set it to the wrong value

    ret = get_is_complete_block(&n_blocks, &is_complete_block_flag);

    LONGS_EQUAL( 0, ret );
    LONGS_EQUAL( 1, n_blocks );
    LONGS_EQUAL( false, is_complete_block_flag );
}
