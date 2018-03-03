#include "BitOperation.h"

int BitOperation_CircularShiftLeft(uint8_t bits_to_shift,
        uint8_t *input, size_t input_len,
        uint8_t *output, size_t output_len)
{
    if (input_len == 1)
    {
        output[0] = input[0] << bits_to_shift;
        output[0] |= (input[0] & 0x80) && 1;
    }
    else if (input_len == 2)
    {
        output[1] = input[1] << bits_to_shift;
        output[0] = input[0] << bits_to_shift;

        output[0] |= (input[1] & 0x80) && 1;
        output[1] |= (input[0] & 0x80) && 1;
    }
    else if (input_len == 3)
    {
        output[2] = input[2] << bits_to_shift;
        output[1] = input[1] << bits_to_shift;
        output[0] = input[0] << bits_to_shift;
    }

    return 0;
}
