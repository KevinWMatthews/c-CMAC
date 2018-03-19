extern "C"
{
#include "Aes128.h"
}

#include "Aes128CreateParamsComparator.h"

bool Aes128CreateParamsComparator::isEqual(const void* object1, const void* object2)
{
    const AES128_CREATE_PARAMS *params1 = (const AES128_CREATE_PARAMS *)object1;
    const AES128_CREATE_PARAMS *params2 = (const AES128_CREATE_PARAMS *)object2;

    if (params1 == NULL)
        return false;
    if (params2 == NULL)
        return false;

    SimpleString key1 = StringFromBinaryWithSize(params1->key, params1->key_len);
    SimpleString key2 = StringFromBinaryWithSize(params2->key, params2->key_len);

    if (key1 != key2)
        return false;

    SimpleString iv1 = StringFromBinaryWithSize(params1->iv, params1->iv_len);
    SimpleString iv2 = StringFromBinaryWithSize(params2->iv, params2->iv_len);

    if (iv1 != iv2)
        return false;

    return true;
}

SimpleString Aes128CreateParamsComparator::valueToString(const void* object)
{
    const AES128_CREATE_PARAMS *params = (const AES128_CREATE_PARAMS *)object;

    if (params == NULL)
        return StringFrom("AES128_CREATE_PARAMS: NULL");

    SimpleString key = StringFromBinaryWithSize(params->key, params->key_len);
    SimpleString iv = StringFromBinaryWithSize(params->iv, params->iv_len);

    return StringFrom("AES128_CREATE_PARAMS: {") + StringFrom("key: ") + key + StringFrom(", iv: ") + iv + StringFrom("}");
}
