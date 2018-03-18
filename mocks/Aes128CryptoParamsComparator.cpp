extern "C"
{
#include "Aes128.h"
}

#include "Aes128CryptoParamsComparator.h"
#include "Aes128CreateParamsComparator.h"

bool Aes128CryptoParamsComparator::isEqual(const void* object1, const void* object2)
{
}

SimpleString Aes128CryptoParamsComparator::valueToString(const void* object)
{
    const AES128_CRYPTO_PARAMS *params = (const AES128_CRYPTO_PARAMS *)object;

    SimpleString aes_handle;
    Aes128CreateParamsComparator comparator;
    // aes_handle = comparator.valueToString(NULL);//params->aes_handle);
    SimpleString input = StringFromBinaryWithSize(params->input, params->input_len);

    return aes_handle + StringFrom(", input: ") + input;
}
