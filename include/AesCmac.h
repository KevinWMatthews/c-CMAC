#ifndef AES_CMAC_INCLUDED
#define AES_CMAC_INCLUDED

#include <stdint.h>
#include <stddef.h>

int AesCmac_Calculate128(uint8_t key[16], size_t key_len,
        uint8_t *message, size_t message_len,
        uint8_t *aes_cmac, size_t aes_cmac_len);


typedef struct AES_CMAC_CALCULATE_128_PARAMS
{
    size_t key_len;
    uint8_t *key;
    size_t message_len;
    uint8_t *message;
} AES_CMAC_CALCULATE_128_PARAMS;
int AesCmac_Calculate128_2(AES_CMAC_CALCULATE_128_PARAMS *params, uint8_t aes_cmac[16], size_t aes_cmac_len);

#endif
