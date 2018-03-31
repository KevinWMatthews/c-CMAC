extern "C"
{
#include "CmacAesOps.h"
#include "Aes128.h"
}

#include "CppUTest/TestHarness.h"
#include <string.h>

TEST_GROUP(CopyCmacOutput)
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

TEST(CopyCmacOutput, can_copy_cipher_output_block)
{
    uint8_t expected[16] = {
        0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
        0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
    };
    uint8_t result[16] = {};
    memcpy( context.cipher_output_block, expected, sizeof(context.cipher_output_block) );

    ret = CmacAesOps_CopyCmacOutput( &context, result, sizeof(result) );
    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, result, sizeof(expected) );
}
