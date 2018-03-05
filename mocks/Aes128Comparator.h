#ifndef AES_128_COMPARATOR_INCLUDED
#define AES_128_COMPARATOR_INCLUDED

class Aes128Comparator : public MockNamedValueComparator
{
public:
    virtual bool isEqual(const void* object1, const void* object2);
    virtual SimpleString valueToString(const void* object);
};

#endif
