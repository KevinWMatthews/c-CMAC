#ifndef AES_CMAC_SUBKEYS_INCLUDED
#define AES_CMAC_SUBKEYS_INCLUDED

#include <stdint.h>

int AesCmac_GenerateSubkeys(uint8_t key[16], uint8_t K1[16], uint8_t K2[16]);

#endif
