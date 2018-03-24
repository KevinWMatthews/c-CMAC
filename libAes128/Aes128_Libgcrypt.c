#include "Aes128.h"
#include <gcrypt.h>
#include <string.h>

typedef struct AES128_STRUCT
{
    gcry_cipher_hd_t gcrypt_handle;
    size_t iv_len;
    uint8_t iv[AES128_BLOCK_LEN];
} AES128_STRUCT;

static AES128_STRUCT aes128;

#define LIBGCRYPT_REQURIED_VERSION      "1.8.2"

AES128_RETURN_CODE Aes128_Initialize(void)
{
    const char * actual_version = NULL;

    actual_version = gcry_check_version(LIBGCRYPT_REQURIED_VERSION);

    gcry_control(GCRYCTL_DISABLE_SECMEM, 0);
    gcry_control(GCRYCTL_INITIALIZATION_FINISHED, 0);

    return AES128_SUCCESS;
}

AES128_RETURN_CODE Aes128_Create(AES128_CREATE_PARAMS *params, AES128_HANDLE * aes_handle)
{
    gcry_error_t gcry_error;

    if (params == NULL)
        return AES128_NULL_POINTER;
    if (params->key == NULL)
        return AES128_NULL_POINTER;
    if (params->iv == NULL)
        return AES128_NULL_POINTER;
    if (aes_handle == NULL)
        return AES128_NULL_POINTER;

    if (params->key_len != AES128_KEY_LEN)
        return AES128_INVALID_KEY_LENGTH;
    if (params->iv_len != AES128_IV_LEN)
        return AES128_INVALID_IV_LENGTH;

    gcry_error = gcry_cipher_open(&aes128.gcrypt_handle, GCRY_CIPHER_AES128, GCRY_CIPHER_MODE_CBC, 0);
    if (gcry_error)
        return AES128_FAILURE;

    gcry_error = gcry_cipher_setkey(aes128.gcrypt_handle, params->key, params->key_len);
    if (gcry_error)
        return AES128_FAILURE;

    gcry_error = gcry_cipher_setiv(aes128.gcrypt_handle, params->iv, params->iv_len);
    if (gcry_error)
        return AES128_FAILURE;

    memcpy(aes128.iv, params->iv, params->iv_len);
    aes128.iv_len = params->iv_len;

    *aes_handle = &aes128;
    return AES128_SUCCESS;
}

void Aes128_Destroy(AES128_HANDLE * self)
{
    return;
}

AES128_RETURN_CODE Aes128_Encrypt(AES128_CRYPTO_PARAMS *params, uint8_t *output, size_t output_len)
{
    AES128_HANDLE aes_handle;
    gcry_error_t gcry_error;

    if (params == NULL)
        return AES128_NULL_POINTER;
    if (params->aes_handle == NULL)
        return AES128_NULL_POINTER;
    if (params->input == NULL)
        return AES128_NULL_POINTER;
    if (output == NULL)
        return AES128_NULL_POINTER;

    if (params->input_len != AES128_BLOCK_LEN)
        return AES128_INVALID_INPUT_LENGTH;
    if (output_len < params->input_len)
        return AES128_INVALID_OUTPUT_LENGTH;

    aes_handle = params->aes_handle;

    // This must be done before every crypto operation.
    gcry_error = gcry_cipher_setiv(aes_handle->gcrypt_handle, aes_handle->iv, aes_handle->iv_len);
    if (gcry_error)
        return AES128_FAILURE;

    gcry_error = gcry_cipher_encrypt(aes_handle->gcrypt_handle, output, output_len, params->input, params->input_len);
    if (gcry_error)
        return AES128_FAILURE;

    return AES128_SUCCESS;
}
