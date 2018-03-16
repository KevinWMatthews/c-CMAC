#include <gcrypt.h>

int main(void)
{
    const char *actual_version = NULL;
    gcry_error_t gcry_ret;

    actual_version = gcry_check_version("1.8.2");

    printf("actual_version: %s\n", actual_version);

    gcry_ret = gcry_control(GCRYCTL_DISABLE_SECMEM, 0);
    printf("gcry_ret: %d\n", gcry_ret);

    return 0;
}
