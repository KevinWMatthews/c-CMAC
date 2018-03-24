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

// Populate and return a handle to a mock AES128_STRUCT.
AES128_HANDLE Mock_Aes128_Create(AES128_CREATE_PARAMS *params);

// Free any resources used by a mock AES handle.
void Mock_Aes128_Destroy(AES128_HANDLE self);

#endif
