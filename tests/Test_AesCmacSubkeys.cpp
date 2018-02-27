extern "C"
{
#include "AesCmacSubkeys.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(aes_cmac_subkeys)
{
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


TEST(aes_cmac_subkeys, generate_subkeys_for_rfc_examples)
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
