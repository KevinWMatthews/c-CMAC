extern "C"
{
#include "AesCmacSubkeys.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(aes_cmac_subkeys)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};


TEST(aes_cmac_subkeys, generate_subkeys_for_rfc_examples)
{
    unsigned char expected_K1[] = {
        0xfb, 0xee, 0xd6, 0x18, 0x35, 0x71, 0x33, 0x66,
        0x7c, 0x85, 0xe0, 0x8f, 0x72, 0x36, 0xa8, 0xde,
    };
    unsigned char expected_K2[] = {
        0xf7, 0xdd, 0xac, 0x30, 0x6a, 0xe2, 0x66, 0xcc,
        0xf9, 0x0b, 0xc1, 0x1e, 0xe4, 0x6d, 0x51, 0x3b,
    };
    unsigned char key[] = {
        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c,
    };
    unsigned char actual_k1[16] = {};
    unsigned char actual_k2[16] = {};
    int ret;

    ret = AesCmac_GenerateSubkeys(key, actual_k1, actual_k2);

    LONGS_EQUAL( ret, 0 );
    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
    MEMCMP_EQUAL( expected_K1, actual_K1, sizeof(expected_K1) );
    MEMCMP_EQUAL( expected_K2, actual_K2, sizeof(expected_K2) );
}
