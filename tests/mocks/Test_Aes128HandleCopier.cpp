extern "C"
{
#include "Aes128.h"
#include "Mock_Aes128.h"
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
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(Aes128HandleCopier, create_and_install_copier)
{
    Aes128HandleCopier copier;
    mock().installCopier("Aes128HandleCopier", copier);
    mock().checkExpectations();
    mock().removeAllComparatorsAndCopiers();
    mock().clear();
}
