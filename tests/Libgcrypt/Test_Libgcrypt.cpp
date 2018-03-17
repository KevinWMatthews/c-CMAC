extern "C"
{
#include <gcrypt.h>
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(Libgcrypt)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(Libgcrypt, wiring_check)
{
    FAIL("start here");
}
