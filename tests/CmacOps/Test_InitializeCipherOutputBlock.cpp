extern "C"
{
#include "CmacAesOps.h"
#include "Aes128.h"
}

#include "CppUTest/TestHarness.h"
#include <string.h>

TEST_GROUP(InitializeCipherOutputblock)
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

TEST(InitializeCipherOutputblock, initialize_clears_block)
{
    uint8_t expected[16] = {0};
    memset( context.cipher_output_block, 0xff, sizeof(context.cipher_output_block) );   // garbage

    ret = CmacAesOps_InitializeCipherOutputBlock(&context);
    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, context.cipher_output_block, sizeof(expected) );
}
