#ifndef CMAC_OPS_INCLUDED
#define CMAC_OPS_INCLUDED

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

size_t calculate_n_blocks(size_t message_length);
int set_is_complete_block(size_t *n_blocks, bool *is_complete_block_flag);
int get_nth_block(uint8_t M[16], size_t M_len, size_t block_num, uint8_t M_n[16]);
int set_last_block_for_incomplete(uint8_t M_n[16], uint8_t K2[16], uint8_t M_last[16]);
int apply_cbc_mac(uint8_t aes_key[16], uint8_t *message, size_t n_blocks, uint8_t X[16], uint8_t Y[16]);
int finish_cbc_mac_1(uint8_t M_last[16], uint8_t X[16], uint8_t Y[16]);
int finish_cbc_mac_2(uint8_t aes_key[16], uint8_t Y[16], uint8_t T[16]);

#endif
