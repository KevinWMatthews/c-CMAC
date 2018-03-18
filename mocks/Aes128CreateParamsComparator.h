#ifndef AES128_CREATE_PARAMS_COMPARATOR_INCLUDED
#define AES128_CREATE_PARAMS_COMPARATOR_INCLUDED

#include "CppUTestExt/MockSupport.h"

class Aes128CreateParamsComparator : public MockNamedValueComparator
{
public:
    virtual bool isEqual(const void* object1, const void* object2);
    virtual SimpleString valueToString(const void* object);
};

#endif
