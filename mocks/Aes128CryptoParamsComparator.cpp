extern "C"
{
#include "Aes128.h"
}

#include "Aes128CryptoParamsComparator.h"

bool Aes128CryptoParamsComparator::isEqual(const void* object1, const void* object2)
{
}

SimpleString Aes128CryptoParamsComparator::valueToString(const void* object)
{
    const AES128_CRYPTO_PARAMS *params = (const AES128_CRYPTO_PARAMS *)object;

    if (params == NULL)
        return StringFrom("NULL");

    SimpleString aes_handle;

    aes_handle = createComparator.valueToString(params->aes_handle);

    SimpleString input = StringFromBinaryWithSize(params->input, params->input_len);

    return StringFrom("AES128_CRYPTO_PARAMS: {") + aes_handle + StringFrom(", input: ") + input + StringFrom("}");
}
