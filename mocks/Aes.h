#ifndef AES_128_INCLUDED
#define AES_128_INCLUDED

#include <stdint.h>
#include <stddef.h>

#define AES128_KEY_LEN     16
#define AES128_IV_LEN      16
typedef struct AES_KEY_128
{
    size_t key_len;
    uint8_t *key;
    size_t iv_len;
    uint8_t *iv;
} AES_KEY_128;

int Aes_Calculate128(AES_KEY_128 *aes_key,
        uint8_t *input, size_t input_len,
        uint8_t *output, size_t output_len);

#endif
