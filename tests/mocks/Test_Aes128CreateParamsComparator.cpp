extern "C"
{
#include "Aes128.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Aes128CreateParamsComparator.h"

TEST_GROUP(Aes128_CreateParamsComparator)
{
    Aes128CreateParamsComparator comparator;
    AES128_CREATE_PARAMS params;
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

TEST(Aes128_CreateParamsComparator, create_and_install_comparator)
{
    mock().installComparator("AES128_CREATE_PARAMS", comparator);
}

TEST(Aes128_CreateParamsComparator, object_to_string_shows_key_and_iv)
{
    simple_string = comparator.valueToString(&params);
    string = simple_string.asCharString();
    STRCMP_CONTAINS("key: ", string);
    STRCMP_CONTAINS("iv: ", string);
}

TEST(Aes128_CreateParamsComparator, object_to_string_shows_size_and_contents_of_key)
{
    uint8_t key[16] = {};
    params.key = key;
    params.key_len = sizeof(key);

    simple_string = comparator.valueToString(&params);
    string = simple_string.asCharString();
    STRCMP_CONTAINS("key: Size = 16 | HexContent", string);
}

TEST(Aes128_CreateParamsComparator, object_to_string_shows_size_and_contents_of_iv)
{
    uint8_t iv[16] = {};
    params.iv = iv;
    params.iv_len = sizeof(iv);

    simple_string = comparator.valueToString(&params);
    string = simple_string.asCharString();
    STRCMP_CONTAINS("iv: Size = 16 | HexContent", string);
}
