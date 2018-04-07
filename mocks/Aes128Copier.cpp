#include "Aes128Copier.h"
#include <string.h>

extern "C"
{
#include "MockAes128.h"
}

void Aes128Copier::copy(void* out, const void* in)
{
    AES128_STRUCT* aes128_out = (AES128_STRUCT *)out;
    const AES128_STRUCT* aes128_in = (const AES128_STRUCT *)in;

    aes128_out->key = aes128_in->key;
    aes128_out->key_len = aes128_in->key_len;
    aes128_out->iv = aes128_in->iv;
    aes128_out->iv_len = aes128_in->iv_len;
}
