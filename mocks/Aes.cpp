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

int Aes_Calculate128_2(AES_KEY_128 *aes_key, uint8_t *input, size_t input_len, uint8_t *output, size_t output_len)
{
    mock().actualCall("Aes_Calculate128_2")
        .withParameter("aes_key", aes_key)
        .withMemoryBufferParameter("input", input, input_len)
        .withParameter("input_len", input_len)
        .withOutputParameter("output", output)
        .withParameter("output_len", output_len);
    return mock().intReturnValue();
}
