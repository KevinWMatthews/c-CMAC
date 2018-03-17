#ifndef AES_128_INCLUDED
#define AES_128_INCLUDED

#include <stddef.h>
#include <stdint.h>

typedef enum
{
    AES128_SUCCESS                  =  0,
    AES128_FAILURE                  = -1,
    AES128_NULL_POINTER             = -2,
    AES128_INVALID_KEY_LENGTH       = -3,
    AES128_INVALID_IV_LENGTH        = -4,
    AES128_INVALID_INPUT_LENGTH     = -5,
    AES128_INVALID_OUTPUT_LENGTH    = -6,
} AES128_RETURN_CODE;
AES128_RETURN_CODE Aes128_Initialize(void);

typedef struct AES128_STRUCT * AES128_HANDLE;

typedef struct AES128_CREATE_PARAMS
{
    size_t key_len;
    uint8_t *key;
    size_t iv_len;
    uint8_t *iv;
} AES128_CREATE_PARAMS;
AES128_RETURN_CODE Aes128_Create(AES128_CREATE_PARAMS *params, AES128_HANDLE *aes_handle);

void Aes128_Destroy(AES128_HANDLE * self);

typedef struct AES128_CRYPTO_PARAMS
{
    AES128_HANDLE aes_handle;
    size_t input_len;
    uint8_t *input;
} AES128_CRYPTO_PARAMS;
AES128_RETURN_CODE Aes128_Encrypt2(AES128_CRYPTO_PARAMS *params, uint8_t *output, size_t output_len);

#endif
