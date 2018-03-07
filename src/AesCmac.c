#include "AesCmac.h"
#include <string.h>
#include "AesCmacSubkeys.h"
#include "CmacOps.h"

int AesCmac_Calculate128(uint8_t key[16], size_t key_len,
        uint8_t *message, size_t message_len,
        uint8_t *aes_cmac, size_t aes_cmac_len)
{
    unsigned char K1[16] = {0};
    unsigned char K2[16] = {0};
    size_t n;
    bool is_complete_block;
    int ret;

    // Step 1
    ret = AesCmac_GenerateSubkeys( key, key_len,
            K1, sizeof(K1),
            K2, sizeof(K2) );

    // Step 2
    n = CmacOps_GetNBlocks(message_len);

    // Step 3
    is_complete_block = CmacOps_GetIsCompleteBlock(message_len);

    // Step 4
    // Given a message of n blocks, get the nth block.
    // For now we have a zero-length message, so it will be all padding.
    unsigned char M_n[16] = {0};        // This will need to be a function...
    unsigned char M_last[16] = {0};

    ret = CmacOps_GetNthBlock(message, message_len, n, M_n);
    ret = CmacOps_SetLastBlockForIncomplete(M_n, K2, M_last);

    // Step 5
    unsigned char X[16] = {0};

    // Step 6
    unsigned char Y[16] = {0};
    ret = CmacOps_ApplyCbcMac(key, message, n, X, Y);
    ret = CmacOps_FinishCbcMac1(M_last, X, Y);
    unsigned char T[16] = {0};
    ret = CmacOps_FinishCbcMac2(key, Y, T);

    memcpy(aes_cmac, T, 16);
    return 0;
}
