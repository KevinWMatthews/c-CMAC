#include "CmacAes.h"
#include "CmacAesOps.h"
#include <string.h>

int CmacAes_Calculate(CMAC_AES_CALCULATE_PARAMS *params, uint8_t aes_cmac[16], size_t aes_cmac_len)
{
    CMAC_AES_CONTEXT context = {0};
    bool is_complete_block;
    int ret;


    uint8_t iv[16] = {0};       // CMAC uses an IV of zeros.
    AES128_CREATE_PARAMS create_params = {
        .key = params->key,
        .key_len = params->key_len,
        .iv = iv,
        .iv_len = sizeof(iv),
    };

    Aes128_Initialize();
    //TODO extract this into a CmacOps function.
    // We need to make it obvious that you must do this.
    // This function will accept only the key and the key length.
    // It will set the IV (note the comment on IV above - code smell).
    Aes128_Create(&create_params, &context.aes_handle);

    // Step 1
    ret = CmacAesOps_GenerateSubkeys2(&context);

    // Step 2
    ret = CmacAesOps_GetNBlocks2(params->message_len, &context);

    // Step 3
    is_complete_block = CmacAesOps_GetIsCompleteBlock(params->message_len);

    // Step 4
    // Given a message of n blocks, get the nth block.
    // For now we have a zero-length message, so it will be all padding.
    unsigned char M_n[16] = {0};
    unsigned char M_last[16] = {0};

    ret = CmacAesOps_GetNthBlock(params->message, params->message_len, &context);
    if (is_complete_block)
    {
        ret = CmacAesOps_SetLastBlockForComplete(context.nth_block, context.K1, M_last);
    }
    else
    {
        ret = CmacAesOps_SetLastBlockForIncomplete(context.nth_block, context.K2, M_last);
    }

    // Step 5
    unsigned char X[16] = {0};

    // Step 6
    unsigned char Y[16] = {0};
    ret = CmacAesOps_ApplyCbcMac(params->key, params->message, context.n_blocks, X, Y);
    ret = CmacAesOps_FinishCbcMac1(M_last, X, Y);


    unsigned char T[16] = {0};
    ret = CmacAesOps_FinishCbcMac2(context.aes_handle, Y, T, sizeof(T));

    Aes128_Destroy(&context.aes_handle);

    // Step 7
    memcpy(aes_cmac, T, 16);

    return 0;
}
