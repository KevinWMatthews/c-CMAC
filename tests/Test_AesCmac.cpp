extern "C"
{
#include "AesCmac.h"
#include "Aes.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Aes128Comparator.h"

static uint8_t zeros[16] = {};

TEST_GROUP(AesCmac)
{
    Aes128Comparator comparator;
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

TEST(AesCmac, rfc_4493_example_1_message_length_0)
{
    unsigned char expected[] = {
        0xbb, 0x1d, 0x69, 0x29, 0xe9, 0x59, 0x37, 0x28,
        0x7f, 0xa3, 0x7d, 0x12, 0x9b, 0x75, 0x67, 0x46,
    };
    unsigned char key[] = {
        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c,
    };
    unsigned char *message = NULL;
    size_t message_len = 0;

    unsigned char cmac[16] = {};

    // Values for mocks
    AES_KEY_128 aes_params = {};
    aes_params.key = key;
    aes_params.key_len = sizeof(key);
    aes_params.iv = zeros;
    aes_params.iv_len = sizeof(zeros);
    // Manually calculate L
    uint8_t L[16] = {
        0x7d, 0xf7, 0x6b, 0x0c, 0x1a, 0xb8, 0x99, 0xb3,
        0x3e, 0x42, 0xf0, 0x47, 0xb9, 0x1b, 0x54, 0x6f,
    };

    mock().installComparator("AES_KEY_128", comparator);

    // Step 1: Calculate L from key
    mock().expectOneCall("Aes_Calculate128")
        .withParameterOfType("AES_KEY_128", "aes_128", &aes_params)
        .withMemoryBufferParameter("input", zeros, sizeof(zeros))
        .withParameter("input_len", sizeof(zeros))
        .withOutputParameterReturning("output", L, sizeof(L))
        .withParameter("output_len", sizeof(L))
        .andReturnValue(0);

    // Step 6: Calculate T from Y
    // Capture value from mock failure
    uint8_t Y[16] = {
        0x77, 0xDD, 0xAC, 0x30, 0x6A, 0xE2, 0x66, 0xCC,
        0xF9, 0x0B, 0xC1, 0x1E, 0xE4, 0x6D, 0x51, 0x3B,
    };
    // Manually calculate from Y
    uint8_t T[16] = {
        0xBB, 0x1D, 0x69, 0x29, 0xE9, 0x59, 0x37, 0x28,
        0x7F, 0xA3, 0x7D, 0x12, 0x9B, 0x75, 0x67, 0x46,
    };

    mock().expectOneCall("Aes_Calculate128")
        .withParameterOfType("AES_KEY_128", "aes_128", &aes_params)
        .withMemoryBufferParameter("input", Y, sizeof(Y))
        .withParameter("input_len", sizeof(Y))
        .withOutputParameterReturning("output", T, sizeof(T))
        .withParameter("output_len", sizeof(T))
        .andReturnValue(0);

    ret = AesCmac_Calculate128( key, sizeof(key), message, message_len, cmac, sizeof(cmac) );

    LONGS_EQUAL( ret, 0 );
    MEMCMP_EQUAL( expected, cmac, sizeof(expected) );
}
