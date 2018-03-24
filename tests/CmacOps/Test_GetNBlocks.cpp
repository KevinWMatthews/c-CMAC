extern "C"
{
#include "CmacAesOps.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(GetNBlocks)
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

TEST(GetNBlocks, zero_length_message)
{
    message_length = 0;
    n_blocks = CmacAesOps_GetNBlocks(message_length);
    LONGS_EQUAL( 1, n_blocks );
}

TEST(GetNBlocks, messgae_shorter_than_one_block_length)
{
    message_length = CMAC_AES_BLOCK_LENGTH-1;
    n_blocks = CmacAesOps_GetNBlocks(message_length);
    LONGS_EQUAL( 1, n_blocks );
}

TEST(GetNBlocks, message_exactly_one_block_length)
{
    message_length = CMAC_AES_BLOCK_LENGTH;
    n_blocks = CmacAesOps_GetNBlocks(message_length);
    LONGS_EQUAL( 1, n_blocks );
}

TEST(GetNBlocks, message_between_one_and_two_blocks_long)
{
    message_length = CMAC_AES_BLOCK_LENGTH+1;
    n_blocks = CmacAesOps_GetNBlocks(message_length);
    LONGS_EQUAL( 2, n_blocks );
}

TEST(GetNBlocks, message_exactly_two_blocks_long)
{
    message_length = CMAC_AES_BLOCK_LENGTH*2;
    n_blocks = CmacAesOps_GetNBlocks(message_length);
    LONGS_EQUAL( 2, n_blocks );
}

TEST(GetNBlocks, message_between_two_and_three_blocks_long)
{
    message_length = (CMAC_AES_BLOCK_LENGTH*2)+1;
    n_blocks = CmacAesOps_GetNBlocks(message_length);
    LONGS_EQUAL( 3, n_blocks );
}
