extern "C"
{
#include "CmacAesOps.h"
}

#include "CppUTest/TestHarness.h"
#include <string.h>

TEST_GROUP(ApplyCbcXor)
{
    CMAC_AES_CONTEXT context;
    int ret;

    void setup()
    {
    }

    void teardown()
    {
    }
};

// In reality there will never be an empty block or a key of 00's.
// These cases are contrived but are useful for testing the algorithm.


TEST(ApplyCbcXor, apply_cbc_xor_to_empty_block)
{
    uint8_t expected[16] = {};

    memset( context.cipher_output_block, 0, sizeof(context.cipher_output_block) );
    memset( context.last_block, 0, sizeof(context.last_block) );

    ret = CmacAesOps_ApplyCbcXor(&context);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, context.cipher_input_block, sizeof(expected) );
}

TEST(ApplyCbcXor, apply_cbc_xor_to_block_of_ffs)
{
    uint8_t expected[16] = {
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    };

    memset( context.cipher_output_block, 0, sizeof(context.cipher_output_block) );
    memset( context.last_block, 0xff, sizeof(context.last_block) );

    ret = CmacAesOps_ApplyCbcXor(&context);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, context.cipher_input_block, sizeof(expected) );
}
