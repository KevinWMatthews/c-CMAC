extern "C"
{
#include <gcrypt.h>
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(Libgcrypt)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

#define LIBGCRYPT_VERSION       "1.8.2"
TEST(Libgcrypt, check_version_succeeds_with_version_match)
{
    const char *required = LIBGCRYPT_VERSION;
    const char *actual = NULL;

    actual = gcry_check_version(required);
    STRCMP_EQUAL( LIBGCRYPT_VERSION, actual );
}

TEST(Libgcrypt, check_version_returns_null_if_actual_version_is_too_old)
{
    const char *required = "1.8.3";
    const char *actual = NULL;

    actual = gcry_check_version(required);
    STRCMP_EQUAL( NULL, actual );
}

TEST(Libgcrypt, check_version_succeeds_if_actual_version_is_newer_than_required)
{
    const char *required = "1.8.1";
    const char *actual = NULL;

    actual = gcry_check_version(required);
    STRCMP_EQUAL( LIBGCRYPT_VERSION, actual );
}
