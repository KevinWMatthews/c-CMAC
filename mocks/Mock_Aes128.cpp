extern "C"
{
#include "Aes128.h"
}

#include "CppUTestExt/MockSupport.h"

typedef struct AES128_STRUCT
{
    size_t key_len;
    uint8_t *key;
    size_t iv_len;
    uint8_t *iv;
} AES128_STRUCT;

static AES128_STRUCT aes128_struct;

AES128_RETURN_CODE Aes128_Initialize(void)
{
    mock().actualCall("Aes128_Initialize");
    return (AES128_RETURN_CODE)mock().intReturnValue();
}

AES128_RETURN_CODE Aes128_Create(AES128_CREATE_PARAMS *params, AES128_HANDLE *aes_handle)
{
    aes128_struct.key = params->key;
    aes128_struct.key_len = params->key_len;
    aes128_struct.iv = params->iv;
    aes128_struct.iv_len = params->iv_len;
    *aes_handle = &aes128_struct;

    mock().actualCall("Aes128_Create")
        .withParameter("params", params)
        .withOutputParameter("aes_handle", aes_handle);
    return (AES128_RETURN_CODE)mock().intReturnValue();
}

AES128_RETURN_CODE Aes128_Encrypt(AES128_CRYPTO_PARAMS *params, uint8_t *output, size_t output_len)
{
    mock().actualCall("Aes128_Encrypt")
        .withParameterOfType("AES128_CRYPTO_PARAMS", "params", params)
        .withOutputParameter("output", output)
        .withParameter("output_len", output_len);
    return (AES128_RETURN_CODE)mock().intReturnValue();
}
