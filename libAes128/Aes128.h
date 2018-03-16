#ifndef AES_128_INCLUDED
#define AES_128_INCLUDED

#include <stddef.h>
#include <stdint.h>

typedef enum
{
    AES128_SUCCESS      =  0,
    AES128_FAILURE      = -1,
} AES128_RETURN_CODE;
AES128_RETURN_CODE Aes128_Initialize(void);

typedef struct AES128_STRUCT * AES128;

typedef struct AES128_KEY
{
    size_t key_len;
    uint8_t key;
} AES128_KEY;
typedef struct AES128_IV
{
    size_t iv_len;
    uint8_t *iv;
} AES128_IV;
AES128 Aes128_Create(AES128_KEY * key, AES128_IV * iv);

#endif