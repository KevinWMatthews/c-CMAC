extern "C"
{
#include "Aes128.h"
#include "Mock_Aes128.h"
}

#include "CppUTestExt/MockSupport.h"

static AES128_STRUCT aes128_struct;

AES128_HANDLE Mock_Aes128_Create(AES128_CREATE_PARAMS *params)
{
    aes128_struct.key = params->key;
    aes128_struct.key_len = params->key_len;
    aes128_struct.iv = params->iv;
    aes128_struct.iv_len = params->iv_len;
    return &aes128_struct;
}

void Mock_Aes128_Destroy(AES128_HANDLE self)
{
    return;
}



AES128_RETURN_CODE Aes128_Initialize(void)
{
    mock().actualCall("Aes128_Initialize");
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
