extern "C"
{
#include "CmacAesOps.h"
#include "Aes128.h"
#include "MockAes128.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include <string.h>

TEST_GROUP(ApplyCbcAes)
{
    CMAC_AES_CONTEXT context;
    int ret;

    void setup()
    {
        mock().strictOrder();
    }

    void teardown()
    {
    }
};

TEST(ApplyCbcAes, apply_cbc_aes_to_empty_block_with_key_of_00s)
{
    // Calculated using online tool
    uint8_t expected[16] = {
        0x66, 0xE9, 0x4B, 0xD4, 0xEF, 0x8A, 0x2C, 0x3B,
        0x88, 0x4C, 0xFA, 0x59, 0xCA, 0x34, 0x2B, 0x2E,
    };
    memset( context.cipher_input_block, 0, sizeof(context.cipher_input_block) );

    uint8_t key[16] = {};
    uint8_t iv[16] = {};

    // Values for mocks
    AES128_HANDLE aes_handle = NULL;
    AES128_CREATE_PARAMS create_params = {};
    AES128_CRYPTO_PARAMS crypto_params = {};

    create_params.key = key;
    create_params.key_len = sizeof(key);
    create_params.iv = iv;
    create_params.iv_len = sizeof(iv);
    aes_handle = MockAes128_Create(&create_params);

    context.aes_handle = aes_handle;
    memset( context.cipher_input_block, 0, sizeof(context.cipher_input_block) );

    crypto_params.aes_handle = aes_handle;
    crypto_params.input = context.cipher_input_block;
    crypto_params.input_len = sizeof(context.cipher_input_block);

    mock().expectOneCall("Aes128_Encrypt")
        .withParameterOfType("AES128_CRYPTO_PARAMS", "params", &crypto_params)
        .withOutputParameterReturning("output", expected, sizeof(expected))
        .withParameter("output_len", sizeof(expected))
        .andReturnValue(AES128_SUCCESS);

    ret = CmacAesOps_ApplyCbcAes(&context);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, context.cipher_output_block, sizeof(expected) );

    MockAes128_Destroy(aes_handle);
}

TEST(ApplyCbcAes, apply_cbc_aes_to_block_of_ffs_with_key_of_00s)
{
    // Calculated using online tool
    uint8_t expected[16] = {
        0x3F, 0x5B, 0x8C, 0xC9, 0xEA, 0x85, 0x5A, 0x0A,
        0xFA, 0x73, 0x47, 0xD2, 0x3E, 0x8D, 0x66, 0x4E,
    };
    memset( context.cipher_input_block, 0, sizeof(context.cipher_input_block) );

    uint8_t key[16] = {};
    uint8_t iv[16] = {};

    // Values for mocks
    AES128_HANDLE aes_handle = NULL;
    AES128_CREATE_PARAMS create_params = {};
    AES128_CRYPTO_PARAMS crypto_params = {};

    create_params.key = key;
    create_params.key_len = sizeof(key);
    create_params.iv = iv;
    create_params.iv_len = sizeof(iv);
    aes_handle = MockAes128_Create(&create_params);

    context.aes_handle = aes_handle;
    memset( context.cipher_input_block, 0xff, sizeof(context.cipher_input_block) );

    crypto_params.aes_handle = aes_handle;
    crypto_params.input = context.cipher_input_block;
    crypto_params.input_len = sizeof(context.cipher_input_block);

    mock().expectOneCall("Aes128_Encrypt")
        .withParameterOfType("AES128_CRYPTO_PARAMS", "params", &crypto_params)
        .withOutputParameterReturning("output", expected, sizeof(expected))
        .withParameter("output_len", sizeof(expected))
        .andReturnValue(AES128_SUCCESS);

    ret = CmacAesOps_ApplyCbcAes(&context);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, context.cipher_output_block, sizeof(expected) );

    MockAes128_Destroy(aes_handle);
}
