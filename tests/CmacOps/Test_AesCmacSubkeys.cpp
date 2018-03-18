extern "C"
{
#include "AesCmacSubkeys.h"
#include "Aes128.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Aes128Comparator.h"

class Comparator_Aes128_CreateParams : public MockNamedValueComparator
{
public:
    virtual bool isEqual(const void* object1, const void* object2)
    {
        const AES128_CREATE_PARAMS *params1 = (const AES128_CREATE_PARAMS *)object1;
        const AES128_CREATE_PARAMS *params2 = (const AES128_CREATE_PARAMS *)object2;

        SimpleString key1 = StringFromBinaryWithSize(params1->key, params1->key_len);
        SimpleString key2 = StringFromBinaryWithSize(params2->key, params2->key_len);

        SimpleString iv1 = StringFromBinaryWithSize(params1->iv, params1->iv_len);
        SimpleString iv2 = StringFromBinaryWithSize(params2->iv, params2->iv_len);

        if (key1 != key2)
            return 0;
        if (iv1 != iv2)
            return 0;

        return 1;
    }

    virtual SimpleString valueToString(const void* object)
    {
        if (object == NULL)
            return StringFrom("NULL");

        const AES128_CREATE_PARAMS *params = (const AES128_CREATE_PARAMS *)object;

        SimpleString key = StringFromBinaryWithSize(params->key, params->key_len);
        SimpleString iv = StringFromBinaryWithSize(params->iv, params->iv_len);

        return StringFrom("{") + StringFrom("key: ") + key + StringFrom(", iv: ") + iv + StringFrom("}");
    }
};

class Comparator_Aes128_CryptoParams : public MockNamedValueComparator
{
public:
    virtual bool isEqual(const void* object1, const void* object2)
    {
        const AES128_CRYPTO_PARAMS *params1 = (const AES128_CRYPTO_PARAMS *)object1;
        const AES128_CRYPTO_PARAMS *params2 = (const AES128_CRYPTO_PARAMS *)object2;

        SimpleString input1 = StringFromBinaryWithSize(params1->input, params1->input_len);
        SimpleString input2 = StringFromBinaryWithSize(params2->input, params2->input_len);

        if (params1->aes_handle != params2->aes_handle)
            return 0;

        if (input1 != input2)
            return 0;

        return 1;
    }

    virtual SimpleString valueToString(const void* object)
    {
        const AES128_CRYPTO_PARAMS *params = (const AES128_CRYPTO_PARAMS *)object;

        // SimpleString aes_handle = valueToString(params->aes_handle);
        // SimpleString aes_handle = Comparator_Aes128_CreateParams::valueToString(params->aes_handle);
        // SimpleString aes_handle = Comparator_Aes128_CreateParams.valueToString(params->aes_handle);
        //
        Comparator_Aes128_CreateParams comp;
        SimpleString aes_handle = comp.valueToString(params->aes_handle);
        // SimpleString aes_handle = StringFromBinaryWithSize(params->aes_handle->key, params->aes_key_len);
        // SimpleString aes_handle = StringFrom("?");
        SimpleString input = StringFromBinaryWithSize(params->input, params->input_len);
        return StringFrom("AES handle: ") + aes_handle + StringFrom("; input: ") + input;
    }
};

TEST_GROUP(AesCmacSubkeys)
{
    Aes128Comparator comparator;
    Comparator_Aes128_CreateParams create_comparator;
    Comparator_Aes128_CryptoParams crypto_comparator;
    int ret;

    void setup()
    {
        mock().strictOrder();
    }

    void teardown()
    {
        mock().checkExpectations();
        mock().clear();
        mock().removeAllComparatorsAndCopiers();
    }
};

#define MSBIT_SET           (0x80)
#define CONST_RB            (0x87)
#define SHIFTED_CONST_RB    (CONST_RB >> 1)

static uint8_t zeros[16] = {};

TEST(AesCmacSubkeys, K1_operate_on_all_zeros_changes_no_bits)
{
    uint8_t expected[16] = {0};
    uint8_t L[16] = {0};
    uint8_t K1[16] = {0};

    ret = AesCmac_CalculateK1FromL( L, sizeof(L), K1, sizeof(K1) );

    LONGS_EQUAL( ret, 0 );
    MEMCMP_EQUAL( expected, K1, sizeof(expected) );
}

TEST(AesCmacSubkeys, left_shift_if_MSbit_L_is_zero)
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

    ret = AesCmac_CalculateK1FromL( L, sizeof(L), K1, sizeof(K1) );

    LONGS_EQUAL( ret, 0 );
    MEMCMP_EQUAL( expected, K1, sizeof(expected) );
}

