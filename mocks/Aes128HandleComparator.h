#ifndef AES128_HANDLE_COMPARATOR_INCLUDED
#define AES128_HANDLE_COMPARATOR_INCLUDED

#include "CppUTestExt/MockSupport.h"

class Aes128HandleComparator : public MockNamedValueComparator
{
public:
    virtual bool isEqual(const void* object1, const void* object2);
    virtual SimpleString valueToString(const void* object);
};

#endif
