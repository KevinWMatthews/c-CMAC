extern "C"
{
#include "Aes.h"
}

#include "CppUTestExt/MockSupport.h"

int Aes_Calculate128(uint8_t key[16], uint8_t iv[16], uint8_t *input, uint8_t *output)
{
    mock().actualCall("Aes_Calculate128")
        .withParameter("key", key)
        .withParameter("iv", iv)
        .withParameter("input", input)
        .withOutputParameter("output", output);
    return mock().intReturnValue();
}
