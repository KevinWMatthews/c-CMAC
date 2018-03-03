#include "BitOperation.h"

// Assume for now that a uint8_t is exactly 8 bits wide.
// Streamline this function to work only on 8-bit unsigned integers.
int BitOperation_CircularShiftLeftOne(uint8_t *input, size_t input_len, uint8_t *output, size_t output_len)
{
    if (input_len == 1)
    {
        output[0] = input[0] << 1;
        output[0] |= (input[0] & 0x80) && 1;
    }
    else if (input_len == 2)
    {
        output[1] = input[1] << 1;
        output[0] = input[0] << 1;

        output[1] |= (input[0] & 0x80) && 1;
        output[0] |= (input[1] & 0x80) && 1;
    }
    else if (input_len == 3)
    {
        output[2] = input[2] << 1;
        output[1] = input[1] << 1;
        output[0] = input[0] << 1;

        output[2] |= (input[0] & 0x80) && 1;
        output[1] |= (input[2] & 0x80) && 1;
        output[0] |= (input[1] & 0x80) && 1;
    }

    return 0;
}
