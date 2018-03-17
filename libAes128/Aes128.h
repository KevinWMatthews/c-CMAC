#ifndef AES_128_INCLUDED
#define AES_128_INCLUDED

#include <stddef.h>
#include <stdint.h>

typedef enum
{
    AES128_SUCCESS      =  0,
    AES128_FAILURE      = -1,
    AES128_NULL_POINTER = -2,
} AES128_RETURN_CODE;
AES128_RETURN_CODE Aes128_Initialize(void);

typedef struct AES128_STRUCT * AES128;

typedef struct AES128_KEY
{
    size_t length;
    uint8_t *buffer;
} AES128_KEY;
typedef struct AES128_IV
{
    size_t length;
    uint8_t *buffer;
} AES128_IV;
AES128_RETURN_CODE Aes128_Create(AES128_KEY * key, AES128_IV * iv, AES128 * self);

void Aes128_Destroy(AES128 * self);

AES128_RETURN_CODE Aes128_Encrypt(AES128 self, uint8_t * input, size_t input_len, uint8_t * output, size_t output_len);

#endif
