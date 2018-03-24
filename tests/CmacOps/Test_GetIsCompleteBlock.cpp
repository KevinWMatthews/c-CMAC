extern "C"
{
#include "CmacAesOps.h"
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
    message_length = 0;

    is_complete_block_flag = CmacAesOps_GetIsCompleteBlock(message_length);

    LONGS_EQUAL( false, is_complete_block_flag );
}

TEST(GetIsCompleteBlock, message_shorter_than_one_block_is_not_complete)
{
    message_length = 15;

    is_complete_block_flag = CmacAesOps_GetIsCompleteBlock(message_length);

    LONGS_EQUAL( false, is_complete_block_flag );
}

TEST(GetIsCompleteBlock, message_exactly_one_block_long_is_complete)
{
    message_length = CMAC_AES_BLOCK_LENGTH;

    is_complete_block_flag = CmacAesOps_GetIsCompleteBlock(message_length);

    LONGS_EQUAL( true, is_complete_block_flag );
}

TEST(GetIsCompleteBlock, message_between_one_and_two_blocks_long_is_not_complete)
{
    message_length = CMAC_AES_BLOCK_LENGTH+15;

    is_complete_block_flag = CmacAesOps_GetIsCompleteBlock(message_length);

    LONGS_EQUAL( false, is_complete_block_flag );
}

TEST(GetIsCompleteBlock, message_exactly_two_blocks_long_is_complete)
{
    message_length = CMAC_AES_BLOCK_LENGTH*2;

    is_complete_block_flag = CmacAesOps_GetIsCompleteBlock(message_length);

    LONGS_EQUAL( true, is_complete_block_flag );
}
