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

/*
 * Assume for now that a uint8_t is exactly 8 bits wide.
 * Streamline this function to work only on 8-bit unsigned integers.
 */
int BitOperation_CircularShiftLeftOne(uint8_t *input, size_t input_len, uint8_t *output, size_t output_len)
{
    int i;

    /*
     * Bits wrap around between bytes:
     * -------------------------------
     * |                             |
     * ^                             V
     * 00000000 00000000 .. 0000000000
     *        | |      |    |
     *        ^ V      ^    V
     *        ---      --..--
     */
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
