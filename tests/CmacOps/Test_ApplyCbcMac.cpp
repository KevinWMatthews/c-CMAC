extern "C"
{
#include "CmacOps.h"
#include "Aes.h"
#include "Aes128.h"
#include "Mock_Aes128.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Aes128Comparator.h"
#include "Aes128CryptoParamsComparator.h"

TEST_GROUP(ApplyCbcMac)
{
    Aes128CryptoParamsComparator crypto_comparator;
    // Aes128Comparator comparator;
    size_t n_blocks;
    bool is_complete_block_flag;
    int ret;

    void setup()
    {
        mock().strictOrder();
    }

    void teardown()
    {
        mock().checkExpectations();
        mock().clear();
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
    ret = CmacOps_ApplyCbcMac(key, NULL, 1, X, Y);

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

    ret = CmacOps_FinishCbcMac1(M_last, X, Y);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, Y, sizeof(expected) );
}

#if 0
TEST(ApplyCbcMac, finish_zero_length_message_part_2)
{
    uint8_t key[16] = {};
    uint8_t Y[16] = {0x80};
    uint8_t T[16] = {};

    // Calculated expected using online tool
    uint8_t expected[16] = {
        0x3A, 0xD7, 0x8E, 0x72, 0x6C, 0x1E, 0xC0, 0x2B,
        0x7E, 0xBF, 0xE9, 0x2B, 0x23, 0xD9, 0xEC, 0x34,
    };
    // Values for mocks
    AES_KEY_128 aes_params = {};
    aes_params.key = key;
    aes_params.key_len = sizeof(key);
    aes_params.iv = zeros;
    aes_params.iv_len = sizeof(zeros);



    mock().installComparator("AES_KEY_128", comparator);
    mock().expectOneCall("Aes_Calculate128")
        .withParameterOfType("AES_KEY_128", "aes_128", &aes_params)
        .withMemoryBufferParameter("input", Y, sizeof(Y))
        .withParameter("input_len", sizeof(Y))
        .withOutputParameterReturning("output", expected, sizeof(expected))
        .withParameter("output_len", sizeof(expected))
        .andReturnValue(0);

    ret = CmacOps_FinishCbcMac2(key, Y, T);

    mock().checkExpectations();
    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, T, sizeof(expected) );
}
#endif

TEST(ApplyCbcMac, finish_zero_length_message_part_2__)
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

    //old
    AES_KEY_128 aes_params = {};
    aes_params.key = key;
    aes_params.key_len = sizeof(key);
    aes_params.iv = zeros;
    aes_params.iv_len = sizeof(zeros);

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

    mock().installComparator("AES128_CRYPTO_PARAMS", crypto_comparator);
    mock().expectOneCall("Aes128_Encrypt")
        .withParameterOfType("AES128_CRYPTO_PARAMS", "params", &crypto_params)
        .withOutputParameterReturning("output", expected, sizeof(expected))
        .withParameter("output_len", sizeof(expected))
        .andReturnValue(AES128_SUCCESS);

    ret = CmacOps_FinishCbcMac2_(aes_handle, Y, T, sizeof(T));

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, T, sizeof(expected) );
    mock().checkExpectations();
    mock().removeAllComparatorsAndCopiers();
}
