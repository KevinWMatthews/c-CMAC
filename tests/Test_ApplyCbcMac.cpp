extern "C"
{
#include "AesCmac.h"
#include "Aes.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Aes128Comparator.h"

TEST_GROUP(ApplyCbcMac)
{
    Aes128Comparator comparator;
    size_t n_blocks;
    bool is_complete_block_flag;
    int ret;

    void setup()
    {
        mock().strictOrder();
    }

    void teardown()
    {
        mock().checkExpectations();
        mock().clear();
        mock().removeAllComparatorsAndCopiers();
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
    ret = apply_cbc_mac(key, NULL, 1, X, Y);

    LONGS_EQUAL( 0, ret );

    // Change nothing?
    MEMCMP_EQUAL( expected_X, X, sizeof(expected_X) );
    MEMCMP_EQUAL( expected_Y, Y, sizeof(expected_Y) );
}

TEST(ApplyCbcMac, finish_zero_length_message_part_1)
{
    uint8_t M_last[16] = {0x80};
    uint8_t X[16] = {};
    uint8_t Y[16] = {};
    uint8_t expected[16] = {0x80};

    ret = finish_cbc_mac_1(M_last, X, Y);

    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, Y, sizeof(expected) );
}

TEST(ApplyCbcMac, finish_zero_length_message_part_2)
{
    uint8_t key[16] = {};
    uint8_t Y[16] = {0x80};
    uint8_t T[16] = {};

    // Calculated expected using online tool
    uint8_t expected[16] = {
        0x3A, 0xD7, 0x8E, 0x72, 0x6C, 0x1E, 0xC0, 0x2B,
        0x7E, 0xBF, 0xE9, 0x2B, 0x23, 0xD9, 0xEC, 0x34,
    };
    // Values for mocks
    AES_KEY_128 aes_params = {};
    aes_params.key = key;
    aes_params.key_len = sizeof(key);
    aes_params.iv = zeros;
    aes_params.iv_len = sizeof(zeros);



    mock().installComparator("AES_KEY_128", comparator);
    mock().expectOneCall("Aes_Calculate128")
        .withParameterOfType("AES_KEY_128", "aes_128", &aes_params)
        .withMemoryBufferParameter("input", Y, sizeof(Y))
        .withParameter("input_len", sizeof(Y))
        .withOutputParameterReturning("output", expected, sizeof(expected))
        .withParameter("output_len", sizeof(expected))
        .andReturnValue(0);

    ret = finish_cbc_mac_2(key, Y, T);

    mock().checkExpectations();
    LONGS_EQUAL( 0, ret );
    MEMCMP_EQUAL( expected, T, sizeof(expected) );
}
