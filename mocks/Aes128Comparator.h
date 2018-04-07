#ifndef AES128_COMPARATOR_INCLUDED
#define AES128_COMPARATOR_INCLUDED

#include "CppUTestExt/MockSupport.h"

// This comparator is only valid for mocked AES128 handles.
// Mock AES128 handles store their keys and IVs.
// Handles are considered identical if they contain the same keys and IVs because
// the effect of each will be the same.
//
// Production code may not contain the struct elements required for this to work -
// the key and IV are passed to the production code library to manage.

class Aes128Comparator : public MockNamedValueComparator
{
public:
    virtual bool isEqual(const void* object1, const void* object2);
    virtual SimpleString valueToString(const void* object);
};

#endif
