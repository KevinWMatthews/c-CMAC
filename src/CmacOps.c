#include "CmacOps.h"
#include "BitOperation.h"
#include "Aes.h"
#include <string.h>

static uint8_t const_Zero[16];

size_t set_n_blocks(size_t message_length)
{
    return 1;
}

int set_is_complete_block(size_t *n_blocks, bool *is_complete_block_flag)
{
    *n_blocks = 1;
    *is_complete_block_flag = false;

    return 0;
}

int get_nth_block(uint8_t M[16], size_t M_len, size_t block_num, uint8_t M_n[16])
{
    memset(M_n, 0, 16);
    if (block_num > 1)  // Only accomodates 0-length message
    {
        return -1;
    }
    return 0;
}

int set_last_block_for_incomplete(uint8_t M_n[16], uint8_t K2[16], uint8_t M_last[16])
{
    // Hack for padding - set first bit, the rest are 0's
    uint8_t padded_M_n[16] = {0x80};

    BitOperation_Xor(padded_M_n, K2, 16, M_last);
    return 0;
}

int apply_cbc_mac(uint8_t aes_key[16], uint8_t *message, size_t n_blocks, uint8_t X[16], uint8_t Y[16])
{
    return 0;
}

int finish_cbc_mac_1(uint8_t M_last[16], uint8_t X[16], uint8_t Y[16])
{
    BitOperation_Xor(M_last, X, 16, Y);
    return 0;
}

int finish_cbc_mac_2(uint8_t aes_key[16], uint8_t Y[16], uint8_t T[16])
{
    //TODO pass this as a parameter?
    AES_KEY_128 key = {
        .key = aes_key,
        .key_len = 16,
        .iv = const_Zero,
        .iv_len = sizeof(const_Zero)
    };
    Aes_Calculate128(&key, Y, 16, T, 16);

    return 0;
}
