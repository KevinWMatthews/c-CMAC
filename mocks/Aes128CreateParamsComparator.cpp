#include "Aes128CreateParamsComparator.h"

bool Aes128CreateParamsComparator::isEqual(const void* object1, const void* object2)
{
    return true;
}

SimpleString Aes128CreateParamsComparator::valueToString(const void* object)
{
    return StringFrom("Aes128 Create Params");
}
