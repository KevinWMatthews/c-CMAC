extern "C"
{
#include "CmacAesOps.h"
#include "MockAes128.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(Uninitialize)
{
    CMAC_AES_CONTEXT context;
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

TEST(Uninitialize, destroy_aes_handle)
{
    AES128_CREATE_PARAMS create_params = {};
    create_params.key = key;
    create_params.key_len = sizeof(key);
    create_params.iv = iv;
    create_params.iv_len = sizeof(iv);

    aes_handle = MockAes128_Create(&create_params);
    LONGS_EQUAL( 16, sizeof(key));
    LONGS_EQUAL( 16, create_params.key_len );
    LONGS_EQUAL( 16, aes_handle->key_len );

    context.aes_handle = aes_handle;

    mock().expectOneCall("Aes128_Destroy");
    //TODO skp testing this until I figure out comparators and pointers.
        // .withParameterOfType("AES128_HANDLE", "self", aes_handle);

    ret = CmacAesOps_Unitialize(&context);
    LONGS_EQUAL( 0, ret );
}
