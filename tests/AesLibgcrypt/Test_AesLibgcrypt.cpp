extern "C"
{
#include "Aes128.h"
#include <gcrypt.h>
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(AesLibgcrypt)
{
    AES128 aes;
    int ret;

    void setup()
    {
        aes = NULL;
        mock().strictOrder();
    }

    void teardown()
    {
        mock().checkExpectations();
        mock().clear();
    }
};

#define LIBGCRYPT_SUCCESS       0

TEST(AesLibgcrypt, initialize_libgcrypt)
{
    mock().expectOneCall("gcry_check_version")
        .withParameter("req_version", "1.8.2")
        .andReturnValue("1.8.2");

    mock().expectOneCall("gcry_control")
        .withParameter("cmd", GCRYCTL_DISABLE_SECMEM)
        // Not sure if/how to test varargs. Not needed since it's NULL.
        .andReturnValue(LIBGCRYPT_SUCCESS);

    ret = Aes128_Initialize();
    LONGS_EQUAL( AES128_SUCCESS, ret );
}


TEST(AesLibgcrypt, create_aes_handle)
{
    AES128_KEY key = {};
    AES128_IV iv = {};

    aes = Aes128_Create(&key, &iv);
    CHECK_TRUE( aes != NULL );
}

IGNORE_TEST(AesLibgcrypt, destroy_aes_handle)
{
    // Aes128_Destroy(&aes);
    // CHECK_TRUE( aes == NULL );
}

IGNORE_TEST(AesLibgcrypt, encrypt_message_0_key_0_iv_0)
{
    // Create
    // Encrypt
    // Check against value calculated from a known-good source.
}
