#include "AesCmacSubkeys.h"
#include <string.h>
#include "BitOperation.h"

// See RFC4493, Fig 2.2
static uint8_t const_Zero[16] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

// See RFC4493, Fig 2.2
#define CONST_RB    0x87

int AesCmac_GenerateSubkeys(AES128_HANDLE aes_handle,
        uint8_t K1[16], size_t K1_len,
        uint8_t K2[16], size_t K2_len)
{
    unsigned char L[16] = {0};
    AesCmac_CalculateLFromK( aes_handle, L, sizeof(L) );
    AesCmac_CalculateK1FromL( L, sizeof(L), K1, K1_len );
    AesCmac_CalculateK2FromK1( K1, 16, K2, K2_len );
    return 0;
}

int AesCmac_CalculateLFromK(AES128_HANDLE aes_handle, uint8_t *L, size_t L_len)
{
    AES128_CRYPTO_PARAMS params = {};
    if (aes_handle == NULL)
        return -1;

    params.aes_handle = aes_handle;
    params.input = const_Zero;
    // params.input[0] = 1;
    params.input_len = sizeof(const_Zero);

    Aes128_Encrypt(&params, L, L_len);
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
