#include "BitOperation.h"

int BitOperation_CircularShiftLeft(uint8_t bits_to_shift,
        uint8_t *input, size_t input_len,
        uint8_t *output, size_t output_len)
{
    output[0] = input[0] << bits_to_shift;
    return 0;
}
