#include <gcrypt.h>

int main(void)
{
    const char *actual_version = NULL;
    gcry_error_t ret;

    actual_version = gcry_check_version("1.8.2");

    printf("actual_version: %s\n", actual_version);

    ret = gcry_control(GCRYCTL_DISABLE_SECMEM, 0);
    // Uncomment this to see a failure
    // ret = gcry_control(GCRYCTL_INITIALIZATION_FINISHED, 0);
    printf("gcry_ret: %d\n", ret);
    ret = gcry_control(GCRYCTL_INITIALIZATION_FINISHED_P, 0);
    printf("gcry_ret: %d\n", ret);

    /*
     * gcry_err_code_t gcry_err_code (gcry_error_t err)
     */
    gcry_err_code_t err_code;
    err_code = gcry_err_code(ret);
    printf("error code: %d\n", err_code);

    /*
     * const char * gcry_strerror (gcry_error_t err)
     */
    const char *err_code_str;
    err_code_str = gcry_strerror(ret);
    printf("Error code: %s\n", err_code_str);

    /*
     * gcry_err_source_t gcry_err_source (gcry_error_t err)
     */
    gcry_err_source_t err_source;
    err_source = gcry_err_source(ret);
    printf("Error source: %d\n", err_source);

    /*
     * const char * gcry_strsource (gcry_error_t err)
     */
    const char *err_source_str;
    err_source_str = gcry_strsource(ret);
    printf("Error source: %s\n", err_source_str);

    return 0;
}
