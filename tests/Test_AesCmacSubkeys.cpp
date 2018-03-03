extern "C"
{
#include "AesCmacSubkeys.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(AesCmacSubkeys)
{
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

#define MSBIT_SET           (0x80)
#define CONST_RB            (0x87)
#define SHIFTED_CONST_RB    (CONST_RB >> 1)

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

uint8_t const_Zero[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

class Aes128Comparator : public MockNamedValueComparator
{
public:
    virtual bool isEqual(const void* object1, const void* object2)
    {
        const AES_KEY_128 *aes1 = (const AES_KEY_128 *)object1;
        const AES_KEY_128 *aes2 = (const AES_KEY_128 *)object2;

        SimpleString key1 = StringFromBinaryWithSize(aes1->key, aes1->key_len);
        SimpleString key2 = StringFromBinaryWithSize(aes2->key, aes2->key_len);

        SimpleString iv1 = StringFromBinaryWithSize(aes1->iv, aes1->iv_len);
        SimpleString iv2 = StringFromBinaryWithSize(aes2->iv, aes2->iv_len);

        if (key1 != key2)
        {
            return 0;
        }

        if (iv1 != iv2)
        {
            return 0;
        }

        return 1;
    }
    virtual SimpleString valueToString(const void* object)
    {
        const AES_KEY_128 *aes = (const AES_KEY_128 *)object;

        SimpleString key = StringFromBinaryWithSize(aes->key, aes->key_len);
        SimpleString iv = StringFromBinaryWithSize(aes->iv, aes->iv_len);

        return StringFrom("key: ") + key + StringFrom("; iv:") + iv;
    }
};

TEST(AesCmacSubkeys, generate_L_from_input_key_all_zeros)
{
    uint8_t key[16] = {0x01, 0x02};
    uint8_t key2[16] = {0x01, 0x02};
    // uint8_t key2[16] = {0x41, 0x42};
    uint8_t iv[16] = {0x0f, 0x0e};
    uint8_t iv2[16] = {0x0f, 0x0e};
    // uint8_t iv2[16] = {0xff, 0xfe};
    Aes128Comparator comparator;

    AES_KEY_128 aes_params = {};
    AES_KEY_128 aes_params2 = {};
    aes_params.key = key;
    aes_params.iv = iv;
    aes_params.key_len = 16;
    aes_params.iv_len = 16;

    aes_params2.key = key2;
    aes_params2.iv = iv2;
    aes_params2.key_len = 16;
    aes_params2.iv_len = 16;

    mock().installComparator("AES_KEY_128", comparator);
    mock().expectOneCall("AesWrapper_Encrypt")
        .withParameterOfType("AES_KEY_128", "aes_128", (void *)&aes_params);

    mock().actualCall("AesWrapper_Encrypt")
        .withParameterOfType("AES_KEY_128", "aes_128", (void *)&aes_params2);

    mock().checkExpectations();
    mock().clear();
    mock().removeAllComparatorsAndCopiers();
}

#if 0
{
    uint8_t K[16] = {0};
    uint8_t expected[16] = {
        0x66, 0xE9, 0x4B, 0xD4, 0xEF, 0x8A, 0x2C, 0x3B, 0x88, 0x4C, 0xFA, 0x59, 0xCA, 0x34, 0x2B, 0x2E,
    };
    uint8_t aes_128[16] = {
        0x66, 0xE9, 0x4B, 0xD4, 0xEF, 0x8A, 0x2C, 0x3B, 0x88, 0x4C, 0xFA, 0x59, 0xCA, 0x34, 0x2B, 0x2E,
    };
    uint8_t iv[16] = {0};
    AES_KEY_128 aes_arg = {};

    aes_arg.key = aes_128,
    aes_arg.key_len = sizeof(aes_128),
    aes_arg.iv = iv,
    aes_arg.iv_len = sizeof(iv),

    mock().expectOneCall("Aes_Calculate128")
        .withMemoryBufferParameter("aes_key", (const unsigned char *)&aes_arg, sizeof(aes_arg))     // Terrible hack
        .withMemoryBufferParameter("input", const_Zero, sizeof(const_Zero))
        .withParameter("input_len", sizeof(const_Zero))
        .withOutputParameterReturning("output", aes_128, sizeof(aes_128))
        .withParameter("output_len", sizeof(aes_128))
        .andReturnValue(0);
    ret = AesCmac_CalcualteLFromKey( K, sizeof(K), aes_128, sizeof(aes_128) );

    LONGS_EQUAL( ret, 0 );
    MEMCMP_EQUAL( expected, aes_128, sizeof(expected) );
}
#endif

/*
IGNORE_TEST(AesCmacSubkeys, generate_subkeys_for_rfc_examples)
{
    uint8_t expected_K1[] = {
        0xfb, 0xee, 0xd6, 0x18, 0x35, 0x71, 0x33, 0x66,
        0x7c, 0x85, 0xe0, 0x8f, 0x72, 0x36, 0xa8, 0xde,
    };
    uint8_t expected_K2[] = {
        0xf7, 0xdd, 0xac, 0x30, 0x6a, 0xe2, 0x66, 0xcc,
        0xf9, 0x0b, 0xc1, 0x1e, 0xe4, 0x6d, 0x51, 0x3b,
    };
    AES_KEY_128 aes_key = {
        .key = {
            0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
            0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c,
        },
        .iv = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
    };
    uint8_t const_Zero[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    uint8_t actual_K1[16] = {};
    uint8_t actual_K2[16] = {};
    int ret;

    uint8_t aes_128[] = {
        0x7d, 0xf7, 0x6b, 0x0c, 0x1a, 0xb8, 0x99, 0xb3,
        0x3e, 0x42, 0xf0, 0x47, 0xb9, 0x1b, 0x54, 0x6f,
    };

    mock().expectOneCall("Aes_Calculate128_2")
        .withParameter("aes_key", &aes_key)
        .withMemoryBufferParameter("input", const_Zero, sizeof(const_Zero))
        .withParameter("input_len", sizeof(const_Zero))
        .withOutputParameterReturning("output", aes_128, sizeof(aes_128))
        .withParameter("output_len", sizeof(aes_128))
        .andReturnValue(0);

    ret = AesCmac_GenerateSubkeys(&aes_key, actual_K1, actual_K2);

    LONGS_EQUAL( ret, 0 );
    MEMCMP_EQUAL( expected_K1, actual_K1, sizeof(expected_K1) );
    MEMCMP_EQUAL( expected_K2, actual_K2, sizeof(expected_K2) );
}
*/
