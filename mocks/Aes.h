#ifndef AES_INCLUDED
#define AES_INCLUDED

#include <stdint.h>
#include <stddef.h>

typedef struct AES_KEY_128
{
    uint8_t key[16];
    uint8_t iv[16];
} AES_KEY_128;
int Aes_Calculate128(uint8_t key[16], uint8_t iv[16], uint8_t *input, uint8_t *output);

int Aes_Calculate128_2(AES_KEY_128 *aes_key, uint8_t *input, size_t input_len, uint8_t *output, size_t output_len);

#endif
