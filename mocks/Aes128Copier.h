#ifndef AES128_COPIER_INCLUDED
#define AES128_COPIER_INCLUDED

#include "CppUTestExt/MockSupport.h"

class Aes128Copier : public MockNamedValueCopier
{
public:
    virtual void copy(void* out, const void* in);
};

#endif
