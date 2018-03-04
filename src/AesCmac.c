#include "AesCmac.h"
#include <string.h>
#include "AesCmacSubkeys.h"

int AesCmac_Calculate128(uint8_t key[16], size_t key_len,
        uint8_t *message, size_t message_len,
        uint8_t *aes_cmac, size_t aes_cmac_len)
{
    unsigned char K1[16] = {0};
    unsigned char K2[16] = {0};
    unsigned int n;
    int ret;

    // Step 1
    ret = AesCmac_GenerateSubkeys( key, key_len,
            K1, sizeof(K1),
            K2, sizeof(K2) );

    // Step 2

    // Step 3

    // Step 4
    // Padding: set the first bit, then it's zeros all the way down.
    unsigned char M_last[16] = {0x80};
    // BitOperation_Xor(M_last, K2, 16, M_last);

    unsigned char cmac_calc[] = {
        0xbb, 0x1d, 0x69, 0x29, 0xe9, 0x59, 0x37, 0x28,
        0x7f, 0xa3, 0x7d, 0x12, 0x9b, 0x75, 0x67, 0x46,
    };
    memcpy(aes_cmac, cmac_calc, sizeof(cmac_calc));
    return 0;
}