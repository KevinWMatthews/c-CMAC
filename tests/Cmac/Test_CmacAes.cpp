extern "C"
{
#include "CmacAes.h"
}

#include "CppUTest/TestHarness.h"


TEST_GROUP(CmacAes)
{
    int ret;

    void setup()
    {
    }

    void teardown()
    {
    }
};

static uint8_t zeros[16] = {};

TEST(CmacAes, rfc_4493_example_1_message_length_0)
{
    uint8_t expected[] = {
        0xbb, 0x1d, 0x69, 0x29, 0xe9, 0x59, 0x37, 0x28,
        0x7f, 0xa3, 0x7d, 0x12, 0x9b, 0x75, 0x67, 0x46,
    };
    uint8_t key[] = {
        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c,
    };
    uint8_t *message = NULL;
    size_t message_len = 0;
    CMAC_AES_CALCULATE_PARAMS params = {};
    uint8_t cmac[16] = {};

    params.key = key;
    params.key_len = sizeof(key);
    params.message = message;
    params.message_len = message_len;
    ret = CmacAes_Calculate( &params, cmac, sizeof(cmac) );

    LONGS_EQUAL( ret, 0 );
    MEMCMP_EQUAL( expected, cmac, sizeof(expected) );
}

TEST(CmacAes, rfc_4493_example_2_message_length_16)
{
    uint8_t expected[] = {
        0x07, 0x0a, 0x16, 0xb4, 0x6b, 0x4d, 0x41, 0x44,
        0xf7, 0x9b, 0xdd, 0x9d, 0xd0, 0x4a, 0x28, 0x7c,
    };
    uint8_t key[] = {
        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c,
    };
    uint8_t message[] = {
        0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
        0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
    };
    size_t message_len = sizeof(message);
    CMAC_AES_CALCULATE_PARAMS params = {};
    uint8_t cmac[16] = {};

    params.key = key;
    params.key_len = sizeof(key);
    params.message = message;
    params.message_len = message_len;
    ret = CmacAes_Calculate( &params, cmac, sizeof(cmac) );

    LONGS_EQUAL( ret, 0 );
    MEMCMP_EQUAL( expected, cmac, sizeof(expected) );
}
