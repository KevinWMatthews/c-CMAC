#ifndef AES_CMAC_SUBKEYS_INCLUDED
#define AES_CMAC_SUBKEYS_INCLUDED

#include <stdint.h>
#include "Aes.h"

int AesCmac_GenerateSubkeys(AES_KEY_128 *aes_key, uint8_t K1[16], uint8_t K2[16]);

#endif
