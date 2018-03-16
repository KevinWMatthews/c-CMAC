extern "C"
{
#include <gcrypt.h>
}

#include "CppUTestExt/MockSupport.h"

const char * gcry_check_version (const char *req_version)
{
    return mock().actualCall("gcry_check_version")
        .withParameter("req_version", req_version)
        .returnStringValue();
    // Or this:
    // return mock().stringReturnValue();
}
