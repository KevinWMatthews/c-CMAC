#include "BitOperation.h"

/*
 * Left shift one bit.
 * The most significant bit is lost and the least significant bit is replaced by a zero.
 */
#define LEFT_SHIFT_ONE(byte)    ((byte) << 1)

/*
 * Get the most significant bit of an 8-bit integer.
 * Right-shift all but the top bit into oblivion.
 */
#define GET_MSBIT_8(byte)       ((byte) >> (8-1))

// Assume for now that a uint8_t is exactly 8 bits wide.
// Streamline this function to work only on 8-bit unsigned integers.
int BitOperation_CircularShiftLeftOne(uint8_t *input, size_t input_len, uint8_t *output, size_t output_len)
{
    if (input_len == 1)
    {
        // LSH(this) | MSB(first)
        output[0] = LEFT_SHIFT_ONE(input[0]) | GET_MSBIT_8(input[0]);
    }
    else if (input_len == 2)
    {
        // LSH(this) | MSB(first)
        output[1] = LEFT_SHIFT_ONE(input[1]) | GET_MSBIT_8(input[0]);
        // LSH(this) | MSB(next)
        output[0] = LEFT_SHIFT_ONE(input[0]) | GET_MSBIT_8(input[1]);
    }
    else if (input_len == 3)
    {
        // LSB(this) | MSB(first)
        output[2] = LEFT_SHIFT_ONE(input[2]) | GET_MSBIT_8(input[0]);
        // LSH(this) | MSB(next)
        output[1] = LEFT_SHIFT_ONE(input[1]) | GET_MSBIT_8(input[2]);
        // LSH(this) | MSB(next)
        output[0] = LEFT_SHIFT_ONE(input[0]) | GET_MSBIT_8(input[1]);
    }

    return 0;
}
