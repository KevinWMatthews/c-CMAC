extern "C"
{
#include "CmacAesSubkeys.h"
#include "Aes128.h"
#include "Mock_Aes128.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(CmacAesSubkeys)
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

TEST(CmacAesSubkeys, generate_subkeys_for_rfc_examples)
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

    // Actual
    uint8_t actual_K1[16] = {};
    uint8_t actual_K2[16] = {};

    // Input
    AES128_STRUCT aes_struct = {};
    AES128_HANDLE aes_handle = &aes_struct;
    AES128_CRYPTO_PARAMS crypto_params = {};
    uint8_t key[16] = {
        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c,
    };
    uint8_t iv[16] = {};
    uint8_t input[16] = {};

    // Mock value for AES encryption
    uint8_t L[16] = {
        0x7d, 0xf7, 0x6b, 0x0c, 0x1a, 0xb8, 0x99, 0xb3,
        0x3e, 0x42, 0xf0, 0x47, 0xb9, 0x1b, 0x54, 0x6f,
    };

    aes_struct.key = key;
    aes_struct.key_len = sizeof(key);
    aes_struct.iv = iv;
    aes_struct.iv_len = sizeof(iv);

    crypto_params.aes_handle = aes_handle;
    crypto_params.input = input;
    crypto_params.input_len = sizeof(input);

    mock().expectOneCall("Aes128_Encrypt")
        .withParameterOfType("AES128_CRYPTO_PARAMS", "params", &crypto_params)
        .withOutputParameterReturning("output", L, sizeof(L))
        .withParameter("output_len", sizeof(L))
        .andReturnValue(AES128_SUCCESS);

    ret = CmacAes_GenerateSubkeys(aes_handle,
            actual_K1, sizeof(actual_K1),
            actual_K2, sizeof(actual_K2));

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected_K1, actual_K1, sizeof(expected_K1) );
    MEMCMP_EQUAL( expected_K2, actual_K2, sizeof(expected_K2) );
}
