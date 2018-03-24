extern "C"
{
#include <gcrypt.h>
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(Libgcrypt_CreateCipherHandle)
{
    gcry_error_t gcry_error;
    gcry_cipher_hd_t gcrypt_handle;

    void setup()
    {
    }

    void teardown()
    {
    }
};

#define LIBGCRYPT_REQURIED_VERSION      "1.8.2"

TEST(Libgcrypt_CreateCipherHandle, open_and_close_cipher_handle)
{
    gcry_check_version(LIBGCRYPT_REQURIED_VERSION);
    gcry_control(GCRYCTL_DISABLE_SECMEM, 0);
    gcry_control(GCRYCTL_INITIALIZATION_FINISHED, 0);

    /*
     * gcry_error_t gcry_cipher_open (gcry_cipher_hd_t *hd, int algo, int mode, unsigned int flags)
     *
     * Create the cipher context and returns a handle to it in ‘hd’.
     *
     * The available cipher algorithms, modes, and flags are listed in gcrypt.h. See:
     *      enum gcry_cipher_algos and the defines below it.
     *      enum gcry_cipher_modes
     *      gcry_cipher_flags, or can be set to 0
     *
     * Returns 0 on success and a non-zero error code on error.
     */
    gcry_error = gcry_cipher_open(&gcrypt_handle, GCRY_CIPHER_AES128, GCRY_CIPHER_MODE_CBC, 0);
    LONGS_EQUAL( GPG_ERR_NO_ERROR, gcry_error );

    /*
     * void gcry_cipher_close (gcry_cipher_hd_t h)
     *
     * Close the cipher context.
     * The handle is will no longer be valid.
     */
    gcry_cipher_close(gcrypt_handle);
}

#if 0
TEST(Libgcrypt_CreateCipherHandle, null_cipher_handle_will_segfault)
{
    gcry_error = gcry_cipher_open(NULL, GCRY_CIPHER_AES128, GCRY_CIPHER_MODE_CBC, 0);
}
#endif

TEST(Libgcrypt_CreateCipherHandle, invalid_cipher_mode_fails)
{
    gcry_error = gcry_cipher_open(&gcrypt_handle, 255, GCRY_CIPHER_MODE_CBC, 0);

    CHECK_FALSE( gcry_error == GPG_ERR_NO_ERROR );
    LONGS_EQUAL( GPG_ERR_CIPHER_ALGO, gcry_err_code(gcry_error) );
}

TEST(Libgcrypt_CreateCipherHandle, invalid_cipher_flags_fail)
{
    gcry_error = gcry_cipher_open(&gcrypt_handle, GCRY_CIPHER_AES128, 255, 0);

    LONGS_EQUAL( GPG_ERR_INV_CIPHER_MODE, gcry_err_code(gcry_error) );
}
