#ifndef AES_CMAC_SUBKEYS_INCLUDED
#define AES_CMAC_SUBKEYS_INCLUDED

#include <stdint.h>
#include "Aes.h"

// Do I want to change this AES_KEY parameter? Probably.
// CMAC forces the IV to 0, so the high level shouldn't be allowed to set it.
// Figure out what layer needs to know this detail.
int AesCmac_GenerateSubkeys(AES_KEY_128 *aes_key, uint8_t K1[16], uint8_t K2[16]);

int AesCmac_CalculateK1FromL(uint8_t *L, size_t L_len, uint8_t *K1, size_t K1_len);

#endif
