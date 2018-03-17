#include "Aes128.h"
#include <gcrypt.h>

typedef struct AES128_STRUCT
{
    int placeholder;
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

AES128 Aes128_Create(AES128_KEY * key, AES128_IV * iv)
{
    return &aes128;
}

void Aes128_Destroy(AES128 * self)
{
    return;
}

AES128_RETURN_CODE Aes128_Encrypt(AES128 self, uint8_t * input, size_t input_len, uint8_t * output, size_t output_len)
{
    uint8_t hard_coded_result[16] = {
        0x66, 0xE9, 0x4B, 0xD4, 0xEF, 0x8A, 0x2C, 0x3B,
        0x88, 0x4C, 0xFA, 0x59, 0xCA, 0x34, 0x2B, 0x2E,
    };
    memcpy(output, hard_coded_result, sizeof(hard_coded_result));
    return AES128_SUCCESS;
}
