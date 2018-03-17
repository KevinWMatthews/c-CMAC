extern "C"
{
#include "Aes128.h"
#include <gcrypt.h>
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(AesLibgcrypt2)
{
    int ret;

    void setup()
    {
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
