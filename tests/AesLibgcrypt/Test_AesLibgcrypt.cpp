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

void expect_initialize_libgcrypt(void)
{
    const char *required_version = "1.8.2";

    mock().expectOneCall("gcry_check_version")
        .withParameter("req_version", required_version)
        .andReturnValue(required_version);

    mock().expectOneCall("gcry_control")
        .withParameter("cmd", GCRYCTL_DISABLE_SECMEM)
        // Not sure if/how to test varargs. Not needed since it's NULL.
        .andReturnValue(GPG_ERR_NO_ERROR);

    mock().expectOneCall("gcry_control")
        .withParameter("cmd", GCRYCTL_INITIALIZATION_FINISHED)
        .andReturnValue(GPG_ERR_NO_ERROR);
}

TEST(AesLibgcrypt, initialize_libgcrypt)
{
    expect_initialize_libgcrypt();
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

TEST(AesLibgcrypt, destroy_aes_handle)
{
    Aes128_Destroy(&aes);
    CHECK_TRUE( aes == NULL );
}

IGNORE_TEST(AesLibgcrypt, encrypt_message_0_key_0_iv_0)
{
    expect_initialize_libgcrypt();
    mock().expectOneCall("gcry_cipher_open")
        // Need to make a comparator? This pointer is hidden.
        .withParameter("hd", 0/* ? */)
        .withParameter("algo", GCRY_CIPHER_AES128)
        .withParameter("mode", GCRY_CIPHER_MODE_CBC)
        .withParameter("flags", 0)
        .andReturnValue(GPG_ERR_NO_ERROR);

    // Init
    Aes128_Initialize();
    // Create
    // Encrypt
    // Check against value calculated from a known-good source.
    // Destroy
}
