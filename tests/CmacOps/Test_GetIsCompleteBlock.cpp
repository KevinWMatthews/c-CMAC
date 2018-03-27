extern "C"
{
#include "CmacAesOps.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(GetIsCompleteBlock)
{
    CMAC_AES_CONTEXT context;
    size_t message_length;
    bool is_complete_block_flag;
    int ret;

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

    ret = CmacAesOps_GetIsCompleteBlock(message_length, &context);

    LONGS_EQUAL( 0, ret );
    LONGS_EQUAL( false, context.is_nth_block_complete );
}

TEST(GetIsCompleteBlock, message_shorter_than_one_block_is_not_complete)
{
    message_length = 15;

    ret = CmacAesOps_GetIsCompleteBlock(message_length, &context);

    LONGS_EQUAL( 0, ret );
    LONGS_EQUAL( false, context.is_nth_block_complete );
}

TEST(GetIsCompleteBlock, message_exactly_one_block_long_is_complete)
{
    message_length = CMAC_AES_BYTES_IN_BLOCK;

    ret = CmacAesOps_GetIsCompleteBlock(message_length, &context);

    LONGS_EQUAL( 0, ret );
    LONGS_EQUAL( true, context.is_nth_block_complete );
}

TEST(GetIsCompleteBlock, message_between_one_and_two_blocks_long_is_not_complete)
{
    message_length = CMAC_AES_BYTES_IN_BLOCK+15;

    ret = CmacAesOps_GetIsCompleteBlock(message_length, &context);

    LONGS_EQUAL( 0, ret );
    LONGS_EQUAL( false, context.is_nth_block_complete );
}

TEST(GetIsCompleteBlock, message_exactly_two_blocks_long_is_complete)
{
    message_length = CMAC_AES_BYTES_IN_BLOCK*2;

    ret = CmacAesOps_GetIsCompleteBlock(message_length, &context);

    LONGS_EQUAL( 0, ret );
    LONGS_EQUAL( true, context.is_nth_block_complete );
}
