extern "C"
{
#include "CmacOps.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(GetIsCompleteBlock)
{
    size_t message_length;
    bool is_complete_block_flag;

    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(GetIsCompleteBlock, zero_length_message_is_not_complete_block)
{
    is_complete_block_flag = true;      // Set it to the wrong value
    message_length = 0;

    is_complete_block_flag = CmacOps_GetIsCompleteBlock(message_length);

    LONGS_EQUAL( false, is_complete_block_flag );
}
