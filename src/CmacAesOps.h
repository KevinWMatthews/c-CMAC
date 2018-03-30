#ifndef CMAC_AES_OPS_INCLUDED
#define CMAC_AES_OPS_INCLUDED

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "Aes128.h"

#define CMAC_AES_BYTES_IN_BLOCK         16

typedef struct CMAC_AES_CONTEXT
{
    AES128_HANDLE aes_handle;
    uint8_t key1[16];           // K1
    uint8_t key2[16];           // K2
    size_t n_blocks;
    bool is_nth_block_complete;
    uint8_t nth_block[16];      // M_n
    size_t nth_block_len;       // Bytes in actually written; not buffer length
    uint8_t last_block[16];     // M_last
    uint8_t current_cipher_block[16];   // X
    uint8_t cipher_input_block[16];     // Y
} CMAC_AES_CONTEXT;

/*
 * Calculates subkeys and stores them in the context.
 */
int CmacAesOps_GenerateSubkeys(CMAC_AES_CONTEXT *context);

/* Calculate the number of blocks in a message.
 *
 * Stores the number of 128-bit (16-byte) blocks in the given message in the context.
 *
 * If the block contains trailing bits, the block number is rounded up. For example,
 * 128 bits => 1 block
 * 129 bits => 2 blocks
 * If the message length is 0, the number of blocks is set to 1.
 */
int CmacAesOps_GetNBlocks(size_t bytes_in_msg, CMAC_AES_CONTEXT *context);

/* Calculate if the last block of a message is complete.
 *
 * If the message length is precisely divisible by 16, the block is complete. The is complete block flag is not set.
 * If the message contains trailing bits, the final block is incomplete. The is complete block flag is set.
 * For example
 * 127 bits => is_complete_block_flag = 0
 * 128 bits => is_complete_block_flag = 1
 * 129 bits => is_complete_block_flag = 0
 */
int CmacAesOps_GetIsCompleteBlock(size_t bytes_in_msg, CMAC_AES_CONTEXT *context);

/* Get the nth block in the message
 *
 * For the given message M, get nth block where n is given by the (1-indexed!) block number.
 * Stores the nth block and its length in the context.
 */
int CmacAesOps_GetNthBlock(uint8_t *msg, size_t bytes_in_msg, CMAC_AES_CONTEXT *context);

/* Calculate the "last block" (M_last) from the Nth block (M_n) and store this in the context.
 *
 * The last block is used as a special input for the final step of the CMAC calculation.
 * It is derived from the Nth block by padding (if necessary) and XOR with one of teh subkeys.
 */
int CmacAesOps_SetLastBlockFromNthBlock(CMAC_AES_CONTEXT *context);

int CmacAesOps_SetLastBlockForIncomplete(uint8_t M_n[16], uint8_t K2[16], uint8_t M_last[16]);

int CmacAesOps_SetLastBlockForComplete(uint8_t M_n[16], uint8_t K1[16], uint8_t M_last[16]);

/* Apply the basic CMC-MAC algorithm to all but the last block of the message.
 *
 * XORs and AES-128 encrypts each block (according to the CBC-MAC spec?).
 * The AES-CMAC is still incomplete; the two finishing steps must be applied.
 */
int CmacAesOps_ApplyCbcMac(uint8_t aes_key[16], uint8_t *message, size_t n_blocks, uint8_t X[16], uint8_t Y[16]);

/*TODO document properly
 * XOR to i-th block of message with the previous cipher block.
 *
 * The last block is a special case: use M_last instead of M_n.
 */
int CmacAesOps_ApplyCbcXor(CMAC_AES_CONTEXT *context);

/*TODO document properly
 * Apply AES to CBC input.
 */
int CmacAesOps_ApplyCbcAes(CMAC_AES_CONTEXT *context);

#endif
