extern "C"
{
#include "Aes128.h"
#include "Mock_Aes128.h"
}

#include "CppUTestExt/MockSupport.h"

AES128_RETURN_CODE Aes128_Initialize(void)
{
    mock().actualCall("Aes128_Initialize");
    return (AES128_RETURN_CODE)mock().intReturnValue();
}

AES128_RETURN_CODE Aes128_Create(AES128_CREATE_PARAMS *params, AES128_HANDLE *aes_handle)
{
    mock().actualCall("Aes128_Create")
        .withParameterOfType("AES128_CREATE_PARAMS", "params", params)
        .withParameter("aes_handle", aes_handle);
    return (AES128_RETURN_CODE)mock().intReturnValue();
}

AES128_RETURN_CODE Aes128_Create2(AES128_CREATE_PARAMS *params, AES128_HANDLE *aes_handle)
{
    AES128_HANDLE self = (AES128_HANDLE)calloc(1, sizeof(*self));
    self->key = params->key;
    self->key_len = params->key_len;
    self->iv = params->iv;
    self->iv_len = params->iv_len;

    *aes_handle = self;
    return (AES128_RETURN_CODE)mock().intReturnValue();
}

AES128_RETURN_CODE Aes128_Create3(AES128_CREATE_PARAMS *params, AES128_HANDLE *aes_handle)
{
    AES128_HANDLE self = (AES128_HANDLE)calloc(1, sizeof(*self));

    mock().actualCall("Aes128_Create3");

    *aes_handle = self;
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

void Aes128_Destroy(AES128_HANDLE *self)
{
    if (self)
        free(*self);
    // *self = 0;
}
