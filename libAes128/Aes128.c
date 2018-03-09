#include "Aes128.h"

typedef struct AES128_STRUCT
{
    int placeholder;
} AES128_STRUCT;

static AES128_STRUCT aes128;

AES128_RETURN_CODE Aes128_Initialize(void)
{
    return AES128_SUCCESS;
}

AES128 Aes128_Create(AES128_KEY * key, AES128_IV * iv)
{
    return &aes128;
}
