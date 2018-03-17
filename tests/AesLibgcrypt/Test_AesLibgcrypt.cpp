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
    AES128 aes_handle;
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
        Aes128_Create(&create_params, &aes_handle);
    }

    void teardown()
    {
        //TODO close handle
        Aes128_Destroy(&aes_handle);
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

TEST(AesLibgcrypt_Encrypt, encrypt_fails_with_null_input)
{
    encrypt_params.aes_handle = aes_handle;
    encrypt_params.input = NULL;

    ret = Aes128_Encrypt2( &encrypt_params, output, sizeof(output) );

    LONGS_EQUAL( AES128_NULL_POINTER, ret );
}

TEST(AesLibgcrypt_Encrypt, encrypt_fails_with_invalid_input_length)
{
    // Forcing input length to 16 bytes for now.
    uint8_t input[16-1] = {};

    encrypt_params.aes_handle = aes_handle;
    encrypt_params.input = input;
    encrypt_params.input_len = sizeof(input);

    ret = Aes128_Encrypt2( &encrypt_params, output, sizeof(output) );

    LONGS_EQUAL( AES128_INVALID_INPUT, ret );
}

TEST(AesLibgcrypt_Encrypt, encrypt_fails_with_null_output)
{
    uint8_t input[16] = {};

    encrypt_params.aes_handle = aes_handle;
    encrypt_params.input = input;

    ret = Aes128_Encrypt2( &encrypt_params, NULL, sizeof(output) );

    LONGS_EQUAL( AES128_NULL_POINTER, ret );
}

TEST(AesLibgcrypt_Encrypt, encrypt_fails_with_output_shorter_than_input)
{
    uint8_t input[16] = {};
    uint8_t short_output[16-1] = {0};

    encrypt_params.aes_handle = aes_handle;
    encrypt_params.input = input;
    encrypt_params.input_len = sizeof(input);

    ret = Aes128_Encrypt2( &encrypt_params, short_output, sizeof(short_output) );

    LONGS_EQUAL( AES128_INVALID_OUTPUT, ret );
}

TEST(AesLibgcrypt_Encrypt, encrypt_message_0_key_0_iv_0)
{
    uint8_t expected[16] = {
        0x66, 0xE9, 0x4B, 0xD4, 0xEF, 0x8A, 0x2C, 0x3B,
        0x88, 0x4C, 0xFA, 0x59, 0xCA, 0x34, 0x2B, 0x2E,
    };
    uint8_t input[16] = {0};

    encrypt_params.aes_handle = aes_handle;
    encrypt_params.input = input;
    encrypt_params.input_len = sizeof(input);

    // Encrypt
    ret = Aes128_Encrypt2( &encrypt_params, output, sizeof(output) );

    // Check against value calculated from a known-good source.
    LONGS_EQUAL( AES128_SUCCESS, ret );
    MEMCMP_EQUAL( expected, output, sizeof(expected) );
}
