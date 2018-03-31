#include "CmacAesOps.h"
#include "BitOperation.h"
#include "CmacAesSubkeys.h"
#include <string.h>

static uint8_t const_Zero[16];

int CmacAesOps_GenerateSubkeys(CMAC_AES_CONTEXT *context)
{
    uint8_t L[16] = {0};

    CmacAesSubkeys_CalculateLFromK( context->aes_handle, L, sizeof(L) );
    CmacAesSubkeys_CalculateK1FromL( L, sizeof(L), context->key1, sizeof(context->key1) );
    CmacAesSubkeys_CalculateK2FromK1( context->key1, sizeof(context->key1),
                                      context->key2, sizeof(context->key2) );

    return 0;
}

int CmacAesOps_GetNBlocks(size_t bytes_in_msg, CMAC_AES_CONTEXT *context)
{
    if (bytes_in_msg == 0)
    {
        context->n_blocks = 1;
    }
    else if (bytes_in_msg % CMAC_AES_BYTES_IN_BLOCK == 0)
    {
        context->n_blocks = bytes_in_msg / CMAC_AES_BYTES_IN_BLOCK;
    }
    else
    {
        context->n_blocks = (bytes_in_msg / CMAC_AES_BYTES_IN_BLOCK) + 1;
    }

    return 0;
}

int CmacAesOps_GetIsCompleteBlock(size_t bytes_in_msg, CMAC_AES_CONTEXT *context)
{
    if (bytes_in_msg == 0)
    {
        context->is_nth_block_complete = false;
    }
    else
    {
        bool remainder = bytes_in_msg % CMAC_AES_BYTES_IN_BLOCK;
        context->is_nth_block_complete = (remainder == 0);
    }
    return 0;
}

int CmacAesOps_GetNthBlock(uint8_t *msg, size_t bytes_in_msg, CMAC_AES_CONTEXT *context)
{
    size_t offset;

    memset( context->nth_block, 0, sizeof(context->nth_block) );

    if (msg == NULL)        // Zero-length message - is a valid case
    {
        return 0;
    }

    offset = CMAC_AES_BYTES_IN_BLOCK * (context->n_blocks - 1);
    memcpy(context->nth_block, msg + offset, bytes_in_msg - offset);
    context->nth_block_len = bytes_in_msg - offset;

    return 0;
}

int CmacAesOps_SetLastBlockFromNthBlock(CMAC_AES_CONTEXT *context)
{
    if (context->is_nth_block_complete)
    {
        BitOperation_Xor(context->nth_block,
                context->key1, sizeof(context->key1),
                context->last_block);
    }
    else
    {
        size_t num_trailing_bytes = context->nth_block_len;

        memcpy(context->last_block, context->nth_block, num_trailing_bytes);
        context->last_block[num_trailing_bytes] = 0x80;      // Padding
        BitOperation_Xor(context->last_block,
                context->key2, sizeof(context->key2),
                context->last_block);
    }
    return 0;
}

int CmacAesOps_ApplyCbcMac(uint8_t aes_key[16], uint8_t *message, size_t n_blocks, uint8_t X[16], uint8_t Y[16])
{
    return 0;
}

int CmacAesOps_InitializeCipherOutputBlock(CMAC_AES_CONTEXT *context)
{
    memset(context->cipher_output_block, 0x00, sizeof(context->cipher_output_block) );
    return 0;
}

int CmacAesOps_ApplyCbcXor(CMAC_AES_CONTEXT *context)
{
    // previous cipher block ^ i-th block.
    // i-th block is last block for final block (not nth block).
    BitOperation_Xor(context->cipher_output_block, context->last_block, 16,
            context->cipher_input_block);
    return 0;
}

int CmacAesOps_ApplyCbcAes(CMAC_AES_CONTEXT *context)
{
    AES128_CRYPTO_PARAMS params = {};

    params.aes_handle = context->aes_handle;
    params.input = context->cipher_input_block;
    params.input_len = sizeof(context->cipher_input_block);

    Aes128_Encrypt( &params, context->cipher_output_block, sizeof(context->cipher_output_block) );
    return 0;
}
