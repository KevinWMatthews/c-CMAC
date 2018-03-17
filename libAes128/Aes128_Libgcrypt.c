#include "Aes128.h"
#include <gcrypt.h>

typedef struct AES128_STRUCT
{
    gcry_cipher_hd_t gcrypt_handle;
} AES128_STRUCT;

static AES128_STRUCT aes128;

#define LIBGCRYPT_REQURIED_VERSION      "1.8.2"

AES128_RETURN_CODE Aes128_Initialize(void)
{
    const char * actual_version = NULL;

    /*
     * const char * gcry_check_version (const char *req_version)
     *
     * Initializes some subsystems used by Libgcrypt and must be invoked before any other function in the library.
     *
     * If the current version is higher than the require version,
     * returns the version number.
     * If the current version is too old, returns NULL.
     */
    actual_version = gcry_check_version(LIBGCRYPT_REQURIED_VERSION);

    /*
     * gcry_error_t gcry_control (enum gcry_ctl_cmds cmd, ...)
     *
     * Set general libgcrypt behavior.
     *
     * GCRYCTL_DISABLE_SECMEM
     *      Disables the use of secure memory
     */
    gcry_control(GCRYCTL_DISABLE_SECMEM, 0);

    /*
     * GCRYCTL_INITIALIZATION_FINISHED
     *      This command tells the library that the application has finished the initialization.
     */
    gcry_control(GCRYCTL_INITIALIZATION_FINISHED, 0);

    return AES128_SUCCESS;
}

AES128_RETURN_CODE Aes128_Create(AES128_CREATE_PARAMS *params, AES128 * aes_handle)
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

    if (params->key_len != 16)
        return AES128_INVALID_KEY;
    if (params->iv_len != 16)
        return AES128_INVALID_IV;

    /*
     * gcry_error_t gcry_cipher_open (gcry_cipher_hd_t *hd, int algo, int mode, unsigned int flags)
     *
     * Create the cipher context and returns a handle to it in ‘hd’.
     *
     * The available cipher algorithms, modes, and flags are listed in gcrypt.h. See:
     *      enum gcry_cipher_algos and the defines below it.
     *      enum gcry_cipher_modes
     *      gcry_cipher_flags, or can be set to 0
     *
     * Returns 0 on success and a non-zero error code on error.
     */
    gcry_error = gcry_cipher_open(&aes128.gcrypt_handle, GCRY_CIPHER_AES128, GCRY_CIPHER_MODE_CBC, 0);
    if (gcry_error)
        return AES128_FAILURE;

    /*
     * gcry_error_t gcry_cipher_setkey (gcry_cipher_hd_t h, const void *k, size_t l)
     *
     * Set the key k used for encryption or decryption in the context denoted by the handle h.
     * Can the key go out of scope?
     *
     * Returns 0 on success and a non-zero error code on error.
     */
    gcry_error = gcry_cipher_setkey(aes128.gcrypt_handle, params->key, params->key_len);
    if (gcry_error)
        return AES128_FAILURE;

    /*
     * gcry_error_t gcry_cipher_setiv (gcry_cipher_hd_t h, const void *k, size_t l)
     *
     * Set the initialization vector used for encryption or decryption.
     * The vector is passed as the buffer K of length l bytes and copied to internal data structures.
     *
     * Returns 0 on success and a non-zero error code on error.
     */
    gcry_error = gcry_cipher_setiv(aes128.gcrypt_handle, params->iv, params->iv_len);
    if (gcry_error)
        return AES128_FAILURE;

    *aes_handle = &aes128;
    return AES128_SUCCESS;
}

void Aes128_Destroy(AES128 * self)
{
    return;
}

AES128_RETURN_CODE Aes128_Encrypt2(AES128_CRYPTO_PARAMS *params, uint8_t *output, size_t output_len)
{
    gcry_error_t gcry_error;

    if (params == NULL)
        return AES128_NULL_POINTER;
    if (params->aes_handle == NULL)
        return AES128_NULL_POINTER;
    if (params->input == NULL)
        return AES128_NULL_POINTER;
    if (output == NULL)
        return AES128_NULL_POINTER;

    if (params->input_len != 16)
        return AES128_INVALID_INPUT;
    if (output_len < params->input_len)
        return AES128_INVALID_OUTPUT;

    /*
     * gcry_error_t gcry_cipher_encrypt (gcry_cipher_hd_t h, unsigned char *out, size_t outsize, const unsigned char *in, size_t inlen)
     *
     * Encrypt in.
     * Fill out with the result.
     *
     * Returns 0 on success or a non-zero error code on error.
     */
    gcry_error = gcry_cipher_encrypt(params->aes_handle->gcrypt_handle, output, output_len, params->input, params->input_len);
    if (gcry_error)
        return AES128_FAILURE;

    return AES128_SUCCESS;
}
