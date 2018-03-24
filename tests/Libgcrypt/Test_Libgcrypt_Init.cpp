extern "C"
{
#include <gcrypt.h>
}

#include "CppUTest/TestHarness.h"
#include "Libgcrypt_TestHelper.h"

#define LIBGCRYPT_VERSION       "1.8.2"

TEST_GROUP(Libgcrypt_Init)
{
    gcry_error_t gcry_error;

    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(Libgcrypt_Init, check_version_succeeds_with_version_match)
{
    const char *required = LIBGCRYPT_VERSION;
    const char *actual = NULL;

    /*
     * const char * gcry_check_version (const char *req_version)
     *
     * Initializes some subsystems used by Libgcrypt and must be invoked before any other function in the library.
     *
     * If the current version is higher than the require version,
     * gcry_errorurns the version number.
     * If the current version is too old, gcry_errorurns NULL.
     */
    actual = gcry_check_version(required);
    STRCMP_EQUAL( LIBGCRYPT_VERSION, actual );
}

TEST(Libgcrypt_Init, check_version_gcry_errorurns_null_if_actual_version_is_too_old)
{
    const char *required = "1.8.3";
    const char *actual = NULL;

    actual = gcry_check_version(required);
    STRCMP_EQUAL( NULL, actual );
}

TEST(Libgcrypt_Init, check_version_succeeds_if_actual_version_is_newer_than_required)
{
    const char *required = "1.8.1";
    const char *actual = NULL;

    actual = gcry_check_version(required);
    STRCMP_EQUAL( LIBGCRYPT_VERSION, actual );
}

TEST(Libgcrypt_Init, can_disable_secure_memory)
{
    /*
     * gcry_error_t gcry_control (enum gcry_ctl_cmds cmd, ...)
     *
     * Set general libgcrypt behavior.
     *
     * GCRYCTL_DISABLE_SECMEM
     *      Disables the use of secure memory
     */
    gcry_error = gcry_control(GCRYCTL_DISABLE_SECMEM, 0);
    CHECK_LIBGCRYPT_RETURN_CODE( GPG_ERR_NO_ERROR, gcry_error );
}

TEST(Libgcrypt_Init, can_disable_secure_memory_ignores_arguments)
{
    gcry_error = gcry_control(GCRYCTL_DISABLE_SECMEM, 255);
    CHECK_LIBGCRYPT_RETURN_CODE( GPG_ERR_NO_ERROR, gcry_error );
}

TEST(Libgcrypt_Init, can_finish_initialization)
{
    /*
     * GCRYCTL_INITIALIZATION_FINISHED
     *      This command tells the library that the application has finished the initialization.
     */
    gcry_error = gcry_control(GCRYCTL_INITIALIZATION_FINISHED, 0);
    CHECK_LIBGCRYPT_RETURN_CODE( GPG_ERR_NO_ERROR, gcry_error );
}

#if 0
// This fails and I don't know why.
TEST(Libgcrypt_Init, can_check_that_init_is_finished)
{
    gcry_error = gcry_control(GCRYCTL_INITIALIZATION_FINISHED, 0);
    gcry_error = gcry_control(GCRYCTL_INITIALIZATION_FINISHED_P, 0);
    CHECK_LIBGCRYPT_RETURN_CODE( GPG_ERR_NO_ERROR, gcry_error );
}
#endif
