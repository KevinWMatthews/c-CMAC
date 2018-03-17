extern "C"
{
#include "Aes128.h"
#include <gcrypt.h>
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(AesLibgcrypt)
{
    AES128 aes;
    int ret;

    void setup()
    {
        aes = NULL;
    }

    void teardown()
    {
    }
};

TEST(AesLibgcrypt, initialize)
{
    ret = Aes128_Initialize();
    LONGS_EQUAL( AES128_SUCCESS, ret );
}

TEST(AesLibgcrypt, destroy_aes_handle)
{
    Aes128_Destroy(&aes);
    CHECK_TRUE( aes == NULL );
}

TEST(AesLibgcrypt, create_aes_handle)
{
    AES128_KEY key = {};
    uint8_t key_buffer[16] = {};
    AES128_IV iv = {};
    uint8_t iv_buffer[16] = {};

    key.buffer = key_buffer;
    key.length = sizeof(key_buffer);
    iv.buffer = iv_buffer;
    iv.length = sizeof(iv_buffer);

    ret = Aes128_Create(&key, &iv, &aes);
    LONGS_EQUAL( AES128_SUCCESS, ret );
    CHECK_TRUE( aes != NULL );
}

TEST(AesLibgcrypt, create_fails_with_null_key)
{
    AES128_IV iv = {};
    uint8_t iv_buffer[16] = {};

    iv.buffer = iv_buffer;
    iv.length = sizeof(iv_buffer);

    ret = Aes128_Create(NULL, &iv, &aes);
    LONGS_EQUAL( AES128_NULL_POINTER, ret );
    CHECK_TRUE( aes == NULL );
}

TEST(AesLibgcrypt, create_fails_with_null_iv)
{
    AES128_KEY key = {};
    uint8_t key_buffer[16] = {};

    key.buffer = key_buffer;
    key.length = sizeof(key_buffer);

    ret = Aes128_Create(&key, NULL, &aes);
    LONGS_EQUAL( AES128_NULL_POINTER, ret );
    CHECK_TRUE( aes == NULL );
}

TEST(AesLibgcrypt, create_fails_with_null_aes)
{
    AES128_KEY key = {};
    uint8_t key_buffer[16] = {};
    AES128_IV iv = {};
    uint8_t iv_buffer[16] = {};

    key.buffer = key_buffer;
    key.length = sizeof(key_buffer);
    iv.buffer = iv_buffer;
    iv.length = sizeof(iv_buffer);

    ret = Aes128_Create(&key, &iv, NULL);
    LONGS_EQUAL( AES128_NULL_POINTER, ret );
    CHECK_TRUE( aes == NULL );
}

//TODO close cipher handle

TEST(AesLibgcrypt, encrypt_message_0_key_0_iv_0)
{
    uint8_t expected[16] = {
        0x66, 0xE9, 0x4B, 0xD4, 0xEF, 0x8A, 0x2C, 0x3B,
        0x88, 0x4C, 0xFA, 0x59, 0xCA, 0x34, 0x2B, 0x2E,
    };
    uint8_t msg[16] = {0};
    size_t msg_len = sizeof(msg);
    uint8_t actual[16] = {0};
    size_t actual_len = sizeof(actual);

    AES128_KEY key = {};
    uint8_t key_buffer[16] = {};
    AES128_IV iv = {};
    uint8_t iv_buffer[16] = {};

    // Init
    key.buffer = key_buffer;
    key.length = sizeof(key_buffer);
    iv.buffer = iv_buffer;
    iv.length = sizeof(iv_buffer);

    Aes128_Initialize();

    // Create
    Aes128_Create(&key, &iv, &aes);

    // Encrypt
    ret = Aes128_Encrypt(aes, msg, msg_len, actual, actual_len);

    // Check against value calculated from a known-good source.
    LONGS_EQUAL( AES128_SUCCESS, ret );
    MEMCMP_EQUAL( expected, actual, sizeof(expected) );

    // Destroy
    Aes128_Destroy(&aes);
}
