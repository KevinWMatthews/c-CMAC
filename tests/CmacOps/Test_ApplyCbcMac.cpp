extern "C"
{
#include "CmacAesOps.h"
#include "Aes128.h"
#include "MockAes128.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include <string.h>

TEST_GROUP(ApplyCbcMac)
{
    CMAC_AES_CONTEXT context;
    size_t n_blocks;
    bool is_complete_block_flag;
    int ret;

    void setup()
    {
        mock().strictOrder();
    }

    void teardown()
    {
    }
};

static uint8_t zeros[16] = {};

TEST(ApplyCbcMac, apply_to_zero_length_message)
{
    uint8_t key[16] = {};
    uint8_t X[16] = {};
    uint8_t Y[16] = {};
    uint8_t expected_X[16] = {0};
    uint8_t expected_Y[16] = {0};

    // A zero-length message is treated as having n=1.
    // See RFC 4493, step 3.
    ret = CmacAesOps_ApplyCbcMac(key, NULL, 1, X, Y);

    LONGS_EQUAL( 0, ret );

    // Change nothing?
    MEMCMP_EQUAL( expected_X, X, sizeof(expected_X) );
    MEMCMP_EQUAL( expected_Y, Y, sizeof(expected_Y) );
}
