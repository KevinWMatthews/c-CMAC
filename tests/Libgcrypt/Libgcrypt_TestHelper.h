#ifndef LIBGCRYPT_TEST_HELPER
#define LIBGCRYPT_TEST_HELPER

// Check the actual return_value (gcry_error_t) against
// an expected error code (gpg_err_code_t).
//
// Extracts the error code from the return value and
// compares it to the expected error code.
//
// For a list of error codes, search gpg-error.h for the enum:
//  gpg_err_code_t
//
// gcry_err_code_t gcry_err_code (gcry_error_t err)
//  The static inline function gcry_err_code returns the gcry_err_code_t component of the error value err.
//  This function must be used to extract the error code from an error value in order to compare it with the GPG_ERR_* error code macros.
#define CHECK_LIBGCRYPT_RETURN_CODE(expected_error_code, actual_return_value)   \
    LONGS_EQUAL(expected_error_code, gcry_err_code(actual_return_value))

#endif
