extern "C"
{
#include "Aes128.h"
#include <gcrypt.h>
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(AesLibgcrypt2)
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

TEST(AesLibgcrypt2, initialize)
{
    ret = Aes128_Initialize();
    LONGS_EQUAL( AES128_SUCCESS, ret );
}

TEST(AesLibgcrypt2, create_aes_handle)
{
    AES128_KEY key = {};
    AES128_IV iv = {};

    aes = Aes128_Create(&key, &iv);
    CHECK_TRUE( aes != NULL );
}
