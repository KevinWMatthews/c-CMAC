extern "C"
{
#include "AesCmac.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(AesCmac)
{
    void setup()
    {
    }

    void teardown()
    {
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

    int ret = 42;
    unsigned char cmac[16] = {};

    ret = AesCmac_Calculate128( key, sizeof(key), message, message_len, cmac, sizeof(cmac) );

    LONGS_EQUAL( ret, 0 );
    MEMCMP_EQUAL( expected, cmac, sizeof(expected) );
}
