extern "C"
{
#include <gcrypt.h>
}

#include "CppUTest/TestHarness.h"
#include "Libgcrypt_TestHelper.h"

#define LIBGCRYPT_REQURIED_VERSION      "1.8.2"

TEST_GROUP(Libgcrypt_AesEncrypt)
{
    gcry_error_t gcrypt_ret;
    gcry_cipher_hd_t gcrypt_handle;

    void setup()
    {
        gcry_check_version(LIBGCRYPT_REQURIED_VERSION);
        gcry_control(GCRYCTL_DISABLE_SECMEM, 0);
        gcry_control(GCRYCTL_INITIALIZATION_FINISHED, 0);
        gcry_cipher_open(&gcrypt_handle, GCRY_CIPHER_AES128, GCRY_CIPHER_MODE_CBC, 0);
    }

    void teardown()
    {
        gcry_cipher_close(gcrypt_handle);
    }
};

TEST(Libgcrypt_AesEncrypt, encrypt)
{
    char expected[16] = {
        0x66, 0xE9, 0x4B, 0xD4, 0xEF, 0x8A, 0x2C, 0x3B,
        0x88, 0x4C, 0xFA, 0x59, 0xCA, 0x34, 0x2B, 0x2E,
    };
    char actual[16] = {};
    char key[16] = {};
    char iv[16] = {};
    char input[16] = {};

    gcry_cipher_setkey( gcrypt_handle, key, sizeof(key) );
    gcry_cipher_setiv( gcrypt_handle, iv, sizeof(iv) );

    /*
     * gcry_error_t gcry_cipher_encrypt (gcry_cipher_hd_t h, unsigned char *out, size_t outsize, const unsigned char *in, size_t inlen)
     *
     * Encrypt in.
     * Fill out with the result.
     *
     * Returns 0 on success or a non-zero error code on error.
     */
    gcrypt_ret = gcry_cipher_encrypt(gcrypt_handle, actual, sizeof(actual), input, sizeof(input));

    CHECK_LIBGCRYPT_RETURN_CODE( GPG_ERR_NO_ERROR, gcrypt_ret );
    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
}

TEST(Libgcrypt_AesEncrypt, encrypt_data_twice)
{
    char expected[16] = {
        0x66, 0xE9, 0x4B, 0xD4, 0xEF, 0x8A, 0x2C, 0x3B,
        0x88, 0x4C, 0xFA, 0x59, 0xCA, 0x34, 0x2B, 0x2E,
    };
    char actual[16] = {};
    char actual2[16] = {};

    char key[16] = {};
    char iv[16] = {};
    char input[16] = {};
    gcry_error_t gcrypt_ret2;

    gcry_cipher_setkey( gcrypt_handle, key, sizeof(key) );
    gcry_cipher_setiv( gcrypt_handle, iv, sizeof(iv) );

    gcrypt_ret = gcry_cipher_encrypt(gcrypt_handle, actual, sizeof(actual), input, sizeof(input));

    // Must set IV again before second encryption
    gcry_cipher_setiv( gcrypt_handle, iv, sizeof(iv) );
    gcrypt_ret2 = gcry_cipher_encrypt(gcrypt_handle, actual2, sizeof(actual2), input, sizeof(input));

    CHECK_LIBGCRYPT_RETURN_CODE( GPG_ERR_NO_ERROR, gcrypt_ret );
    CHECK_LIBGCRYPT_RETURN_CODE( GPG_ERR_NO_ERROR, gcrypt_ret2 );
    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
    MEMCMP_EQUAL( expected, actual2, sizeof(expected) );
}

