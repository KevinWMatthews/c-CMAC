extern "C"
{
#include "CmacAesOps.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include <string.h>

TEST_GROUP(Initialize)
{
    CMAC_AES_CONTEXT context;
    AES128_CREATE_PARAMS params;
    AES128_HANDLE aes_handle;
    uint8_t key[16];
    uint8_t iv[16];
    int ret;

    void setup()
    {
        mock().strictOrder();
    }

    void teardown()
    {
    }
};

TEST(Initialize, initialize_with_key_of_00s)
{
    memset(key, 0x00, sizeof(key));
    memset(iv, 0x00, sizeof(iv));   // Required by spec

    params.key = key;
    params.key_len = sizeof(key);
    params.iv = iv;
    params.iv_len = sizeof(iv);

    mock().expectOneCall("Aes128_Initialize")
        .andReturnValue(AES128_SUCCESS);
    mock().expectOneCall("Aes128_Create")
        .withParameterOfType("AES128_CREATE_PARAMS", "params", &params)
        // Probably skip the copier and fill the struct manually.
        // If we do this, we can't specify the parameter at all - the mock would check pointer addresses
        // Do we need to malloc or destroy something?
        // .withOutputParameter("aes_handle",
        .withOutputParameterReturning("aes_handle", NULL, 0) ;
    ret = CmacAesOps_Initialize( &context, key, sizeof(key) );

    LONGS_EQUAL( 0, ret );
    mock().checkExpectations();     // Hack to work around scoping issues with comparator.
}

TEST(Initialize, initialize_with_key_of_ffs)
{
    memset(key, 0xff, sizeof(key));

    params.key = key;
    params.key_len = sizeof(key);
    params.iv = iv;
    params.iv_len = sizeof(iv);

    mock().expectOneCall("Aes128_Initialize")
        .andReturnValue(AES128_SUCCESS);
    mock().expectOneCall("Aes128_Create")
        .withParameterOfType("AES128_CREATE_PARAMS", "params", &params)
        // Hack until I figure out how to use a copier
        .withOutputParameterReturning("aes_handle", NULL, 0) ;
    ret = CmacAesOps_Initialize( &context, key, sizeof(key) );

    LONGS_EQUAL( 0, ret );
    mock().checkExpectations();     // Hack to work around scoping issues with comparator.
}
