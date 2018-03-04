extern "C"
{
#include "AesCmac.h"
#include "Aes.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

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

static uint8_t zeros[16] = {};

TEST_GROUP(AesCmac)
{
    Aes128Comparator comparator;
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

TEST(AesCmac, rfc_4493_example_1_message_length_0)
{
    unsigned char expected[] = {
        0xbb, 0x1d, 0x69, 0x29, 0xe9, 0x59, 0x37, 0x28,
        0x7f, 0xa3, 0x7d, 0x12, 0x9b, 0x75, 0x67, 0x46,
    };
    unsigned char key[] = {
        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c,
    };
    unsigned char *message = NULL;
    size_t message_len = 0;

    unsigned char cmac[16] = {};

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


    ret = AesCmac_Calculate128( key, sizeof(key), message, message_len, cmac, sizeof(cmac) );

    LONGS_EQUAL( ret, 0 );
    MEMCMP_EQUAL( expected, cmac, sizeof(expected) );
}
