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
    AES128_CREATE_PARAMS params2;
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

TEST(Aes128_CreateParamsComparator, compare_false_with_null_pointers)
{
    CHECK_FALSE( comparator.isEqual(NULL, &params2) );
    CHECK_FALSE( comparator.isEqual(&params, NULL) );
}

TEST(Aes128_CreateParamsComparator, compare_true_with_empty_params)
{
    CHECK_TRUE( comparator.isEqual(&params, &params2) );
}

TEST(Aes128_CreateParamsComparator, compare_true_with_zero_length_key_and_iv)
{
    params.key_len = 0;
    params.iv_len = 0;
    params2.key_len = 0;
    params2.iv_len = 0;
    CHECK_TRUE( comparator.isEqual(&params, &params2) );
}

TEST(Aes128_CreateParamsComparator, compare_true_with_actual_key_and_iv)
{
    uint8_t key[16] = {};
    uint8_t iv[16] = {};

    params.key = key;
    params.iv = iv;
    params.key_len = 0;
    params.iv_len = 0;

    params2.key = key;
    params2.iv = iv;
    params2.key_len = 0;
    params2.iv_len = 0;
    CHECK_TRUE( comparator.isEqual(&params, &params2) );
}

TEST(Aes128_CreateParamsComparator, compare_false_if_key_len_is_different)
{
    uint8_t key[16] = {};
    uint8_t key2[15] = {};

    params.key = key;
    params.key_len = sizeof(key);

    params2.key = key2;
    params2.key_len = sizeof(key2);

    CHECK_FALSE( comparator.isEqual(&params, &params2) );
}

TEST(Aes128_CreateParamsComparator, compare_false_if_iv_len_is_different)
{
    uint8_t iv[16] = {};
    uint8_t iv2[15] = {};

    params.iv = iv;
    params.iv_len = sizeof(iv);

    params2.iv = iv2;
    params2.iv_len = sizeof(iv2);

    CHECK_FALSE( comparator.isEqual(&params, &params2) );
}

TEST(Aes128_CreateParamsComparator, compare_false_if_key_content_is_different)
{
    uint8_t key[16] = {0x00};
    uint8_t key2[16] = {0x01};

    params.key = key;
    params.key_len = sizeof(key);

    params2.key = key2;
    params2.key_len = sizeof(key2);

    CHECK_FALSE( comparator.isEqual(&params, &params2) );
}

TEST(Aes128_CreateParamsComparator, compare_false_if_iv_content_is_different)
{
    uint8_t iv[16] = {0x00};
    uint8_t iv2[16] = {0x01};

    params.iv = iv;
    params.iv_len = sizeof(iv);

    params2.iv = iv2;
    params2.iv_len = sizeof(iv2);

    CHECK_FALSE( comparator.isEqual(&params, &params2) );
}

TEST(Aes128_CreateParamsComparator, example_use_case)
{
    uint8_t key[16] = {};
    uint8_t iv[16] = {};
    uint8_t key2[16] = {0x42};
    uint8_t iv2[16] = {0x66};

    params.key = key;
    params.key_len = sizeof(key);
    params.iv = iv;
    params.iv_len = sizeof(iv);

    params2.key = key2;
    params2.key_len = sizeof(key2);
    params2.iv = iv2;
    params2.iv_len = sizeof(iv2);

    mock().installComparator("AES128_CREATE_PARAMS", comparator);
    mock().expectOneCall("example_use_case")
        .withParameterOfType("AES128_CREATE_PARAMS", "params", &params);

#if 1
    // Succeeds
    mock().actualCall("example_use_case")
        .withParameterOfType("AES128_CREATE_PARAMS", "params", &params);
#else
    // Fails
    mock().actualCall("example_use_case")
        .withParameterOfType("AES128_CREATE_PARAMS", "params", &params2);
#endif
}
