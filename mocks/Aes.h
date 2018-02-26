#ifndef AES_INCLUDED
#define AES_INCLUDED

#include <stdint.h>

int Aes_Calculate128(uint8_t key[16], uint8_t iv[16], uint8_t *input, uint8_t *output);

#endif
