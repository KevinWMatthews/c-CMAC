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
    //TODO rename to prepare Nth block
    // Later could fold into SetLastBlock if it knows how to fill the array with 00's
    CmacAesOps_GetNthBlock(params->message, params->message_len, &context);
    CmacAesOps_SetLastBlockFromNthBlock(&context);

    // Step 5
    //TODO Rename this: initialize xor input block
    // Set previous_block to 0's
    CmacAesOps_InitializeCipherOutputBlock(&context);

    // Step 6
    //TODO Pull all of this into a function?
    // for i = 0 to n-1,
    //   get block by number
    //   apply cbc xor
    //   apply cbc aes
    //   loop
    // for i = n,
    //   get last block (not nth block)
    //   apply cbc xor
    //   apply cbc aes

    // while (CmacAesOps_IsBlockRemaining(&context))        // Get this from the context.
    {
        // Fill message input block with block number
        // CmacAesOps_GetBlockByNumber(&context);   // Pass in block number?
        // This has a special condition (internally) - if the block number to get == n_blocks,
        // get the pre-calculated last_block instead of the nth block of the message.
        // This is rather magical, though; maybe keep the last step separate.
    }

    // Now do the last block
    //TODO rename this to be specific to the last block
    CmacAesOps_ApplyCbcXor(&context);   // This operates on the specially-formatted last block
    CmacAesOps_ApplyCbcAes(&context);

    // Step 7
    CmacAesOps_CopyCmacOutput(&context, aes_cmac, aes_cmac_len);

    // Teardown
    CmacAesOps_Unitialize(&context);

    return 0;
}
