#ifndef MOCK_AES128_INCLUDED
#define MOCK_AES128_INCLUDED

// For testing we can treat the AES128_STRUCT as its creation parameters.
// If two structs are created with identical parameters, they will be functionally equivalent.
typedef struct AES128_STRUCT
{
    size_t key_len;
    uint8_t *key;
    size_t iv_len;
    uint8_t *iv;
} AES128_STRUCT;

#endif
