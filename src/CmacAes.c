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

    //TODO extract this into a CmacOps function.
    // We need to make it obvious that you must do this.
    // This function will accept only the key and the key length.
    // It will set the IV (note the comment on IV above - code smell).
    Aes128_Initialize();
    Aes128_Create(&create_params, &context.aes_handle);

    // Step 1
    ret = CmacAesOps_GenerateSubkeys(&context);

    // Step 2
    ret = CmacAesOps_GetNBlocks(params->message_len, &context);

    // Step 3
    ret = CmacAesOps_GetIsCompleteBlock(params->message_len, &context);

    // Step 4
    ret = CmacAesOps_GetNthBlock(params->message, params->message_len, &context);
    ret = CmacAesOps_SetLastBlockFromNthBlock(&context);

    // Step 5
    ret = CmacAesOps_InitializeCipherOutputBlock(&context);

    // Step 6
    //TODO Pull all of this into a function?
    ret = CmacAesOps_ApplyCbcXor(&context);
    ret = CmacAesOps_ApplyCbcAes(&context);

    // Step 7
    memcpy(aes_cmac, context.cipher_output_block, 16);

    //TODO Extract this into a CmacOps function?
    Aes128_Destroy(&context.aes_handle);

    return 0;
}
