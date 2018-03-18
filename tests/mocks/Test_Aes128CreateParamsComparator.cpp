extern "C"
{
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Aes128CreateParamsComparator.h"

TEST_GROUP(Aes128_CreateParamsComparator)
{
    Aes128CreateParamsComparator comparator;

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
