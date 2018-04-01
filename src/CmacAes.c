#include "CmacAes.h"
#include "CmacAesOps.h"
#include <string.h>

int CmacAes_Calculate(CMAC_AES_CALCULATE_PARAMS *params, uint8_t aes_cmac[16], size_t aes_cmac_len)
{
    CMAC_AES_CONTEXT context = {0};

    // Setup
    CmacAesOps_Initialize(&context, params->key, params->key_len);

    // Step 1
    CmacAesOps_GenerateSubkeys(&context);

    // Step 2
    CmacAesOps_GetNBlocks(params->message_len, &context);

    // Step 3
    CmacAesOps_GetIsCompleteBlock(params->message_len, &context);

    // Step 4
    CmacAesOps_GetNthBlock(params->message, params->message_len, &context);
    CmacAesOps_SetLastBlockFromNthBlock(&context);

    // Step 5
    CmacAesOps_InitializeCipherOutputBlock(&context);

    // Step 6
    //TODO Pull all of this into a function?
    CmacAesOps_ApplyCbcXor(&context);
    CmacAesOps_ApplyCbcAes(&context);

    // Step 7
    CmacAesOps_CopyCmacOutput(&context, aes_cmac, aes_cmac_len);

    // Teardown
    CmacAesOps_Unitialize(&context);

    return 0;
}
