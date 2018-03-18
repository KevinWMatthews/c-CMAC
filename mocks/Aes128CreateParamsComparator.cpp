extern "C"
{
#include "Aes128.h"
}

#include "Aes128CreateParamsComparator.h"

bool Aes128CreateParamsComparator::isEqual(const void* object1, const void* object2)
{
    return true;
}

SimpleString Aes128CreateParamsComparator::valueToString(const void* object)
{
    const AES128_CREATE_PARAMS *params = (const AES128_CREATE_PARAMS *)object;

    SimpleString key = StringFromBinaryWithSize(params->key, params->key_len);
    SimpleString iv = StringFromBinaryWithSize(params->iv, params->iv_len);

    return StringFrom("key: ") + key + StringFrom(", iv: ") + iv;
}
