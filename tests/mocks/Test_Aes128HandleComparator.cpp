extern "C"
{
#include "Aes128.h"
#include "MockAes128.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Aes128HandleComparator.h"

TEST_GROUP(Aes128_HandleComparator)
{
    Aes128HandleComparator comparator;
    AES128_HANDLE handle;
    AES128_HANDLE handle2;
    AES128_STRUCT aes_struct;
    AES128_STRUCT aes_struct2;
    SimpleString simple_string;
    const char *string;

    void setup()
    {
        mock().strictOrder();
        handle = &aes_struct;
        handle2 = &aes_struct2;
    }

    void teardown()
    {
        mock().clear();
    }
};

TEST(Aes128_HandleComparator, create_and_install_comparator)
{
    mock().installComparator("AES128_HANDLE", comparator);
    mock().checkExpectations();
    mock().removeAllComparatorsAndCopiers();
}

TEST(Aes128_HandleComparator, object_to_string_shows_null_handle)
{
    simple_string = comparator.valueToString(NULL);
    string = simple_string.asCharString();
    STRCMP_CONTAINS("AES128_HANDLE: NULL", string);
}

TEST(Aes128_HandleComparator, object_to_string_will_not_segfault_with_null_key)
{
    uint8_t iv[16] = {};
    handle->key = NULL;
    handle->key_len = 1;
    handle->iv = iv;
    handle->iv_len = sizeof(iv);

    simple_string = comparator.valueToString(handle);
    string = simple_string.asCharString();
    STRCMP_CONTAINS("key: ", string);
    STRCMP_CONTAINS("iv: ", string);
}

TEST(Aes128_HandleComparator, object_to_string_will_not_segfault_with_null_iv)
{
    uint8_t key[16] = {};
    handle->key = key;
    handle->key_len = sizeof(key);
    handle->iv = NULL;
    handle->iv_len = 1;

    simple_string = comparator.valueToString(handle);
    string = simple_string.asCharString();
    STRCMP_CONTAINS("key: ", string);
    STRCMP_CONTAINS("iv: ", string);
}

TEST(Aes128_HandleComparator, object_to_string_shows_key_and_iv)
{
    uint8_t key[16] = {0x88};
    uint8_t iv[16] = {0x99};

    handle->key = key;
    handle->key_len = sizeof(key);
    handle->iv = iv;
    handle->iv_len = sizeof(iv);

    simple_string = comparator.valueToString(handle);
    string = simple_string.asCharString();
    STRCMP_CONTAINS("key: Size = 16 | HexContent", string);
    STRCMP_CONTAINS(" 88 ", string)
    STRCMP_CONTAINS("iv: Size = 16 | HexContent", string);
    STRCMP_CONTAINS(" 99 ", string)
}

TEST(Aes128_HandleComparator, compare_with_null_pointers)
{
    CHECK_TRUE( comparator.isEqual(NULL, NULL) );
    CHECK_FALSE( comparator.isEqual(NULL, handle2) );
    CHECK_FALSE( comparator.isEqual(handle, NULL) );
}

TEST(Aes128_HandleComparator, compare_true_with_empty_handle)
{
    CHECK_TRUE( comparator.isEqual(handle, handle2) );
}

TEST(Aes128_HandleComparator, compare_true_with_null_and_zero_length_key_and_iv)
{
    handle->key_len = 0;
    handle->iv_len = 0;
    handle2->key_len = 0;
    handle2->iv_len = 0;
    CHECK_TRUE( comparator.isEqual(handle, handle2) );
}

TEST(Aes128_HandleComparator, compare_true_with_actual_key_and_iv)
{
    uint8_t key[16] = {};
    uint8_t iv[16] = {};

    handle->key = key;
    handle->iv = iv;
    handle->key_len = 0;
    handle->iv_len = 0;

    handle2->key = key;
    handle2->iv = iv;
    handle2->key_len = 0;
    handle2->iv_len = 0;
    CHECK_TRUE( comparator.isEqual(handle, handle2) );
}

TEST(Aes128_HandleComparator, compare_false_if_key_len_is_different)
{
    uint8_t key[16] = {};
    uint8_t key2[15] = {};

    handle->key = key;
    handle->key_len = sizeof(key);

    handle2->key = key2;
    handle2->key_len = sizeof(key2);

    CHECK_FALSE( comparator.isEqual(handle, handle2) );
}

TEST(Aes128_HandleComparator, compare_false_if_iv_len_is_different)
{
    uint8_t iv[16] = {};
    uint8_t iv2[15] = {};

    handle->iv = iv;
    handle->iv_len = sizeof(iv);

    handle2->iv = iv2;
    handle2->iv_len = sizeof(iv2);

    CHECK_FALSE( comparator.isEqual(handle, handle2) );
}

TEST(Aes128_HandleComparator, compare_false_if_key_content_is_different)
{
    uint8_t key[16] = {0x00};
    uint8_t key2[16] = {0x01};

    handle->key = key;
    handle->key_len = sizeof(key);

    handle2->key = key2;
    handle2->key_len = sizeof(key2);

    CHECK_FALSE( comparator.isEqual(handle, handle2) );
}

TEST(Aes128_HandleComparator, compare_false_if_iv_content_is_different)
{
    uint8_t iv[16] = {0x00};
    uint8_t iv2[16] = {0x01};

    handle->iv = iv;
    handle->iv_len = sizeof(iv);

    handle2->iv = iv2;
    handle2->iv_len = sizeof(iv2);

    CHECK_FALSE( comparator.isEqual(handle, handle2) );
}

TEST(Aes128_HandleComparator, example_use_case)
{
    uint8_t key[16] = {};
    uint8_t iv[16] = {};
    uint8_t key2[16] = {0x42};
    uint8_t iv2[16] = {0x66};

    handle->key = key;
    handle->key_len = sizeof(key);
    handle->iv = iv;
    handle->iv_len = sizeof(iv);

    handle2->key = key2;
    handle2->key_len = sizeof(key2);
    handle2->iv = iv2;
    handle2->iv_len = sizeof(iv2);

    mock().installComparator("AES128_HANDLE", comparator);
    mock().expectOneCall("example_use_case")
        .withParameterOfType("AES128_HANDLE", "handle", handle);

#if 1
    // Succeeds
    mock().actualCall("example_use_case")
        .withParameterOfType("AES128_HANDLE", "handle", handle);
#else
    // Fails
    mock().actualCall("example_use_case")
        .withParameterOfType("AES128_HANDLE", "handle", handle2);
#endif
    mock().checkExpectations();
    mock().removeAllComparatorsAndCopiers();
}
