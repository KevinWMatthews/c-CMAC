#ifndef BIT_OPERATION_INCLUDED
#define BIT_OPERATION_INCLUDED

#include <stdint.h>
#include <stddef.h>

int BitOperation_CircularShiftLeft(uint8_t bits_to_shift,
        uint8_t *input, size_t input_len,
        uint8_t *output, size_t output_len);

#endif
