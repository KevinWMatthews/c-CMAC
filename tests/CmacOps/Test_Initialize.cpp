extern "C"
{
#include "CmacAesOps.h"
#include "MockAes128.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include <string.h>

TEST_GROUP(Initialize)
{
    CMAC_AES_CONTEXT context;
    AES128_CREATE_PARAMS params;
    AES128_STRUCT mock_aes_struct;
    AES128_HANDLE mock_aes_handle;
    uint8_t key[16];
    uint8_t iv[16];
    int ret;

    void setup()
    {
        mock().strictOrder();

        memset(iv, 0x00, sizeof(iv));   // Required by spec

        params.key = key;
        params.key_len = sizeof(key);
        params.iv = iv;
        params.iv_len = sizeof(iv);

        mock_aes_struct.key = key;
        mock_aes_struct.key_len = sizeof(key);
        mock_aes_struct.iv = iv;
        mock_aes_struct.iv_len = sizeof(iv);
        mock_aes_handle = &mock_aes_struct;
    }

    void teardown()
    {
    }
};

TEST(Initialize, initialize_with_key_of_00s)
{
    memset(key, 0x00, sizeof(key));

    mock().expectOneCall("Aes128_Initialize")
        .andReturnValue(AES128_SUCCESS);
    mock().expectOneCall("Aes128_Create")
        .withParameterOfType("AES128_CREATE_PARAMS", "params", &params)
        .withOutputParameterOfTypeReturning("AES128_HANDLE", "aes_handle", &mock_aes_handle);

    ret = CmacAesOps_Initialize( &context, key, sizeof(key) );

    LONGS_EQUAL( 0, ret );
}

TEST(Initialize, initialize_with_key_of_ffs)
{
    memset(key, 0xff, sizeof(key));

    mock().expectOneCall("Aes128_Initialize")
        .andReturnValue(AES128_SUCCESS);
    mock().expectOneCall("Aes128_Create")
        .withParameterOfType("AES128_CREATE_PARAMS", "params", &params)
        .withOutputParameterOfTypeReturning("AES128_HANDLE", "aes_handle", &mock_aes_handle);

    ret = CmacAesOps_Initialize( &context, key, sizeof(key) );

    LONGS_EQUAL( 0, ret );
}
