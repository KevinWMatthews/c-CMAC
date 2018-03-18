extern "C"
{
#include "Aes128.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Aes128CryptoParamsComparator.h"

TEST_GROUP(Aes128_CryptoParamsComparator)
{
    Aes128CryptoParamsComparator comparator;
    AES128_CRYPTO_PARAMS params;
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

IGNORE_TEST(Aes128_CryptoParamsComparator, object_to_string_shows_all_elements)
{
    simple_string = comparator.valueToString(&params);
    string = simple_string.asCharString();

    STRCMP_CONTAINS("AES handle:", string);
    STRCMP_CONTAINS("input:", string);
}
