extern "C"
{
#include "Aes.h"
}

#include "CppUTestExt/MockSupport.h"
#include "Aes128Comparator.h"

bool Aes128Comparator::isEqual(const void* object1, const void* object2)
{
    const AES_KEY_128 *aes1 = (const AES_KEY_128 *)object1;
    const AES_KEY_128 *aes2 = (const AES_KEY_128 *)object2;

    SimpleString key1 = StringFromBinaryWithSize(aes1->key, aes1->key_len);
    SimpleString key2 = StringFromBinaryWithSize(aes2->key, aes2->key_len);

    SimpleString iv1 = StringFromBinaryWithSize(aes1->iv, aes1->iv_len);
    SimpleString iv2 = StringFromBinaryWithSize(aes2->iv, aes2->iv_len);

    if (key1 != key2)
    {
        return 0;
    }

    if (iv1 != iv2)
    {
        return 0;
    }

    return 1;
}

SimpleString Aes128Comparator::valueToString(const void* object)
{
    const AES_KEY_128 *aes_handle = (const AES_KEY_128 *)object;

    SimpleString key = StringFromBinaryWithSize(aes_handle->key, aes_handle->key_len);
    SimpleString iv = StringFromBinaryWithSize(aes_handle->iv, aes_handle->iv_len);

    return StringFrom("key: ") + key + StringFrom("; iv: ") + iv;
}
