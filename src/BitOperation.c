#include "BitOperation.h"

/*
 * Left shift one bit.
 * The most significant bit is lost and the least significant bit is replaced by a zero.
 */
#define LEFT_SHIFT_ONE(byte)    ((byte) << 1)

int BitOperation_LogicalShiftLeftOne(uint8_t *input, size_t input_len, uint8_t *output, size_t output_len)
{
    int i;

    // Start at the end of the array
    i = input_len - 1;

    // Last byte is special - no wrap around
    output[i] = LEFT_SHIFT_ONE(input[i]);

    // Work backwards through the array
    while (i > 0)
    {
        --i;
        // left_shift(this) | MSB(next)
        output[i] = LEFT_SHIFT_ONE(input[i]) | GET_MSBIT_8(input[i+1]);
    }

    return 0;
}

/*
 * Assume for now that a uint8_t is exactly 8 bits wide.
 * Streamline this function to work only on 8-bit unsigned integers.
 */
int BitOperation_CircularShiftLeftOne(uint8_t *input, size_t input_len, uint8_t *output, size_t output_len)
{
    int i;

    // Start at the end of the array
    i = input_len - 1;

    // Last byte is special - bit wraps around from the front of the array
    output[i] = LEFT_SHIFT_ONE(input[i]) | GET_MSBIT_8(input[0]);

    // Work backwards through the array
    while (i > 0)
    {
        --i;
        // left_shift(this) | MSB(next)
        output[i] = LEFT_SHIFT_ONE(input[i]) | GET_MSBIT_8(input[i+1]);
    }

    return 0;
}

int BitOperation_Xor(uint8_t *input1, uint8_t *input2, size_t len, uint8_t *output)
{
    if (len == 1)
    {
        output[0] = input1[0] ^  input2[0];
    }
    if (len == 2)
    {
        output[0] = input1[0] ^  input2[0];
        output[1] = input1[1] ^  input2[1];
    }
    return 0;
}
