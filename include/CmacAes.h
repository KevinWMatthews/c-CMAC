#ifndef CMAC_AES_INCLUDED
#define CMAC_AES_INCLUDED

#include <stdint.h>
#include <stddef.h>

typedef struct CMAC_AES_CALCULATE_PARAMS
{
    size_t key_len;
    uint8_t *key;
    size_t message_len;
    uint8_t *message;
} CMAC_AES_CALCULATE_PARAMS;
int CmacAes_Calculate(CMAC_AES_CALCULATE_PARAMS *params, uint8_t aes_cmac[16], size_t aes_cmac_len);

#endif
