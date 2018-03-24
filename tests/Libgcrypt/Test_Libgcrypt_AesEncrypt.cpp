extern "C"
{
#include <gcrypt.h>
}

#include "CppUTest/TestHarness.h"

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

TEST(Libgcrypt_AesEncrypt, wiring_check)
{
    FAIL("START Here");
}
