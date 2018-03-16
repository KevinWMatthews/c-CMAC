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

    return AES128_SUCCESS;
}

AES128 Aes128_Create(AES128_KEY * key, AES128_IV * iv)
{
    return &aes128;
}
