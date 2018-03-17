extern "C"
{
#include "Aes128.h"
#include <gcrypt.h>
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(AesLibgcrypt)
{
    AES128 aes;
    AES128_CREATE_PARAMS create_params;
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

TEST(AesLibgcrypt, create_fails_with_null_params)
{
    ret = Aes128_Create(NULL, &aes);
    LONGS_EQUAL( AES128_NULL_POINTER, ret );
    CHECK_TRUE( aes == NULL );
}

TEST(AesLibgcrypt, create_fails_with_null_key)
{
    create_params.key = NULL;

    ret = Aes128_Create(&create_params, &aes);

    LONGS_EQUAL( AES128_NULL_POINTER, ret );
    CHECK_TRUE( aes == NULL );
}

TEST(AesLibgcrypt, create_fails_with_null_iv)
{
    uint8_t key[16] = {};
    create_params.key = key;
    create_params.iv = NULL;

    ret = Aes128_Create(&create_params, &aes);

    LONGS_EQUAL( AES128_NULL_POINTER, ret );
    CHECK_TRUE( aes == NULL );
}

TEST(AesLibgcrypt, create_fails_with_null_aes)
{
    uint8_t key[16] = {};
    uint8_t iv[16] = {};
    create_params.key = key;
    create_params.iv = iv;

    ret = Aes128_Create(&create_params, NULL);

    LONGS_EQUAL( AES128_NULL_POINTER, ret );
}

TEST(AesLibgcrypt, create_fails_with_invalid_key_length)
{
    uint8_t key[16-1] = {};
    uint8_t iv[16] = {};
    create_params.key = key;
    create_params.key_len = sizeof(key);
    create_params.iv = iv;

    ret = Aes128_Create(&create_params, &aes);

    LONGS_EQUAL( AES128_INVALID_KEY, ret );
}

TEST(AesLibgcrypt, create_fails_with_invalid_iv_length)
{
    uint8_t key[16] = {};
    uint8_t iv[16-1] = {};
    create_params.key = key;
    create_params.key_len = sizeof(key);
    create_params.iv = iv;
    create_params.iv_len = sizeof(iv);

    ret = Aes128_Create(&create_params, &aes);

    LONGS_EQUAL( AES128_INVALID_IV, ret );
}

TEST(AesLibgcrypt, create_aes_handle)
{
    uint8_t key[16] = {};
    uint8_t iv[16] = {};
    create_params.key = key;
    create_params.key_len = sizeof(key);
    create_params.iv = iv;
    create_params.iv_len = sizeof(iv);


    ret = Aes128_Create(&create_params, &aes);

    LONGS_EQUAL( AES128_SUCCESS, ret );
    CHECK_TRUE( aes != NULL );
}

//TODO close cipher handle


TEST_GROUP(AesLibgcrypt_Encrypt)
{
    AES128 aes;
    AES128_CREATE_PARAMS create_params;
    AES128_CRYPTO_PARAMS encrypt_params;
    uint8_t zeros[16];
    uint8_t output[16];
    int ret;

    void setup()
    {
        // Clear zeros array?
        create_params.key = zeros;
        create_params.key_len = sizeof(zeros);
        create_params.iv = zeros;
        create_params.iv_len = sizeof(zeros);

        Aes128_Initialize();
        Aes128_Create(&create_params, &aes);
    }

    void teardown()
    {
    }
};

TEST(AesLibgcrypt_Encrypt, encrypt_fails_with_null_params)
{
    ret = Aes128_Encrypt2( NULL, output, sizeof(output) );
    LONGS_EQUAL( AES128_NULL_POINTER, ret );
}

TEST(AesLibgcrypt_Encrypt, encrypt_fails_with_null_aes_handle)
{
    encrypt_params.aes_handle = NULL;
    ret = Aes128_Encrypt2( &encrypt_params, output, sizeof(output) );
    LONGS_EQUAL( AES128_NULL_POINTER, ret );
}







TEST(AesLibgcrypt, encrypt_message_0_key_0_iv_0)
{
    uint8_t expected[16] = {
        0x66, 0xE9, 0x4B, 0xD4, 0xEF, 0x8A, 0x2C, 0x3B,
        0x88, 0x4C, 0xFA, 0x59, 0xCA, 0x34, 0x2B, 0x2E,
    };
    uint8_t msg[16] = {0};
    uint8_t actual[16] = {0};
    AES128_CRYPTO_PARAMS crypto_params = {};
    crypto_params.input = msg;


    size_t msg_len = sizeof(msg);
    size_t actual_len = sizeof(actual);

    uint8_t key[16] = {};
    uint8_t iv[16] = {};
    create_params.key = key;
    create_params.key_len = sizeof(key);
    create_params.iv = iv;
    create_params.iv_len = sizeof(iv);

    // Init
    Aes128_Initialize();

    // Create
    Aes128_Create(&create_params, &aes);

    // Encrypt
    ret = Aes128_Encrypt(aes, msg, msg_len, actual, actual_len);

    // Check against value calculated from a known-good source.
    LONGS_EQUAL( AES128_SUCCESS, ret );
    MEMCMP_EQUAL( expected, actual, sizeof(expected) );

    // Destroy
    Aes128_Destroy(&aes);
}
