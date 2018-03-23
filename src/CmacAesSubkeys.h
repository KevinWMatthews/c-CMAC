#ifndef CMAC_AES_SUBKEYS_INCLUDED
#define CMAC_AES_SUBKEYS_INCLUDED

#include <stdint.h>
#include "Aes128.h"

int CmacAes_CalculateLFromK(AES128_HANDLE aes_handle, uint8_t *L, size_t L_len);

int CmacAes_CalculateK1FromL(uint8_t *L, size_t L_len, uint8_t *K1, size_t K1_len);

int CmacAes_CalculateK2FromK1(uint8_t *K1, size_t K1_len, uint8_t *K2, size_t K2_len);

#endif
