#ifndef AES128_INCLUDED
#define AES128_INCLUDED

#include <stddef.h>
#include <stdint.h>

#define AES128_KEY_LEN      16
#define AES128_IV_LEN       16
#define AES128_BLOCK_LEN    16

typedef struct AES128_STRUCT * AES128_HANDLE;

typedef enum
{
    AES128_SUCCESS                  =  0,
    AES128_FAILURE                  = -1,
    AES128_NULL_POINTER             = -2,
    AES128_INVALID_KEY_LENGTH       = -3,
    AES128_INVALID_IV_LENGTH        = -4,
    AES128_INVALID_INPUT_LENGTH     = -5,
    AES128_INVALID_OUTPUT_LENGTH    = -6,
} AES128_RETURN_CODE;


/*
 * Initialize the underlying crypto library before use
 */
AES128_RETURN_CODE Aes128_Initialize(void);


/*
 * Create an AES128 crypto handle.
 * Must specify a key and initialization vector.
 *
 * Only one handle may be created at a time!
 */
typedef struct AES128_CREATE_PARAMS
{
    size_t key_len;
    uint8_t *key;
    size_t iv_len;
    uint8_t *iv;
} AES128_CREATE_PARAMS;
AES128_RETURN_CODE Aes128_Create(AES128_CREATE_PARAMS *params, AES128_HANDLE *aes_handle);
AES128_RETURN_CODE Aes128_Create2(AES128_CREATE_PARAMS *params, AES128_HANDLE *aes_handle);
AES128_RETURN_CODE Aes128_Create3(AES128_CREATE_PARAMS *params, AES128_HANDLE *aes_handle);
AES128_RETURN_CODE Aes128_Create4(AES128_CREATE_PARAMS *params, AES128_HANDLE *aes_handle);
AES128_RETURN_CODE Aes128_Create5(AES128_CREATE_PARAMS *params, AES128_HANDLE *aes_handle);


/*
 * Destroy an AES128 crypto handle and set the pointer to NULL.
 */
void Aes128_Destroy(AES128_HANDLE *self);


/*
 * Encrypt the input text using the given AES128 handle (key and IV).
 * Puts the result in output.
 */
typedef struct AES128_CRYPTO_PARAMS
{
    AES128_HANDLE aes_handle;
    size_t input_len;
    uint8_t *input;
} AES128_CRYPTO_PARAMS;
AES128_RETURN_CODE Aes128_Encrypt(AES128_CRYPTO_PARAMS *params, uint8_t *output, size_t output_len);

#endif
