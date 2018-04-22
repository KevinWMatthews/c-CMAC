extern "C"
{
#include "CmacAesOps.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(ApplyCbcMac)
{
    CMAC_AES_CONTEXT context;
    int ret;

    void setup()
    {
        //TODO need to initialize AES keys and such
    }

    void teardown()
    {
    }
};

static uint8_t zeros[16] = {};

TEST(ApplyCbcMac, does_not_opeate_on_zero_length_message)
{
    ret = CmacAesOps_ApplyCbcMac(&context, NULL, 0);

    LONGS_EQUAL( 0, ret );
    LONGS_EQUAL( 0, context.current_block_number );
    // MEMCMP_EQUAL( zeros, context.cipher_input_block, 16 );
}

TEST(ApplyCbcMac, does_not_operate_on_single_block_message)
{
    uint8_t message[16] = {};

    ret = CmacAesOps_ApplyCbcMac(&context, message, sizeof(message));

    LONGS_EQUAL( 0, ret );
    LONGS_EQUAL( 0, context.current_block_number );
}

TEST(ApplyCbcMac, operates_on_first_block_of_two_block_message)
{
    uint8_t message[17] = {};

    ret = CmacAesOps_ApplyCbcMac(&context, message, sizeof(message));

    LONGS_EQUAL( 0, ret );
    LONGS_EQUAL( 1, context.current_block_number );
}
