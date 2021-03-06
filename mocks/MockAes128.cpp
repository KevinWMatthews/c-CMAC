extern "C"
{
#include "Aes128.h"
#include "MockAes128.h"
}

#include "CppUTestExt/MockSupport.h"

static AES128_STRUCT mock_aes_struct;

AES128_HANDLE MockAes128_Create(AES128_CREATE_PARAMS *params)
{
    mock_aes_struct.key = params->key;
    mock_aes_struct.key_len = params->key_len;
    mock_aes_struct.iv = params->iv;
    mock_aes_struct.iv_len = params->iv_len;
    return &mock_aes_struct;
}

void MockAes128_Destroy(AES128_HANDLE self)
{
    return;
}



AES128_RETURN_CODE Aes128_Encrypt(AES128_CRYPTO_PARAMS *params, uint8_t *output, size_t output_len)
{
    mock().actualCall("Aes128_Encrypt")
        .withParameterOfType("AES128_CRYPTO_PARAMS", "params", params)
        .withOutputParameter("output", output)
        .withParameter("output_len", output_len);
    return (AES128_RETURN_CODE)mock().intReturnValue();
}
