#include <gcrypt.h>

int main(void)
{
    const char *actual_version = NULL;

    actual_version = gcry_check_version("1.8.2");

    printf("actual_version: %s\n", actual_version);

    gcry_control(GCRYCTL_DISABLE_SECMEM, 0);

    return 0;
}