TEST(AesCmacSubkeys, left_shift_and_xor_if_MSbit_L_is_one)
{
    uint8_t expected[16] = {0};
    uint8_t L[16] = {0};
    uint8_t K1[16] = {0};

    L[0] = MSBIT_SET;
    expected[15] = CONST_RB;

    ret = AesCmac_CalculateK1FromL( L, sizeof(L), K1, sizeof(K1) );

    LONGS_EQUAL( ret, 0 );
    MEMCMP_EQUAL( expected, K1, sizeof(expected) );
}

TEST(AesCmacSubkeys, verify_K1_uses_xor_const_rb)
{
    uint8_t expected[16] = {0};
    uint8_t L[16] = {0};
    uint8_t K1[16] = {0};

    L[0] = MSBIT_SET;

    // The xor in the K1 calculation must clear these bits.
    L[15] = SHIFTED_CONST_RB;

    // K1 calculation must use this algorithm.
    expected[15] = (SHIFTED_CONST_RB << 1) ^ CONST_RB;

    ret = AesCmac_CalculateK1FromL( L, sizeof(L), K1, sizeof(K1) );

    LONGS_EQUAL( ret, 0 );
    MEMCMP_EQUAL( expected, K1, sizeof(expected) );
}

TEST(AesCmacSubkeys, K2_operate_on_all_zeros_changes_no_bits)
{
    uint8_t expected[16] = {0};
    uint8_t K1[16] = {0};
    uint8_t K2[16] = {0};

    ret = AesCmac_CalculateK2FromK1( K1, sizeof(K1), K2, sizeof(K2) );

    LONGS_EQUAL( ret, 0 );
    MEMCMP_EQUAL( expected, K2, sizeof(expected) );
}

TEST(AesCmacSubkeys, K2_left_shift_only_if_MSB_K1_is_zero)
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

    ret = AesCmac_CalculateK2FromK1( K1, sizeof(K1), K2, sizeof(K2) );

    LONGS_EQUAL( ret, 0 );
    MEMCMP_EQUAL( expected, K2, sizeof(expected) );
}

TEST(AesCmacSubkeys, K2_left_shift_and_xor_if_MSB_K1_is_one)
{
    uint8_t expected[16] = {0};
    uint8_t K1[16] = {0};
    uint8_t K2[16] = {0};

    K1[0] = MSBIT_SET;
    expected[15] = CONST_RB;

    ret = AesCmac_CalculateK2FromK1( K1, sizeof(K1), K2, sizeof(K2) );

    LONGS_EQUAL( ret, 0 );
    MEMCMP_EQUAL( expected, K2, sizeof(expected) );
}

TEST(AesCmacSubkeys, K2_xor_clears_bits)
{
    uint8_t expected[16] = {0};
    uint8_t K1[16] = {0};
    uint8_t K2[16] = {0};

    K1[0] = MSBIT_SET;

    // The xor in the K2 calculation must clear these bits.
    K1[15] = SHIFTED_CONST_RB;

    expected[15] = (SHIFTED_CONST_RB << 1) ^ CONST_RB;

    ret = AesCmac_CalculateK2FromK1( K1, sizeof(K1), K2, sizeof(K2) );

    LONGS_EQUAL( ret, 0 );
    MEMCMP_EQUAL( expected, K2, sizeof(expected) );
}

