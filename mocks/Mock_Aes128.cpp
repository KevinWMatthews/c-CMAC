extern "C"
{
#include "Aes128.h"
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
        .withParameter("params", params)
        .withParameter("aes_handle", aes_handle);
    return (AES128_RETURN_CODE)mock().intReturnValue();
}
