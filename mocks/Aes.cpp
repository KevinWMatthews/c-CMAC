extern "C"
{
#include "Aes.h"
}

#include "CppUTestExt/MockSupport.h"

int Aes_Calculate128(AES_KEY_128 *aes_key, uint8_t *input, size_t input_len, uint8_t *output, size_t output_len)
{
    mock().actualCall("Aes_Calculate128")
        .withParameterOfType("AES_KEY_128", "aes_128", (void *)aes_key)
        .withMemoryBufferParameter("input", input, input_len)
        .withParameter("input_len", input_len)
        .withOutputParameter("output", output)
        .withParameter("output_len", output_len);
    return mock().intReturnValue();
}
