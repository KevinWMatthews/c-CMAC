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
         // *(MyType*)out = *(const MyType*)in;
        if (in == NULL)
            return;
        if (out == NULL)
            return;

        AES128_HANDLE * out_handle = (AES128_HANDLE *)out;
        const AES128_HANDLE * in_handle = (const AES128_HANDLE *)in;

        *out_handle = *in_handle;
    }
};

class Aes128StructCopier : public MockNamedValueCopier
{
public:
    virtual void copy(void* out, const void* in)
    {
        if (in == NULL)
            return;
        if (out == NULL)
            return;

        AES128_STRUCT * out_struct = (AES128_STRUCT *)out;
        const AES128_STRUCT * in_struct = (const AES128_STRUCT *)in;

        out_struct->key = in_struct->key;
        out_struct->key_len = in_struct->key_len;
        out_struct->iv = in_struct->iv;
        out_struct->iv_len = in_struct->iv_len;

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
        mock().clear();
    }
};

TEST(Aes128HandleCopier, create_and_install_copier)
{
    mock().installCopier("Aes128HandleCopier", copier);
    mock().checkExpectations();
    mock().removeAllComparatorsAndCopiers();
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
}

TEST(Aes128HandleCopier, experiment_with_simple_copier)
{
    Aes128StructCopier copier;

    uint8_t key[16] = {0x00, 0x11};
    uint8_t iv[16] = {0xff, 0xee};

    AES128_STRUCT aes_struct = {};
    aes_struct.key = key;
    aes_struct.key_len = sizeof(key);
    aes_struct.iv = iv;
    aes_struct.iv_len = sizeof(iv);

    mock().installCopier("AES128_STRUCT", copier);
    mock().expectOneCall("MockAesCreate")
        .withOutputParameterOfTypeReturning("AES128_STRUCT", "aes_struct", &aes_struct);

    // This happens in a function somewhere
    AES128_STRUCT aes_struct2 = {};
    MockAesCreate(&aes_struct2);

    POINTERS_EQUAL(key, aes_struct2.key);
    LONGS_EQUAL(sizeof(key), aes_struct2.key_len);
    MEMCMP_EQUAL(key, aes_struct2.key, sizeof(key));

    POINTERS_EQUAL(iv, aes_struct2.iv);
    LONGS_EQUAL(sizeof(iv), aes_struct2.iv_len);
    MEMCMP_EQUAL(iv, aes_struct2.iv, sizeof(iv));

    mock().checkExpectations();
    mock().removeAllComparatorsAndCopiers();
}

TEST(Aes128HandleCopier, create_using_handle_copier)
{
    Aes128CreateParamsComparator comparator;
    Aes128HandleCopier copier;

    uint8_t key[16] = {0x00, 0x11};
    uint8_t iv[16] = {0xff, 0xee};

    AES128_STRUCT aes_struct = {};
    AES128_HANDLE handle = &aes_struct;
    aes_struct.key = key;
    aes_struct.key_len = sizeof(key);
    aes_struct.iv = iv;
    aes_struct.iv_len = sizeof(iv);

    AES128_CREATE_PARAMS params = {};
    params.key = key;
    params.key_len = sizeof(key);
    params.iv = iv;
    params.iv_len = sizeof(iv);

    mock().installComparator("AES128_CREATE_PARAMS", comparator);
    mock().installCopier("AES128_HANDLE", copier);

    mock().expectOneCall("Aes128_Create5")
        .withParameterOfType("AES128_CREATE_PARAMS", "params", &params)
        .withOutputParameterOfTypeReturning("AES128_HANDLE", "aes_handle", &handle)
        .andReturnValue(AES128_SUCCESS);

    // This will happen inside a function somewhere
    AES128_HANDLE handle2 = NULL;
    Aes128_Create5(&params, &handle2);

    POINTERS_EQUAL(handle2, handle);

    // Check our setup
    POINTERS_EQUAL(key, handle->key);
    LONGS_EQUAL(sizeof(key), handle->key_len);
    MEMCMP_EQUAL(key, handle->key, sizeof(key));

    POINTERS_EQUAL(iv, handle->iv);
    LONGS_EQUAL(sizeof(iv), handle->iv_len);
    MEMCMP_EQUAL(iv, handle->iv, sizeof(iv));

    CHECK_FALSE(handle2 == NULL);

    // Check that we didn't change our original handle...
    POINTERS_EQUAL(key, handle2->key);
    LONGS_EQUAL(sizeof(key), handle2->key_len);
    MEMCMP_EQUAL(key, handle2->key, sizeof(key));

    POINTERS_EQUAL(iv, handle2->iv);
    LONGS_EQUAL(sizeof(iv), handle2->iv_len);
    MEMCMP_EQUAL(iv, handle2->iv, sizeof(iv));

    // Aes128_Destroy(&handle);

    mock().checkExpectations();
    mock().removeAllComparatorsAndCopiers();
}
