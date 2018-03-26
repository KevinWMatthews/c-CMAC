#ifndef CMAC_AES_OPS_INCLUDED
#define CMAC_AES_OPS_INCLUDED

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "Aes128.h"

#define CMAC_AES_BLOCK_LENGTH       16

/*
 *TODO add documentation
 */
int CmacAesOps_GenerateSubkeys(AES128_HANDLE aes_handle,
        uint8_t K1[16], size_t K1_len,
        uint8_t K2[16], size_t K2_len);

/* Calculate the number of blocks in a message.
 *
 * Returns the number of 128-bit (16-byte) blocks in the given message.
 * If the block contains trailing bits, the block number is rounded up. For example,
 * 128 bits => 1 block
 * 129 bits => 2 blocks
 * If the message length is 0, the number of blocks is set to 1.
 */
size_t CmacAesOps_GetNBlocks(size_t message_length);

/* Calculate if the last block of a message is complete.
 *
 * If the message length is precisely divisible by 16, the block is complete. The is complete block flag is not set.
 * If the message contains trailing bits, the final block is incomplete. The is complete block flag is set.
 * For example
 * 127 bits => is_complete_block_flag = 0
 * 128 bits => is_complete_block_flag = 1
 * 129 bits => is_complete_block_flag = 0
 */
bool CmacAesOps_GetIsCompleteBlock(size_t message_length);

/* Get the nth block in the message
 *
 * For the given message M, get nth block where n is given by the (1-indexed!) block number.
 * Value is returned in M_n.
 */
int CmacAesOps_GetNthBlock(uint8_t *msg, size_t bytes_in_msg, uint8_t nth_block[16]);

/* Calculate the XOR of the last message block.
 *
 * Given the nth block of the message, calculate the XOR of last block.
 * This is used as a special input for the final step of the CMAC calculation.
 *
 * If the block is incomplete, XOR using K2.
 *TODO if the block is complete, XOR using K1.
 */
int CmacAesOps_SetLastBlockForIncomplete(uint8_t M_n[16], uint8_t K2[16], uint8_t M_last[16]);

int CmacAesOps_SetLastBlockForComplete(uint8_t M_n[16], uint8_t K1[16], uint8_t M_last[16]);

/* Apply the basic CMC-MAC algorithm to all but the last block of the message.
 *
 * XORs and AES-128 encrypts each block (according to the CBC-MAC spec?).
 * The AES-CMAC is still incomplete; the two finishing steps must be applied.
 */
int CmacAesOps_ApplyCbcMac(uint8_t aes_key[16], uint8_t *message, size_t n_blocks, uint8_t X[16], uint8_t Y[16]);

/* Apply first finishing step of the CBC-MAC.
 *
 * The last block is a special case: use M_last instead of M_n.
 */
int CmacAesOps_FinishCbcMac1(uint8_t M_last[16], uint8_t X[16], uint8_t Y[16]);

/* Apply second finishing step of the CBC-MAC.
 *
 * Perform final AES-128 encryption.
 * T is the CMC-MAC result.
 */
int CmacAesOps_FinishCbcMac2(AES128_HANDLE aes_handle, uint8_t Y[16], uint8_t T[16], size_t T_len);

#endif
