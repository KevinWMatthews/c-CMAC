extern "C"
{
#include <gcrypt.h>
}

#include "CppUTest/TestHarness.h"
#include "Libgcrypt_TestHelper.h"

#define LIBGCRYPT_REQURIED_VERSION      "1.8.2"

TEST_GROUP(Libgcrypt_AesEncrypt)
{
    gcry_error_t gcry_error;
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
    gcry_error = gcry_cipher_setkey( gcrypt_handle, key, sizeof(key) );
    CHECK_LIBGCRYPT_RETURN_CODE( GPG_ERR_NO_ERROR, gcry_error );
}


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
    gcry_error = gcry_cipher_setiv( gcrypt_handle, iv, sizeof(iv) );
    CHECK_LIBGCRYPT_RETURN_CODE( GPG_ERR_NO_ERROR, gcry_error );
}

TEST(Libgcrypt_AesEncrypt, set_key_too_short_fails)
{
    char key[15] = {};
    gcry_error = gcry_cipher_setkey(gcrypt_handle, key, sizeof(key));
    CHECK_LIBGCRYPT_RETURN_CODE( GPG_ERR_INV_KEYLEN, gcry_error );
}

TEST(Libgcrypt_AesEncrypt, set_key_too_long_fails)
{
    char key[17] = {};
    gcry_error = gcry_cipher_setkey(gcrypt_handle, key, sizeof(key));
    CHECK_LIBGCRYPT_RETURN_CODE( GPG_ERR_INV_KEYLEN, gcry_error );
}

// These tests work but libgcrypt prints a warning directly to the console.
// Disable them until I figure out how to trap the output.
#if 0
TEST(Libgcrypt_AesEncrypt, set_iv_too_short_prints_warning)
{
    char iv[15] = {};
    gcry_error = gcry_cipher_setiv(gcrypt_handle, iv, sizeof(iv));
    CHECK_LIBGCRYPT_RETURN_CODE( GPG_ERR_NO_ERROR, gcry_error );
}

TEST(Libgcrypt_AesEncrypt, set_iv_too_long_prints_warning)
{
    char iv[17] = {};
    gcry_error = gcry_cipher_setiv(gcrypt_handle, iv, sizeof(iv));
    CHECK_LIBGCRYPT_RETURN_CODE( GPG_ERR_NO_ERROR, gcry_error );
}
#endif

#if 0
TEST(Libgcrypt_AesEncrypt, set_null_key_segfaults)
{
    gcry_error = gcry_cipher_setkey(gcrypt_handle, NULL, 16);
}
#endif