TEST(Libgcrypt_AesEncrypt, encrypt_non_zero_data)
{
    char expected[16] = {
        0xBB, 0x83, 0x8C, 0x98, 0x03, 0xBD, 0x17, 0x40,
        0xF8, 0x69, 0x49, 0x8D, 0x47, 0xD5, 0x26, 0x59,
    };
    char actual[16] = {};
    char key[16] = {
        0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
        0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
    };
    char iv[16] = {
        0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88,
        0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00,
    };
    char input[16] = {
        0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
        0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10,
    };

    gcry_cipher_setkey( gcrypt_handle, key, sizeof(key) );
    gcry_cipher_setiv( gcrypt_handle, iv, sizeof(iv) );

    /*
     * gcry_error_t gcry_cipher_encrypt (gcry_cipher_hd_t h, unsigned char *out, size_t outsize, const unsigned char *in, size_t inlen)
     *
     * Encrypt in.
     * Fill out with the result.
     *
     * Returns 0 on success or a non-zero error code on error.
     */
    gcrypt_ret = gcry_cipher_encrypt(gcrypt_handle, actual, sizeof(actual), input, sizeof(input));

    CHECK_LIBGCRYPT_RETURN_CODE( GPG_ERR_NO_ERROR, gcrypt_ret );
    MEMCMP_EQUAL( expected, actual, sizeof(expected) );
}


/*
 * Set Key
 */
TEST(Libgcrypt_AesEncrypt, set_key)
{
    char key[16] = {};

    /*
     * gcry_error_t gcry_cipher_setkey (gcry_cipher_hd_t h, const void *k, size_t l)
     *
     * Set the key k used for encryption or decryption in the context denoted by the handle h.
     * Can the key go out of scope?
     *
     * Returns 0 on success and a non-zero error code on error.
     */
    gcrypt_ret = gcry_cipher_setkey( gcrypt_handle, key, sizeof(key) );
    CHECK_LIBGCRYPT_RETURN_CODE( GPG_ERR_NO_ERROR, gcrypt_ret );
}

TEST(Libgcrypt_AesEncrypt, set_key_too_short_fails)
{
    char key[15] = {};
    gcrypt_ret = gcry_cipher_setkey(gcrypt_handle, key, sizeof(key));
    CHECK_LIBGCRYPT_RETURN_CODE( GPG_ERR_INV_KEYLEN, gcrypt_ret );
}

TEST(Libgcrypt_AesEncrypt, set_key_too_long_fails)
{
    char key[17] = {};
    gcrypt_ret = gcry_cipher_setkey(gcrypt_handle, key, sizeof(key));
    CHECK_LIBGCRYPT_RETURN_CODE( GPG_ERR_INV_KEYLEN, gcrypt_ret );
}

/*
 * Set IV
 */
TEST(Libgcrypt_AesEncrypt, set_iv)
{
    char iv[16] = {};

    /*
     * gcry_error_t gcry_cipher_setiv (gcry_cipher_hd_t h, const void *k, size_t l)
     *
     * Set the initialization vector used for encryption or decryption.
     * The vector is passed as the buffer K of length l bytes and copied to internal data structures.
     *
     * Returns 0 on success and a non-zero error code on error.
     */
    gcrypt_ret = gcry_cipher_setiv( gcrypt_handle, iv, sizeof(iv) );
    CHECK_LIBGCRYPT_RETURN_CODE( GPG_ERR_NO_ERROR, gcrypt_ret );
}

// These tests work but libgcrypt prints a warning directly to the console.
// Disable them until I figure out how to trap the output.
#if 0
TEST(Libgcrypt_AesEncrypt, set_iv_too_short_prints_warning)
{
    char iv[15] = {};
    gcrypt_ret = gcry_cipher_setiv(gcrypt_handle, iv, sizeof(iv));
    CHECK_LIBGCRYPT_RETURN_CODE( GPG_ERR_NO_ERROR, gcrypt_ret );
}

TEST(Libgcrypt_AesEncrypt, set_iv_too_long_prints_warning)
{
    char iv[17] = {};
    gcrypt_ret = gcry_cipher_setiv(gcrypt_handle, iv, sizeof(iv));
    CHECK_LIBGCRYPT_RETURN_CODE( GPG_ERR_NO_ERROR, gcrypt_ret );
}
#endif

#if 0
TEST(Libgcrypt_AesEncrypt, set_null_key_segfaults)
{
    gcrypt_ret = gcry_cipher_setkey(gcrypt_handle, NULL, 16);
}
#endif
