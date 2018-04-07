extern "C"
{
#include "MockAes128.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Aes128Copier.h"
#include <string.h>

TEST_GROUP(Aes128Copier)
{
    uint8_t key[16];
    uint8_t iv[16];
    AES128_STRUCT aes128_in;
    AES128_STRUCT aes128_out;

    Aes128Copier local_copier;

    void setup()
    {
        memset(key, 0xaa, sizeof(key));
        memset(iv, 0x55, sizeof(iv));
        aes128_in.key = key;
        aes128_in.key_len = sizeof(key);
        aes128_in.iv = iv;
        aes128_in.iv_len = sizeof(iv);
    }

    void teardown()
    {
    }
};

TEST(Aes128Copier, can_copy_mock_aes128_struct)
{
    local_copier.copy(&aes128_out, &aes128_in);

    MEMCMP_EQUAL(key, aes128_out.key, sizeof(key));
    LONGS_EQUAL(sizeof(key), aes128_out.key_len);
    MEMCMP_EQUAL(iv, aes128_out.iv, sizeof(iv));
    LONGS_EQUAL(sizeof(iv), aes128_out.iv_len);
}

TEST(Aes128Copier, null_output_object_does_not_segfault)
{
    local_copier.copy(NULL, &aes128_in);
}

TEST(Aes128Copier, null_input_object_does_not_segfault)
{
    local_copier.copy(&aes128_out, NULL);
}

TEST(Aes128Copier, null_input_key_does_not_segfault)
{
    aes128_in.key = NULL;
    local_copier.copy(&aes128_out, &aes128_in);

    POINTERS_EQUAL( NULL, aes128_out.key );
}

TEST(Aes128Copier, null_input_iv_does_not_segfault)
{
    aes128_in.iv = NULL;
    local_copier.copy(&aes128_out, &aes128_in);

    POINTERS_EQUAL( NULL, aes128_out.iv );
}
