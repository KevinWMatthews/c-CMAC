#ifndef AES_CMAC_INCLUDED
#define AES_CMAC_INCLUDED

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

int AesCmac_Calculate128(uint8_t key[16], size_t key_len,
        uint8_t *message, size_t message_len,
        uint8_t *aes_cmac, size_t aes_cmac_len);

// Expose operations of steps for testing.
// Will move to a different module?

size_t get_n_blocks(size_t message_length);

int get_is_complete_block(size_t *n_blocks, bool *is_complete_block_flag);

// Get the nth block from message M and put it in M_n.
// For a zero-lenght message, clears M_n.
int get_nth_block(uint8_t M[16], size_t M_len, size_t block_num, uint8_t M_n[16]);

int set_last_block_for_incomplete(uint8_t M_n[16], uint8_t K2[16], uint8_t M_last[16]);

// I think we want n_blocks instead of message_len; we've already taken care of the last block.
int apply_cbc_mac(uint8_t aes_key[16], uint8_t *message, size_t n_blocks, uint8_t X[16], uint8_t Y[16]);

int finish_cbc_mac_1(uint8_t M_last[16], uint8_t X[16], uint8_t Y[16]);

int finish_cbc_mac_2(uint8_t aes_key[16], uint8_t Y[16], uint8_t T[16]);


#endif
