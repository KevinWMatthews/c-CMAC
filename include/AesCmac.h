#ifndef AES_CMAC_INCLUDED
#define AES_CMAC_INCLUDED

#include <stdint.h>
#include <stddef.h>

int AesCmac_Calculate128(uint8_t key[16], size_t key_len,
        uint8_t *message, size_t message_len,
        uint8_t *aes_cmac, size_t aes_cmac_len);

int AesCmac_Calculate128_(uint8_t key[16], size_t key_len,
        uint8_t *message, size_t message_len,
        uint8_t *aes_cmac, size_t aes_cmac_len);

#endif
