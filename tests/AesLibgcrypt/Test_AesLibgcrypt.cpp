extern "C"
{
#include "Aes128.h"
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
    }

    void teardown()
    {
    }
};

TEST(AesLibgcrypt, initialize_libgcrypt)
{
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
