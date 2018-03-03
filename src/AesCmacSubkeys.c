#include "AesCmacSubkeys.h"
#include "Aes.h"
#include <string.h>
#include "BitOperation.h"

// See RFC4493, Fig 2.2
static uint8_t const_Zero[16] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

// See RFC4493, Fig 2.2
static uint8_t const_Rb[16] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87,
};

/*
 * Shift the bits in an array to the left by one.
 * Bytes in the array are assumed to be stored with
 * the least significant byte first?
 *
 * So:
 *  0xffee..1100
 *    ||      -- LSB
 *    -- MSB
 * is stored as:
 *  00 11 .. ee ff
 *
 * Bitshifting:
 *  0x00        0x11        0xX     0xee        0xff
 *  0b0000 0000 0b0001 0001 0bX .. 0b1110 1110 0b1111 1111
 * yields:
 *  0x00        0x22               0xdd        0xfe
 *  0b0000 0000 0b0010 001X .. 0b1 0b1101 1101 0b1111 1110
 *                                                       - This bit wraps around.
 */
//TODO test this...
static void bitshift_left_one(uint8_t *input, size_t input_len,
                              uint8_t *output, size_t output_len)
{
}

int AesCmac_GenerateSubkeys(AES_KEY_128 *aes_key, uint8_t K1[16], uint8_t K2[16])
{
    uint8_t K1_calc[] = {
        0xfb, 0xee, 0xd6, 0x18, 0x35, 0x71, 0x33, 0x66,
        0x7c, 0x85, 0xe0, 0x8f, 0x72, 0x36, 0xa8, 0xde,
    };
    uint8_t K2_calc[] = {
        0xf7, 0xdd, 0xac, 0x30, 0x6a, 0xe2, 0x66, 0xcc,
        0xf9, 0x0b, 0xc1, 0x1e, 0xe4, 0x6d, 0x51, 0x3b,
    };
    int ret;
    unsigned char L[16] = {};

    ret = Aes_Calculate128( aes_key, const_Zero, sizeof(const_Zero), L, sizeof(L) );

    memcpy(K1, K1_calc, 16);
    memcpy(K2, K2_calc, 16);

    return 0;
}

int AesCmac_CalculateK1FromL(uint8_t *L, size_t L_len, uint8_t *K1, size_t K1_len)
{
    BitOperation_LogicalShiftLeftOne(L, L_len, K1, K1_len);
    return 0;
}
