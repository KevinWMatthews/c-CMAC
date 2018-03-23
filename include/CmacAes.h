#ifndef CMAC_AES_INCLUDED
#define CMAC_AES_INCLUDED

#include <stdint.h>
#include <stddef.h>

int CmacAes_Calculate(uint8_t key[16], size_t key_len,
        uint8_t *message, size_t message_len,
        uint8_t *aes_cmac, size_t aes_cmac_len);


typedef struct CMAC_AES_CALCULATE_PARAMS
{
    size_t key_len;
    uint8_t *key;
    size_t message_len;
    uint8_t *message;
} CMAC_AES_CALCULATE_PARAMS;
int CmacAes_Calculate_2(CMAC_AES_CALCULATE_PARAMS *params, uint8_t aes_cmac[16], size_t aes_cmac_len);

#endif
