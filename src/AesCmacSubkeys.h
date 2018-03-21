#ifndef AES_CMAC_SUBKEYS_INCLUDED
#define AES_CMAC_SUBKEYS_INCLUDED

#include <stdint.h>
#include "Aes.h"
#include "Aes128.h"

int AesCmac_GenerateSubkeys(AES128_HANDLE aes_handle,
        uint8_t K1[16], size_t K1_len,
        uint8_t K2[16], size_t K2_len);

int AesCmac_CalculateLFromK(AES128_HANDLE aes_handle, uint8_t *L, size_t L_len);

int AesCmac_CalculateK1FromL(uint8_t *L, size_t L_len, uint8_t *K1, size_t K1_len);

int AesCmac_CalculateK2FromK1(uint8_t *K1, size_t K1_len, uint8_t *K2, size_t K2_len);

#endif
