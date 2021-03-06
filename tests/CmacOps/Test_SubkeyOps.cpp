extern "C"
{
#include "CmacAesSubkeys.h"
#include "Aes128.h"
#include "MockAes128.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(CmacAesSubkeyOps)
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


#define MSBIT_SET           (0x80)
#define CONST_RB            (0x87)
#define SHIFTED_CONST_RB    (CONST_RB >> 1)

static uint8_t zeros[16] = {};

TEST(CmacAesSubkeyOps, K1_operate_on_all_zeros_changes_no_bits)
{
    uint8_t expected[16] = {0};
    uint8_t L[16] = {0};
    uint8_t K1[16] = {0};

    ret = CmacAesSubkeys_CalculateK1FromL( L, sizeof(L), K1, sizeof(K1) );

    LONGS_EQUAL( ret, 0 );
    MEMCMP_EQUAL( expected, K1, sizeof(expected) );
}

TEST(CmacAesSubkeyOps, left_shift_if_MSbit_L_is_zero)
{
    uint8_t expected[16] = {
        0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
        0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    };
    uint8_t L[16] = {
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    };
    uint8_t K1[16] = {0};

    ret = CmacAesSubkeys_CalculateK1FromL( L, sizeof(L), K1, sizeof(K1) );

    LONGS_EQUAL( ret, 0 );
    MEMCMP_EQUAL( expected, K1, sizeof(expected) );
}

TEST(CmacAesSubkeyOps, left_shift_and_xor_if_MSbit_L_is_one)
{
    uint8_t expected[16] = {0};
    uint8_t L[16] = {0};
    uint8_t K1[16] = {0};

    L[0] = MSBIT_SET;
    expected[15] = CONST_RB;

    ret = CmacAesSubkeys_CalculateK1FromL( L, sizeof(L), K1, sizeof(K1) );

    LONGS_EQUAL( ret, 0 );
    MEMCMP_EQUAL( expected, K1, sizeof(expected) );
}

TEST(CmacAesSubkeyOps, verify_K1_uses_xor_const_rb)
{
    uint8_t expected[16] = {0};
    uint8_t L[16] = {0};
    uint8_t K1[16] = {0};

    L[0] = MSBIT_SET;

    // The xor in the K1 calculation must clear these bits.
    L[15] = SHIFTED_CONST_RB;

    // K1 calculation must use this algorithm.
    expected[15] = (SHIFTED_CONST_RB << 1) ^ CONST_RB;

    ret = CmacAesSubkeys_CalculateK1FromL( L, sizeof(L), K1, sizeof(K1) );

    LONGS_EQUAL( ret, 0 );
    MEMCMP_EQUAL( expected, K1, sizeof(expected) );
}

TEST(CmacAesSubkeyOps, K2_operate_on_all_zeros_changes_no_bits)
{
    uint8_t expected[16] = {0};
    uint8_t K1[16] = {0};
    uint8_t K2[16] = {0};

    ret = CmacAesSubkeys_CalculateK2FromK1( K1, sizeof(K1), K2, sizeof(K2) );

    LONGS_EQUAL( ret, 0 );
    MEMCMP_EQUAL( expected, K2, sizeof(expected) );
}

TEST(CmacAesSubkeyOps, K2_left_shift_only_if_MSB_K1_is_zero)
{
    uint8_t expected[16] = {
        0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
        0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    };
    uint8_t K1[16] = {
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    };
    uint8_t K2[16] = {0};

    ret = CmacAesSubkeys_CalculateK2FromK1( K1, sizeof(K1), K2, sizeof(K2) );

    LONGS_EQUAL( ret, 0 );
    MEMCMP_EQUAL( expected, K2, sizeof(expected) );
}

TEST(CmacAesSubkeyOps, K2_left_shift_and_xor_if_MSB_K1_is_one)
{
    uint8_t expected[16] = {0};
    uint8_t K1[16] = {0};
    uint8_t K2[16] = {0};

    K1[0] = MSBIT_SET;
    expected[15] = CONST_RB;

    ret = CmacAesSubkeys_CalculateK2FromK1( K1, sizeof(K1), K2, sizeof(K2) );

    LONGS_EQUAL( ret, 0 );
    MEMCMP_EQUAL( expected, K2, sizeof(expected) );
}

TEST(CmacAesSubkeyOps, K2_xor_clears_bits)
{
    uint8_t expected[16] = {0};
    uint8_t K1[16] = {0};
    uint8_t K2[16] = {0};

    K1[0] = MSBIT_SET;

    // The xor in the K2 calculation must clear these bits.
    K1[15] = SHIFTED_CONST_RB;

    expected[15] = (SHIFTED_CONST_RB << 1) ^ CONST_RB;

    ret = CmacAesSubkeys_CalculateK2FromK1( K1, sizeof(K1), K2, sizeof(K2) );

    LONGS_EQUAL( ret, 0 );
    MEMCMP_EQUAL( expected, K2, sizeof(expected) );
}

TEST(CmacAesSubkeyOps, generate_L_from_input_key_all_zeros)
{
    uint8_t expected[16] = {
        0x66, 0xE9, 0x4B, 0xD4, 0xEF, 0x8A, 0x2C, 0x3B,
        0x88, 0x4C, 0xFA, 0x59, 0xCA, 0x34, 0x2B, 0x2E,
    };
    uint8_t actual[16] = {};
    uint8_t key[16] = {};
    uint8_t iv[16] = {};
    uint8_t input[16] = {};
    AES128_HANDLE aes_handle = NULL;
    AES128_CREATE_PARAMS create_params = {};
    AES128_CRYPTO_PARAMS crypto_params = {};

    create_params.key = key;
    create_params.key_len = sizeof(key);
    create_params.iv = iv;
    create_params.iv_len = sizeof(iv);
    aes_handle = MockAes128_Create(&create_params);

    crypto_params.aes_handle = aes_handle;
    crypto_params.input = input;
    crypto_params.input_len = sizeof(input);

    mock().expectOneCall("Aes128_Encrypt")
        .withParameterOfType("AES128_CRYPTO_PARAMS", "params", &crypto_params)
        .withOutputParameterReturning("output", expected, sizeof(expected))
        .withParameter("output_len", sizeof(expected))
        .andReturnValue(AES128_SUCCESS);

    ret = CmacAesSubkeys_CalculateLFromK(aes_handle, actual, sizeof(actual));

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
}

TEST(CmacAesSubkeyOps, generate_L_using_rfc4933_example)
{
    uint8_t expected[16] = {
        0x7d, 0xf7, 0x6b, 0x0c, 0x1a, 0xb8, 0x99, 0xb3,
        0x3e, 0x42, 0xf0, 0x47, 0xb9, 0x1b, 0x54, 0x6f,
    };
    uint8_t actual[16] = {};

    uint8_t key[16] = {
        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c,
    };
    uint8_t iv[16] = {};
    uint8_t input[16] = {};     // Per the RFC spec
    AES128_HANDLE aes_handle = NULL;
    AES128_CREATE_PARAMS create_params = {};
    AES128_CRYPTO_PARAMS crypto_params = {};

    create_params.key = key;
    create_params.key_len = sizeof(key);
    create_params.iv = iv;
    create_params.iv_len = sizeof(iv);
    aes_handle = MockAes128_Create(&create_params);

    crypto_params.aes_handle = aes_handle;
    crypto_params.input = input;
    crypto_params.input_len = sizeof(input);

    mock().expectOneCall("Aes128_Encrypt")
        .withParameterOfType("AES128_CRYPTO_PARAMS", "params", &crypto_params)
        .withOutputParameterReturning("output", expected, sizeof(expected))
        .withParameter("output_len", sizeof(expected))
        .andReturnValue(AES128_SUCCESS);

    ret = CmacAesSubkeys_CalculateLFromK(aes_handle, actual, sizeof(actual));

    LONGS_EQUAL( AES128_SUCCESS, ret );
    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
}
