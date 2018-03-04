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
#define CONST_RB    0x87

int AesCmac_GenerateSubkeys(uint8_t aes_key[16], size_t aes_key_len,
        uint8_t K1[16], size_t K1_len,
        uint8_t K2[16], size_t K2_len)
{
    unsigned char L[16] = {0};
    AesCmac_CalculateLFromK( aes_key, aes_key_len, L, sizeof(L) );
    AesCmac_CalculateK1FromL( L, sizeof(L), K1, K1_len );
    AesCmac_CalculateK2FromK1( K1, 16, K2, K2_len );
    return 0;
}

int AesCmac_CalculateLFromK(uint8_t *K, size_t K_len, uint8_t *L, size_t L_len)
{
    AES_KEY_128 aes_key =  {
        .key = K,
        .key_len = K_len,
        .iv = const_Zero,
        .iv_len = sizeof(const_Zero),
    };
    Aes_Calculate128(&aes_key, const_Zero, sizeof(const_Zero), L, L_len);
    return 0;
}

int AesCmac_CalculateK1FromL(uint8_t *L, size_t L_len, uint8_t *K1, size_t K1_len)
{
    BitOperation_LogicalShiftLeftOne(L, L_len, K1, K1_len);
    if ( GET_MSBIT_8(L[0]) )
        K1[15] ^= CONST_RB;

    return 0;
}

int AesCmac_CalculateK2FromK1(uint8_t *K1, size_t K1_len, uint8_t *K2, size_t K2_len)
{
    BitOperation_LogicalShiftLeftOne(K1, K1_len, K2, K2_len);
    if ( GET_MSBIT_8(K1[0]) )
        K2[15] ^= CONST_RB;

    return 0;
}