IGNORE_TEST(AesCmacSubkeys, generate_L_from_input_key_all_zeros)
{
    uint8_t expected[16] = {
        0x66, 0xE9, 0x4B, 0xD4, 0xEF, 0x8A, 0x2C, 0x3B, 0x88, 0x4C, 0xFA, 0x59, 0xCA, 0x34, 0x2B, 0x2E,
    };
    uint8_t zeros[16] = {};

    uint8_t key[16] = {};
    uint8_t iv[16] = {};
    AES_KEY_128 aes_params = {};
    aes_params.key = key;
    aes_params.key_len = sizeof(key);
    aes_params.iv = iv;
    aes_params.iv_len = sizeof(key);

    uint8_t L[16] = {};

    AES128_HANDLE aes_handle = NULL;
    AES128_CREATE_PARAMS create_params = {};
    AES128_CRYPTO_PARAMS crypto_params = {};

    create_params.key = key;
    create_params.key_len = sizeof(key);
    create_params.iv = iv;
    create_params.iv_len = sizeof(key);

    crypto_params.aes_handle = aes_handle;
    crypto_params.input = key;
    crypto_params.input_len = sizeof(key);


    mock().expectOneCall("Aes128_Initialize")
        .andReturnValue(AES128_SUCCESS);
    mock().expectOneCall("Aes128_Create")
        .withParameter("params", &create_params)
        .withOutputParameterReturning("aes_handle", &aes_handle, sizeof(&aes_handle))
        .andReturnValue(AES128_SUCCESS);

    Aes128_Initialize();
    Aes128_Create(&create_params, &aes_handle);

    mock().installComparator("AES128_CREATE_PARAMS", create_comparator);    //?
    mock().installComparator("AES128_CRYPTO_PARAMS", crypto_comparator);
    mock().expectOneCall("Aes128_Encrypt")
        .withParameterOfType("AES128_CRYPTO_PARAMS", "params", &crypto_params)
        .withOutputParameterReturning("output", expected, sizeof(expected))
        .withParameter("output_len", sizeof(expected))
        .andReturnValue(AES128_SUCCESS);

    ret = AesCmac_CalculateLFromK_( aes_handle, L, sizeof(L) );

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, L, sizeof(expected) );
}

TEST(AesCmacSubkeys, generate_L_using_rfc4933_example)
{
    uint8_t expected[16] = {
        0x7d, 0xf7, 0x6b, 0x0c, 0x1a, 0xb8, 0x99, 0xb3,
        0x3e, 0x42, 0xf0, 0x47, 0xb9, 0x1b, 0x54, 0x6f,
    };

    uint8_t key[16] = {
        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c,
    };
    uint8_t iv[16] = {};
    AES_KEY_128 aes_params = {};
    aes_params.key = key;
    aes_params.key_len = sizeof(key);
    aes_params.iv = iv;
    aes_params.iv_len = sizeof(key);

    uint8_t L[16] = {};

    mock().installComparator("AES_KEY_128", comparator);
    mock().expectOneCall("Aes_Calculate128")
        .withParameterOfType("AES_KEY_128", "aes_128", (void *)&aes_params)
        .withMemoryBufferParameter("input", zeros, sizeof(zeros))
        .withParameter("input_len", sizeof(zeros))
        .withOutputParameterReturning("output", expected, sizeof(expected))
        .withParameter("output_len", sizeof(expected))
        .andReturnValue(0);

    ret = AesCmac_CalculateLFromK( key, sizeof(key), L, sizeof(L) );

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, L, sizeof(expected) );
}

TEST(AesCmacSubkeys, generate_subkeys_for_rfc_examples)
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
    unsigned char key[16] = {
        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c,
    };

    // Values for mocks
    AES_KEY_128 aes_params = {};
    aes_params.key = key;
    aes_params.key_len = sizeof(key);
    aes_params.iv = zeros;
    aes_params.iv_len = sizeof(zeros);
    uint8_t L[16] = {
        0x7d, 0xf7, 0x6b, 0x0c, 0x1a, 0xb8, 0x99, 0xb3,
        0x3e, 0x42, 0xf0, 0x47, 0xb9, 0x1b, 0x54, 0x6f,
    };

    mock().installComparator("AES_KEY_128", comparator);
    mock().expectOneCall("Aes_Calculate128")
        .withParameterOfType("AES_KEY_128", "aes_128", &aes_params)
        .withMemoryBufferParameter("input", zeros, sizeof(zeros))
        .withParameter("input_len", sizeof(zeros))
        .withOutputParameterReturning("output", L, sizeof(L))
        .withParameter("output_len", sizeof(L))
        .andReturnValue(0);

    ret = AesCmac_GenerateSubkeys(key, sizeof(key),
            actual_K1, sizeof(actual_K1),
            actual_K2, sizeof(actual_K2));

    LONGS_EQUAL( ret, 0 );
    MEMCMP_EQUAL( expected_K1, actual_K1, sizeof(expected_K1) );
    MEMCMP_EQUAL( expected_K2, actual_K2, sizeof(expected_K2) );
}
