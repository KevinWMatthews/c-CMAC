#ifndef AES_128_INCLUDED
#define AES_128_INCLUDED

#include <stddef.h>
#include <stdint.h>

typedef enum
{
    AES128_SUCCESS              =  0,
    AES128_FAILURE              = -1,
    AES128_NULL_POINTER         = -2,
    AES128_INVALID_KEY          = -3,
    AES128_INVALID_IV           = -4,
} AES128_RETURN_CODE;
AES128_RETURN_CODE Aes128_Initialize(void);

typedef struct AES128_STRUCT * AES128;

typedef struct AES128_CREATE_PARAMS
{
    uint8_t *key;
    size_t key_len;
    uint8_t *iv;
    size_t iv_len;
} AES128_CREATE_PARAMS;
AES128_RETURN_CODE Aes128_Create(AES128_CREATE_PARAMS *params, AES128 *aes_handle);

void Aes128_Destroy(AES128 * self);

typedef struct AES128_CRYPTO_PARAMS
{
    AES128 aes_handle;
    uint8_t *input;
} AES128_CRYPTO_PARAMS;
AES128_RETURN_CODE Aes128_Encrypt(AES128 self, uint8_t * input, size_t input_len, uint8_t * output, size_t output_len);
AES128_RETURN_CODE Aes128_Encrypt2(AES128_CRYPTO_PARAMS *params, uint8_t *output, size_t output_len);

#endif
