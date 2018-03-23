extern "C"
{
#include "CmacAesOps.h"
#include "Aes128.h"
#include "Mock_Aes128.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(ApplyCbcMac)
{
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

TEST(ApplyCbcMac, finish_zero_length_message_part_1)
{
    uint8_t M_last[16] = {0x80};
    uint8_t X[16] = {};
    uint8_t Y[16] = {};
    uint8_t expected[16] = {0x80};

    ret = CmacAesOps_FinishCbcMac1(M_last, X, Y);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, Y, sizeof(expected) );
}

TEST(ApplyCbcMac, finish_zero_length_message_part_2)
{
    // Calculated expected using online tool
    uint8_t expected[16] = {
        0x3A, 0xD7, 0x8E, 0x72, 0x6C, 0x1E, 0xC0, 0x2B,
        0x7E, 0xBF, 0xE9, 0x2B, 0x23, 0xD9, 0xEC, 0x34,
    };

    uint8_t key[16] = {};
    uint8_t iv[16] = {};
    uint8_t Y[16] = {0x80};
    uint8_t T[16] = {};

    // Values for mocks
    AES128_STRUCT aes_struct = {};
    AES128_HANDLE aes_handle = &aes_struct;
    AES128_CRYPTO_PARAMS crypto_params = {};

    aes_struct.key = key;
    aes_struct.key_len = sizeof(key);
    aes_struct.iv = iv;
    aes_struct.iv_len = sizeof(iv);

    crypto_params.aes_handle = aes_handle;
    crypto_params.input = Y;
    crypto_params.input_len = sizeof(Y);

    mock().expectOneCall("Aes128_Encrypt")
        .withParameterOfType("AES128_CRYPTO_PARAMS", "params", &crypto_params)
        .withOutputParameterReturning("output", expected, sizeof(expected))
        .withParameter("output_len", sizeof(expected))
        .andReturnValue(AES128_SUCCESS);

    ret = CmacAesOps_FinishCbcMac2(aes_handle, Y, T, sizeof(T));

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, T, sizeof(expected) );
}
