extern "C"
{
#include "CmacAesOps.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(GetNBlocks)
{
    CMAC_AES_CONTEXT context;
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

TEST(GetNBlocks, zero_length_message_has_one_block)
{
    message_length = 0;
    ret = CmacAesOps_GetNBlocks(message_length, &context);
    LONGS_EQUAL( 0, ret );
    LONGS_EQUAL( 1, context.n_blocks );
}

TEST(GetNBlocks, messgae_shorter_than_one_block_has_one_block)
{
    message_length = CMAC_AES_BLOCK_LENGTH - 1;
    ret = CmacAesOps_GetNBlocks(message_length, &context);
    LONGS_EQUAL( 0, ret );
    LONGS_EQUAL( 1, context.n_blocks );
}

TEST(GetNBlocks, message_exactly_one_block_length_has_one_block)
{
    message_length = CMAC_AES_BLOCK_LENGTH;
    ret = CmacAesOps_GetNBlocks(message_length, &context);
    LONGS_EQUAL( 0, ret );
    LONGS_EQUAL( 1, context.n_blocks );
}

TEST(GetNBlocks, message_between_one_and_two_blocks_long_has_two_blocks)
{
    message_length = CMAC_AES_BLOCK_LENGTH + 1;
    ret = CmacAesOps_GetNBlocks(message_length, &context);
    LONGS_EQUAL( 0, ret );
    LONGS_EQUAL( 2, context.n_blocks );
}

TEST(GetNBlocks, message_exactly_two_blocks_long)
{
    message_length = CMAC_AES_BLOCK_LENGTH * 2;
    ret = CmacAesOps_GetNBlocks(message_length, &context);
    LONGS_EQUAL( 0, ret );
    LONGS_EQUAL( 2, context.n_blocks );
}

TEST(GetNBlocks, message_between_two_and_three_blocks_long)
{
    message_length = (CMAC_AES_BLOCK_LENGTH * 2) + 1;
    ret = CmacAesOps_GetNBlocks(message_length, &context);
    LONGS_EQUAL( 0, ret );
    LONGS_EQUAL( 3, context.n_blocks );
}
