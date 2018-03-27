#include "CmacAesOps.h"
#include "BitOperation.h"
#include "CmacAesSubkeys.h"
#include <string.h>

static uint8_t const_Zero[16];

int CmacAesOps_GenerateSubkeys2(CMAC_AES_CONTEXT *context)
{
    uint8_t L[16] = {0};

    CmacAesSubkeys_CalculateLFromK( context->aes_handle, L, sizeof(L) );
    CmacAesSubkeys_CalculateK1FromL( L, sizeof(L), context->K1, sizeof(context->K1) );
    CmacAesSubkeys_CalculateK2FromK1( context->K1, sizeof(context->K1),
                                      context->K2, sizeof(context->K2) );

    return 0;
}

int CmacAesOps_GetNBlocks(size_t bytes_in_msg, CMAC_AES_CONTEXT *context)
{
    if (bytes_in_msg == 0)
    {
        context->n_blocks = 1;
    }
    else if (bytes_in_msg % CMAC_AES_BLOCK_LENGTH == 0)
    {
        context->n_blocks = bytes_in_msg / CMAC_AES_BLOCK_LENGTH;
    }
    else
    {
        context->n_blocks = (bytes_in_msg / CMAC_AES_BLOCK_LENGTH) + 1;
    }

    return 0;
}

bool CmacAesOps_GetIsCompleteBlock(size_t bytes_in_msg)
{
    if (bytes_in_msg == 0)
        return false;

    return (bytes_in_msg % CMAC_AES_BLOCK_LENGTH) == 0;
}

int CmacAesOps_GetNthBlock(uint8_t *msg, size_t bytes_in_msg, CMAC_AES_CONTEXT *context)
{
    size_t offset;

    memset( context->nth_block, 0, sizeof(context->nth_block) );

    if (msg == NULL)        // Zero-length message - is a valid case
    {
        return 0;
    }

    offset = CMAC_AES_BLOCK_LENGTH * (context->n_blocks - 1);
    memcpy(context->nth_block, msg + offset, bytes_in_msg - offset);

    return 0;
}

int CmacAesOps_SetLastBlockForIncomplete(uint8_t M_n[16], uint8_t K2[16], uint8_t M_last[16])
{
    // Hack for padding - set first bit, the rest are 0's
    uint8_t padded_M_n[16] = {0x80};

    BitOperation_Xor(padded_M_n, K2, 16, M_last);
    return 0;
}

int CmacAesOps_SetLastBlockForComplete(uint8_t M_n[16], uint8_t K1[16], uint8_t M_last[16])
{
    BitOperation_Xor(M_n, K1, 16, M_last);
    return 0;
}

int CmacAesOps_ApplyCbcMac(uint8_t aes_key[16], uint8_t *message, size_t n_blocks, uint8_t X[16], uint8_t Y[16])
{
    return 0;
}

int CmacAesOps_FinishCbcMac1(uint8_t M_last[16], uint8_t X[16], uint8_t Y[16])
{
    BitOperation_Xor(M_last, X, 16, Y);
    return 0;
}

int CmacAesOps_FinishCbcMac2(AES128_HANDLE aes_handle, uint8_t Y[16], uint8_t T[16], size_t T_len)
{
    AES128_CRYPTO_PARAMS params = {
        .aes_handle = aes_handle,
        .input = Y,
        .input_len = 16,        // ?
    };

    return Aes128_Encrypt(&params, T, 16); //?
}
