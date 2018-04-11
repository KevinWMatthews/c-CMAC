extern "C"
{
#include "Aes128.h"
}

// Test the wrapper with the actual gcrypt library.

#include "CppUTest/TestHarness.h"

TEST_GROUP(Aes128Libgcrypt_Initialize)
{
    AES128_HANDLE aes_handle;
    int ret;

    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(Aes128Libgcrypt_Initialize, initialize)
{
    ret = Aes128_Initialize();
    LONGS_EQUAL( AES128_SUCCESS, ret );
}

//TODO fail if invalid library version is installed



TEST_GROUP(Aes128Libgcrypt_Create)
{
    AES128_HANDLE aes_handle;
    AES128_CREATE_PARAMS create_params;
    int ret;

    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(Aes128Libgcrypt_Create, create_and_destroy_aes_handle)
{
    uint8_t key[AES128_KEY_LEN] = {};
    uint8_t iv[AES128_IV_LEN] = {};
    create_params.key = key;
    create_params.key_len = sizeof(key);
    create_params.iv = iv;
    create_params.iv_len = sizeof(iv);

    ret = Aes128_Create(&create_params, &aes_handle);

    LONGS_EQUAL( AES128_SUCCESS, ret );
    CHECK_TRUE( aes_handle != NULL );

    Aes128_Destroy(&aes_handle);
    CHECK_TRUE( aes_handle == NULL );
}

TEST(Aes128Libgcrypt_Create, create_fails_with_null_params)
{
    ret = Aes128_Create(NULL, &aes_handle);
    LONGS_EQUAL( AES128_NULL_POINTER, ret );
    CHECK_TRUE( aes_handle == NULL );
}

TEST(Aes128Libgcrypt_Create, create_fails_with_null_key)
{
    create_params.key = NULL;

    ret = Aes128_Create(&create_params, &aes_handle);

    LONGS_EQUAL( AES128_NULL_POINTER, ret );
    CHECK_TRUE( aes_handle == NULL );
}

TEST(Aes128Libgcrypt_Create, create_fails_with_null_iv)
{
    uint8_t key[AES128_KEY_LEN] = {};
    create_params.key = key;
    create_params.iv = NULL;

    ret = Aes128_Create(&create_params, &aes_handle);

    LONGS_EQUAL( AES128_NULL_POINTER, ret );
    CHECK_TRUE( aes_handle == NULL );
}

TEST(Aes128Libgcrypt_Create, create_fails_with_null_aes)
{
    uint8_t key[AES128_KEY_LEN] = {};
    uint8_t iv[AES128_IV_LEN] = {};
    create_params.key = key;
    create_params.iv = iv;

    ret = Aes128_Create(&create_params, NULL);

    LONGS_EQUAL( AES128_NULL_POINTER, ret );
}

TEST(Aes128Libgcrypt_Create, create_fails_with_invalid_key_length)
{
    uint8_t key[AES128_KEY_LEN-1] = {};
    uint8_t iv[AES128_IV_LEN] = {};
    create_params.key = key;
    create_params.key_len = sizeof(key);
    create_params.iv = iv;

    ret = Aes128_Create(&create_params, &aes_handle);

    LONGS_EQUAL( AES128_INVALID_KEY_LENGTH, ret );
}

TEST(Aes128Libgcrypt_Create, create_fails_with_invalid_iv_length)
{
    uint8_t key[AES128_KEY_LEN] = {};
    uint8_t iv[AES128_IV_LEN-1] = {};
    create_params.key = key;
    create_params.key_len = sizeof(key);
    create_params.iv = iv;
    create_params.iv_len = sizeof(iv);

    ret = Aes128_Create(&create_params, &aes_handle);

    LONGS_EQUAL( AES128_INVALID_IV_LENGTH, ret );
}

TEST(Aes128Libgcrypt_Create, can_destroy_null_pointer)
{
    Aes128_Destroy(NULL);
}

TEST(Aes128Libgcrypt_Create, can_destroy_null_aes_handle)
{
    aes_handle = NULL;
    Aes128_Destroy(&aes_handle);
}



TEST_GROUP(Aes128Libgcrypt_Encrypt)
{
    AES128_HANDLE aes_handle;
    AES128_CREATE_PARAMS create_params;
    AES128_CRYPTO_PARAMS encrypt_params;
    uint8_t zeros[AES128_KEY_LEN];
    uint8_t output[AES128_BLOCK_LEN];
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

TEST(Aes128Libgcrypt_Encrypt, encrypt_fails_with_null_params)
{
    ret = Aes128_Encrypt( NULL, output, sizeof(output) );
    LONGS_EQUAL( AES128_NULL_POINTER, ret );
}

TEST(Aes128Libgcrypt_Encrypt, encrypt_fails_with_null_aes_handle)
{
    encrypt_params.aes_handle = NULL;

    ret = Aes128_Encrypt( &encrypt_params, output, sizeof(output) );

    LONGS_EQUAL( AES128_NULL_POINTER, ret );
}

TEST(Aes128Libgcrypt_Encrypt, encrypt_fails_with_null_input)
{
    encrypt_params.aes_handle = aes_handle;
    encrypt_params.input = NULL;

    ret = Aes128_Encrypt( &encrypt_params, output, sizeof(output) );

    LONGS_EQUAL( AES128_NULL_POINTER, ret );
}

TEST(Aes128Libgcrypt_Encrypt, encrypt_fails_with_invalid_input_length)
{
    // Forcing input length to 16 bytes for now.
    uint8_t input[AES128_BLOCK_LEN-1] = {};

    encrypt_params.aes_handle = aes_handle;
    encrypt_params.input = input;
    encrypt_params.input_len = sizeof(input);

    ret = Aes128_Encrypt( &encrypt_params, output, sizeof(output) );

    LONGS_EQUAL( AES128_INVALID_INPUT_LENGTH, ret );
}

TEST(Aes128Libgcrypt_Encrypt, encrypt_fails_with_null_output)
{
    uint8_t input[AES128_BLOCK_LEN] = {};

    encrypt_params.aes_handle = aes_handle;
    encrypt_params.input = input;

    ret = Aes128_Encrypt( &encrypt_params, NULL, sizeof(output) );

    LONGS_EQUAL( AES128_NULL_POINTER, ret );
}

TEST(Aes128Libgcrypt_Encrypt, encrypt_fails_with_output_shorter_than_input)
{
    uint8_t input[AES128_BLOCK_LEN] = {};
    uint8_t short_output[AES128_BLOCK_LEN-1] = {0};

    encrypt_params.aes_handle = aes_handle;
    encrypt_params.input = input;
    encrypt_params.input_len = sizeof(input);

    ret = Aes128_Encrypt( &encrypt_params, short_output, sizeof(short_output) );

    LONGS_EQUAL( AES128_INVALID_OUTPUT_LENGTH, ret );
}

TEST(Aes128Libgcrypt_Encrypt, encrypt_message_0_key_0_iv_0)
{
    uint8_t expected[AES128_BLOCK_LEN] = {
        0x66, 0xE9, 0x4B, 0xD4, 0xEF, 0x8A, 0x2C, 0x3B,
        0x88, 0x4C, 0xFA, 0x59, 0xCA, 0x34, 0x2B, 0x2E,
    };
    uint8_t input[AES128_BLOCK_LEN] = {0};

    encrypt_params.aes_handle = aes_handle;
    encrypt_params.input = input;
    encrypt_params.input_len = sizeof(input);

    // Encrypt
    ret = Aes128_Encrypt( &encrypt_params, output, sizeof(output) );

    // Check against value calculated from a known-good source.
    LONGS_EQUAL( AES128_SUCCESS, ret );
    MEMCMP_EQUAL( expected, output, sizeof(expected) );
}

TEST(Aes128Libgcrypt_Encrypt, encrypt_message_0_key_0_iv_0_twice)
{
    uint8_t expected[AES128_BLOCK_LEN] = {
        0x66, 0xE9, 0x4B, 0xD4, 0xEF, 0x8A, 0x2C, 0x3B,
        0x88, 0x4C, 0xFA, 0x59, 0xCA, 0x34, 0x2B, 0x2E,
    };
    uint8_t input[AES128_BLOCK_LEN] = {};
    uint8_t output2[AES128_BLOCK_LEN] = {};
    int ret2;

    encrypt_params.aes_handle = aes_handle;
    encrypt_params.input = input;
    encrypt_params.input_len = sizeof(input);

    // Encrypt
    ret = Aes128_Encrypt( &encrypt_params, output, sizeof(output) );
    ret2 = Aes128_Encrypt( &encrypt_params, output2, sizeof(output2) );

    // Check against value calculated from a known-good source.
    LONGS_EQUAL( AES128_SUCCESS, ret );
    MEMCMP_EQUAL( expected, output, sizeof(expected) );
    LONGS_EQUAL( AES128_SUCCESS, ret2 );
    MEMCMP_EQUAL( expected, output2, sizeof(expected) );
}



TEST_GROUP(Aes128Libgcrypt_EncryptKnown)
{
    AES128_HANDLE aes_handle;
    AES128_CREATE_PARAMS create_params;
    AES128_CRYPTO_PARAMS encrypt_params;
    uint8_t output[AES128_BLOCK_LEN];
    int ret;

    void setup()
    {
        Aes128_Initialize();
    }

    void teardown()
    {
        Aes128_Destroy(&aes_handle);
    }
};

TEST(Aes128Libgcrypt_EncryptKnown, example_from_rfc4493)
{
    uint8_t expected[AES128_BLOCK_LEN] = {
        0x7d, 0xf7, 0x6b, 0x0c, 0x1a, 0xb8, 0x99, 0xb3,
        0x3e, 0x42, 0xf0, 0x47, 0xb9, 0x1b, 0x54, 0x6f,
    };
    uint8_t key[AES128_KEY_LEN] = {
        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c,
    };
    uint8_t iv[AES128_IV_LEN] = {};
    uint8_t msg[AES128_BLOCK_LEN] = {};
    create_params.key = key;
    create_params.key_len = sizeof(key);
    create_params.iv = iv;
    create_params.iv_len = sizeof(iv);

    ret = Aes128_Create(&create_params, &aes_handle);
    encrypt_params.aes_handle = aes_handle;
    encrypt_params.input = msg;
    encrypt_params.input_len = sizeof(msg);

    ret = Aes128_Encrypt( &encrypt_params, output, sizeof(output) );

    LONGS_EQUAL( AES128_SUCCESS, ret );
    MEMCMP_EQUAL( expected, output, sizeof(expected) );
}
