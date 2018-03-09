extern "C"
{
#include "Aes128.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(AesLibgcrypt)
{
    int ret;

    void setup()
    {
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
    AES128 aes = NULL;
    AES128_KEY key = {};
    AES128_IV iv = {};

    aes = Aes128_Create(&key, &iv);
    CHECK_TRUE( aes != NULL );
}
