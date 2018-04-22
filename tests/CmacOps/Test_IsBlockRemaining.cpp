extern "C"
{
#include "CmacAesOps.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(IsBlockRemaining)
{
    CMAC_AES_CONTEXT context;

    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(IsBlockRemaining, no_blocks_remain_for_zero_length_message)
{
    CmacAesOps_GetNBlocks(0, &context);
    LONGS_EQUAL( false, CmacAesOps_IsBlockRemaining(&context) );
}

TEST(IsBlockRemaining, no_blocks_remain_for_messages_shorter_than_single_block)
{
    CmacAesOps_GetNBlocks(15, &context);
    LONGS_EQUAL( false, CmacAesOps_IsBlockRemaining(&context) );
}

TEST(IsBlockRemaining, no_blocks_remain_for_single_block_message)
{
    CmacAesOps_GetNBlocks(16, &context);
    LONGS_EQUAL( false, CmacAesOps_IsBlockRemaining(&context) );
}

TEST(IsBlockRemaining, single_block_remains_for_single_block_message_with_trailing_bytes)
{
    CmacAesOps_GetNBlocks(17, &context);
    LONGS_EQUAL( true, CmacAesOps_IsBlockRemaining(&context) );
}
