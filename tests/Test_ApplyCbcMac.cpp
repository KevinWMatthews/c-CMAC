extern "C"
{
#include "AesCmac.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(ApplyCbcMac)
{
    size_t n_blocks;
    bool is_complete_block_flag;
    int ret;

    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(ApplyCbcMac, apply_to_zero_length_message)
{
    uint8_t key[16] = {};
    uint8_t T[16] = {};

    ret = apply_cbc_mac(NULL, 0, key, T);

    LONGS_EQUAL( 0, ret );
}
