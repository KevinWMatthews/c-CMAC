extern "C"
{
#include "Aes128.h"
// #include "Mock_Aes128.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

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

TEST(Aes128HandleCopier, existing_mock_create_with_expectaions)
{
    AES128_HANDLE handle = NULL;

    AES128_CREATE_PARAMS params = {};
    params.key = NULL;
    params.key_len = 0;
    params.iv = NULL;
    params.iv_len = 0;

    mock().expectOneCall("Aes128_Create3")
        .andReturnValue(AES128_SUCCESS);
    Aes128_Create3(&params, &handle);

    CHECK_FALSE(handle == NULL);

    mock().checkExpectations();
    mock().clear();

    Aes128_Destroy(&handle);
}
