#ifndef MOCK_AES128_INCLUDED
#define MOCK_AES128_INCLUDED

typedef struct AES128_STRUCT
{
    size_t key_len;
    uint8_t *key;
    size_t iv_len;
    uint8_t *iv;
} AES128_STRUCT;

#endif
