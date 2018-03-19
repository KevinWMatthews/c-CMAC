extern "C"
{
#include "Aes128.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Aes128CryptoParamsComparator.h"
#include <string.h>

TEST_GROUP(Aes128_CryptoParamsComparator)
{
    Aes128CryptoParamsComparator comparator;
    AES128_CRYPTO_PARAMS params;
    SimpleString simple_string;
    const char *string;

    void setup()
    {
        mock().strictOrder();
        memset( &params, 0, sizeof(params) );
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
