extern "C"
{
#include "CmacAesOps.h"
#include "Aes128.h"
#include "MockAes128.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(GenerateSubkeys)
{
    int ret;

    void setup()
    {
        mock().strictOrder();
    }

    void teardown()
    {
    }
};

TEST(GenerateSubkeys, generate_subkeys_for_rfc_examples)
{
    // Expected
    uint8_t expected_K1[16] = {
        0xfb, 0xee, 0xd6, 0x18, 0x35, 0x71, 0x33, 0x66,
        0x7c, 0x85, 0xe0, 0x8f, 0x72, 0x36, 0xa8, 0xde,
    };
    uint8_t expected_K2[16] = {
        0xf7, 0xdd, 0xac, 0x30, 0x6a, 0xe2, 0x66, 0xcc,
        0xf9, 0x0b, 0xc1, 0x1e, 0xe4, 0x6d, 0x51, 0x3b,
    };

    // Input
    uint8_t key[16] = {
        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c,
    };
    uint8_t input[16] = {};         // All zeros, from RFC

    // Actual
    CMAC_AES_CONTEXT context = {};

    // Values for mocks
    AES128_CREATE_PARAMS create_params = {};
    AES128_CRYPTO_PARAMS crypto_params = {};
    uint8_t iv[16] = {};            // All zeros, from RFC

    // Mock value for AES encryption
    uint8_t L[16] = {
        0x7d, 0xf7, 0x6b, 0x0c, 0x1a, 0xb8, 0x99, 0xb3,
        0x3e, 0x42, 0xf0, 0x47, 0xb9, 0x1b, 0x54, 0x6f,
    };

    create_params.key = key;
    create_params.key_len = sizeof(key);
    create_params.iv = iv;
    create_params.iv_len = sizeof(iv);
    context.aes_handle = MockAes128_Create(&create_params);

    crypto_params.aes_handle = context.aes_handle;
    crypto_params.input = input;
    crypto_params.input_len = sizeof(input);

    mock().expectOneCall("Aes128_Encrypt")
        .withParameterOfType("AES128_CRYPTO_PARAMS", "params", &crypto_params)
        .withOutputParameterReturning("output", L, sizeof(L))
        .withParameter("output_len", sizeof(L))
        .andReturnValue(AES128_SUCCESS);

    ret = CmacAesOps_GenerateSubkeys(&context);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected_K1, context.K1, sizeof(expected_K1) );
    MEMCMP_EQUAL( expected_K2, context.K2, sizeof(expected_K2) );

    MockAes128_Destroy(context.aes_handle);
}
