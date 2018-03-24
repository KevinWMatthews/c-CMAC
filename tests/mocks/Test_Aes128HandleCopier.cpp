extern "C"
{
#include "Aes128.h"
#include "Mock_Aes128.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Aes128CreateParamsComparator.h"

class Aes128HandleCopier : public MockNamedValueCopier
{
public:
    virtual void copy(void* out, const void* in)
    {

    }
};

TEST_GROUP(Aes128HandleCopier)
{
    Aes128HandleCopier copier;

    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(Aes128HandleCopier, create_and_install_copier)
{
    mock().installCopier("Aes128HandleCopier", copier);
    mock().checkExpectations();
    mock().removeAllComparatorsAndCopiers();
    mock().clear();
}

TEST(Aes128HandleCopier, can_copy_null_aes_handle)
{
    AES128_HANDLE handle = NULL;
    AES128_HANDLE handle2 = NULL;

    copier.copy(handle2, handle);

    POINTERS_EQUAL(handle, handle2);
}

TEST(Aes128HandleCopier, existing_mock_create)
{
    AES128_HANDLE handle = NULL;

    AES128_CREATE_PARAMS params = {};
    params.key = NULL;
    params.key_len = 0;
    params.iv = NULL;
    params.iv_len = 0;

    Aes128_Create2(&params, &handle);

    CHECK_FALSE(handle == NULL);

    Aes128_Destroy(&handle);
}

TEST(Aes128HandleCopier, existing_mock_create_with_values)
{
    AES128_HANDLE handle = NULL;

    AES128_CREATE_PARAMS params = {};
    uint8_t key[16] = {0x00, 0x11};
    uint8_t iv[16] = {0xff, 0xee};

    params.key = key;
    params.key_len = sizeof(key);
    params.iv = iv;
    params.iv_len = sizeof(iv);

    Aes128_Create2(&params, &handle);

    CHECK_FALSE(handle == NULL);

    POINTERS_EQUAL(key, handle->key);
    LONGS_EQUAL(sizeof(key), handle->key_len);
    MEMCMP_EQUAL(key, handle->key, sizeof(key));

    POINTERS_EQUAL(iv, handle->iv);
    LONGS_EQUAL(sizeof(iv), handle->iv_len);
    MEMCMP_EQUAL(iv, handle->iv, sizeof(iv));

    Aes128_Destroy(&handle);
}

TEST(Aes128HandleCopier, existing_mock_create_with_expectations)
{
    Aes128CreateParamsComparator comparator;

    AES128_HANDLE handle = NULL;

    AES128_CREATE_PARAMS params = {};
    uint8_t key[16] = {0x00, 0x11};
    uint8_t iv[16] = {0xff, 0xee};

    params.key = key;
    params.key_len = sizeof(key);
    params.iv = iv;
    params.iv_len = sizeof(iv);

    mock().installComparator("AES128_CREATE_PARAMS", comparator);
    mock().expectOneCall("Aes128_Create4")
        .withParameterOfType("AES128_CREATE_PARAMS", "params", &params)
        .withOutputParameterReturning("aes_handle", &handle, sizeof(handle))
        .andReturnValue(AES128_SUCCESS);

    Aes128_Create4(&params, &handle);

    CHECK_FALSE(handle == NULL);

    POINTERS_EQUAL(key, handle->key);
    LONGS_EQUAL(sizeof(key), handle->key_len);
    MEMCMP_EQUAL(key, handle->key, sizeof(key));

    POINTERS_EQUAL(iv, handle->iv);
    LONGS_EQUAL(sizeof(iv), handle->iv_len);
    MEMCMP_EQUAL(iv, handle->iv, sizeof(iv));

    Aes128_Destroy(&handle);

    mock().checkExpectations();
    mock().removeAllComparatorsAndCopiers();
    mock().clear();
}
