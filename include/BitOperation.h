#ifndef BIT_OPERATION_INCLUDED
#define BIT_OPERATION_INCLUDED

#include <stdint.h>
#include <stddef.h>

int BitOperation_CircularShiftLeftOne(uint8_t *input, size_t input_len, uint8_t *output, size_t output_len);
int BitOperation_LogicalShiftLeftOne(uint8_t *input, size_t input_len, uint8_t *output, size_t output_len);

#endif
