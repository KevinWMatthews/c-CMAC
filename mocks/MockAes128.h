#ifndef MOCKAES128_INCLUDED
#define MOCKAES128_INCLUDED

#include <stdint.h>
#include <stddef.h>
#include "Aes128.h"

// For testing we can treat the AES128_STRUCT as its creation parameters.
// If two structs are created with identical parameters, they will be functionally equivalent.
// Expose the struct details to make verification simple.
typedef struct AES128_STRUCT
{
    size_t key_len;
    uint8_t *key;
    size_t iv_len;
    uint8_t *iv;
} AES128_STRUCT;

// Populate and return a handle to a mock AES128_STRUCT.
AES128_HANDLE MockAes128_Create(AES128_CREATE_PARAMS *params);

// Free any resources used by a mock AES handle.
void MockAes128_Destroy(AES128_HANDLE self);

#endif
