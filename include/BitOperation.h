#ifndef BIT_OPERATION_INCLUDED
#define BIT_OPERATION_INCLUDED

#include <stdint.h>
#include <stddef.h>

/*
 * Perform bitwise operations on byte arrays.
 */

/*
 * Get the most significant bit of an 8-bit integer.
 * Right-shift all but the top bit into oblivion.
 */
#define GET_MSBIT_8(byte)       ((byte) >> (8-1))


/*
 * Bit shift the contents of the array one to the left.
 * No bits are lost - the most significant bit of the array wraps around
 * and replaces the gap left by the least significant bit.
 *
 * Bits carry between bytes and wrap around:
 *        ---      --..--
 *        | ^      |    ^
 *        V |      V    |
 * 00000000 00000000 .. 00000000
 * |                           ^
 * V                           |
 * -----------------------------
 */
int BitOperation_CircularShiftLeftOne(uint8_t *input, size_t input_len, uint8_t *output, size_t output_len);


/*
 * Bit shift the contents of the array one to the left.
 * Bits are lost - the most significant bit of the array is shifted into oblivion.
 * The least significant bit is replaced by a 0.
 *
 * Bits carry between bytes but not wrap around:
 *        ---      --..--
 *        | ^      |    ^
 *        V |      V    |
 * 00000000 00000000 .. 00000000
 */
int BitOperation_LogicalShiftLeftOne(uint8_t *input, size_t input_len, uint8_t *output, size_t output_len);

int BitOperation_Xor(uint8_t *input1, uint8_t *input2, size_t len, uint8_t *output);

#endif
