extern "C"
{
#include "CmacAesOps.h"
#include "Aes128.h"
#include "MockAes128.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include <string.h>

TEST_GROUP(ApplyCbcMac)
{
    CMAC_AES_CONTEXT context;
    size_t n_blocks;
    bool is_complete_block_flag;
    int ret;

    void setup()
    {
        mock().strictOrder();
    }

    void teardown()
    {
    }
};

static uint8_t zeros[16] = {};

TEST(ApplyCbcMac, apply_to_zero_length_message)
{
    uint8_t key[16] = {};
    uint8_t X[16] = {};
    uint8_t Y[16] = {};
    uint8_t expected_X[16] = {0};
    uint8_t expected_Y[16] = {0};

    // A zero-length message is treated as having n=1.
    // See RFC 4493, step 3.
    ret = CmacAesOps_ApplyCbcMac(key, NULL, 1, X, Y);

    LONGS_EQUAL( 0, ret );

    // Change nothing?
    MEMCMP_EQUAL( expected_X, X, sizeof(expected_X) );
    MEMCMP_EQUAL( expected_Y, Y, sizeof(expected_Y) );
}

TEST(ApplyCbcMac, apply_cbc_xor_to_empty_block)
{
    // In reality there will never be an empty block or a key of 00's.
    // However, this is useful for testing the algorithm.
    uint8_t expected[16] = {};
    memset( context.current_cipher_block, 0, sizeof(context.current_cipher_block) );
    memset( context.last_block, 0, sizeof(context.last_block) );

    ret = CmacAesOps_ApplyCbcMac1_(&context);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, context.cipher_input_block, sizeof(expected) );
}

TEST(ApplyCbcMac, apply_cbc_xor_to_block_of_ffs)
{
    uint8_t expected[16] = {
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    };
    memset( context.current_cipher_block, 0, sizeof(context.current_cipher_block) );
    memset( context.last_block, 0xff, sizeof(context.last_block) );

    ret = CmacAesOps_ApplyCbcMac1_(&context);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, context.cipher_input_block, sizeof(expected) );
}

TEST(ApplyCbcMac, apply_cbc_aes_to_empty_block_with_key_of_00s)
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
    MEMCMP_EQUAL( expected, context.current_cipher_block, sizeof(expected) );

    MockAes128_Destroy(aes_handle);
}
