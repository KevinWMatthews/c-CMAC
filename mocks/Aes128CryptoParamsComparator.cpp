extern "C"
{
#include "Aes128.h"
}

#include "Aes128CryptoParamsComparator.h"

bool Aes128CryptoParamsComparator::isEqual(const void* object1, const void* object2)
{
    const AES128_CRYPTO_PARAMS *params1 = (const AES128_CRYPTO_PARAMS *)object1;
    const AES128_CRYPTO_PARAMS *params2 = (const AES128_CRYPTO_PARAMS *)object2;

    if (object1 == NULL)
        return false;
    if (object2 == NULL)
        return false;

    SimpleString input1 = StringFromBinaryWithSize(params1->input, params1->input_len);
    SimpleString input2 = StringFromBinaryWithSize(params2->input, params2->input_len);

    if (input1 != input2)
        return false;

    if ( !createComparator.isEqual(params1->aes_handle, params2->aes_handle) )
        return false;

    return true;
}

SimpleString Aes128CryptoParamsComparator::valueToString(const void* object)
{
    const AES128_CRYPTO_PARAMS *params = (const AES128_CRYPTO_PARAMS *)object;

    if (params == NULL)
        return StringFrom("AES128_CRYPTO_PARAMS: NULL");

    SimpleString aes_handle;

    aes_handle = createComparator.valueToString(params->aes_handle);

    SimpleString input = StringFromBinaryWithSize(params->input, params->input_len);

    return StringFrom("AES128_CRYPTO_PARAMS: {") + aes_handle + StringFrom(", input: ") + input + StringFrom("}");
}
