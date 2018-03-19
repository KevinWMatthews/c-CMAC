extern "C"
{
#include "Aes128.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Aes128CryptoParamsComparator.h"
#include "Mock_Aes128.h"
#include <string.h>

TEST_GROUP(Aes128_CryptoParamsComparator)
{
    Aes128CryptoParamsComparator comparator;
    AES128_CRYPTO_PARAMS params;
    AES128_CRYPTO_PARAMS params2;
    SimpleString simple_string;
    const char *string;

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

TEST(Aes128_CryptoParamsComparator, create_and_install_comparator)
{
    mock().installComparator("AES128_CRYPTO_PARAMS", comparator);
}

TEST(Aes128_CryptoParamsComparator, object_to_string_will_not_segfault_with_null_params)
{
    simple_string = comparator.valueToString(NULL);
    string = simple_string.asCharString();

    STRCMP_CONTAINS("AES128_CRYPTO_PARAMS: NULL", string);
}

TEST(Aes128_CryptoParamsComparator, object_to_string_shows_all_elements)
{
    simple_string = comparator.valueToString(&params);
    string = simple_string.asCharString();

    STRCMP_CONTAINS("AES128_CRYPTO_PARAMS:", string);
    STRCMP_CONTAINS("AES128_CREATE_PARAMS:", string);
    STRCMP_CONTAINS("input:", string);
}

TEST(Aes128_CryptoParamsComparator, object_to_string_shows_input_values)
{
    uint8_t input[16] = {0x00, 0x01, 0x02};
    params.input = input;
    params.input_len = sizeof(input);

    simple_string = comparator.valueToString(&params);
    string = simple_string.asCharString();

    STRCMP_CONTAINS("AES128_CRYPTO_PARAMS", string);
    STRCMP_CONTAINS("input:", string);
    STRCMP_CONTAINS("00 01 02", string);
}

TEST(Aes128_CryptoParamsComparator, compare_with_null_pointers)
{
    CHECK_TRUE( comparator.isEqual(NULL, NULL) );
    CHECK_FALSE( comparator.isEqual(NULL, &params2) );
    CHECK_FALSE( comparator.isEqual(&params, NULL) );
}

TEST(Aes128_CryptoParamsComparator, compare_true_with_empty_params)
{
    CHECK_TRUE( comparator.isEqual(&params, &params2) );
}

TEST(Aes128_CryptoParamsComparator, compare_false_with_different_input)
{
    uint8_t input1[16] = {0x01};
    uint8_t input2[16] = {};

    params.input = input1;
    params.input_len = sizeof(input1);

    params.input = input2;
    params.input_len = sizeof(input2);

    CHECK_FALSE( comparator.isEqual(&params, &params2) );
}

TEST(Aes128_CryptoParamsComparator, compare_true_with_equivalent_aes_handle)
{
    AES128_STRUCT aes_struct = {};
    AES128_HANDLE aes_handle1 = &aes_struct;
    AES128_HANDLE aes_handle2 = &aes_struct;
    uint8_t key[16] = {};
    uint8_t iv[16] = {};
    uint8_t input[16] = {};

    aes_struct.key = key;
    aes_struct.key_len = sizeof(key);
    aes_struct.iv = iv;
    aes_struct.iv_len = sizeof(iv);

    params.aes_handle = aes_handle1;
    params.input = input;
    params.input_len = sizeof(input);

    params2.aes_handle = aes_handle2;
    params2.input = input;
    params2.input_len = sizeof(input);

    CHECK_TRUE( comparator.isEqual(&params, &params2) );
}
