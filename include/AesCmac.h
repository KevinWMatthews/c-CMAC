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

size_t calculate_n_blocks(size_t message_length);

int set_is_complete_block(size_t *n_blocks, bool *is_complete_block_flag);

int set_last_block_for_incomplete(uint8_t M_n[16], uint8_t K2[16], uint8_t M_last[16]);

int apply_cbc_mac(uint8_t *message, size_t message_len, uint8_t aes_key[16], uint8_t t[16]);

#endif
