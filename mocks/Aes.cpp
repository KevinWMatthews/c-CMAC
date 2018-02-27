extern "C"
{
#include "Aes.h"
}

#include "CppUTestExt/MockSupport.h"

int Aes_Calculate128(uint8_t key[16], uint8_t iv[16], uint8_t *input, uint8_t *output)
{
    mock().actualCall("Aes_Calculate128")
        .withMemoryBufferParameter("key", key, 16)
        .withMemoryBufferParameter("iv", iv, 16)
        .withMemoryBufferParameter("input", input, 16)
        .withOutputParameter("output", output);
    return mock().intReturnValue();
}
