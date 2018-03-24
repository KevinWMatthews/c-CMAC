extern "C"
{
#include <gcrypt.h>
}

#include "CppUTest/TestHarness.h"
#include "Libgcrypt_TestHelper.h"

#define LIBGCRYPT_REQURIED_VERSION      "1.8.2"

TEST_GROUP(Libgcrypt_CreateCipherHandle)
{
    gcry_error_t gcrypt_ret;
    gcry_cipher_hd_t gcrypt_handle;

    void setup()
    {
        gcry_check_version(LIBGCRYPT_REQURIED_VERSION);
        gcry_control(GCRYCTL_DISABLE_SECMEM, 0);
        gcry_control(GCRYCTL_INITIALIZATION_FINISHED, 0);
    }

    void teardown()
    {
    }
};

TEST(Libgcrypt_CreateCipherHandle, open_and_close_cipher_handle)
{
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
    gcrypt_ret = gcry_cipher_open(&gcrypt_handle, GCRY_CIPHER_AES128, GCRY_CIPHER_MODE_CBC, 0);
    CHECK_LIBGCRYPT_RETURN_CODE( GPG_ERR_NO_ERROR, gcrypt_ret );

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
    gcrypt_ret = gcry_cipher_open(NULL, GCRY_CIPHER_AES128, GCRY_CIPHER_MODE_CBC, 0);
}
#endif

TEST(Libgcrypt_CreateCipherHandle, invalid_cipher_mode_fails)
{
    gcrypt_ret = gcry_cipher_open(&gcrypt_handle, 255, GCRY_CIPHER_MODE_CBC, 0);

    CHECK_LIBGCRYPT_RETURN_CODE( GPG_ERR_CIPHER_ALGO, gcrypt_ret );
}

TEST(Libgcrypt_CreateCipherHandle, invalid_cipher_flags_fail)
{
    gcrypt_ret = gcry_cipher_open(&gcrypt_handle, GCRY_CIPHER_AES128, 255, 0);

    CHECK_LIBGCRYPT_RETURN_CODE( GPG_ERR_INV_CIPHER_MODE, gcrypt_ret );
}
