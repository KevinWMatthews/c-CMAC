#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestPlugin.h"
#include "CppUTest/TestRegistry.h"
#include "CppUTestExt/MockSupportPlugin.h"
#include "Aes128Comparator.h"
#include "Aes128Copier.h"
#include "Aes128CreateParamsComparator.h"
#include "Aes128CryptoParamsComparator.h"

int main(int ac, char **av)
{
    Aes128Comparator aes128_comparator;
    Aes128Copier aes128_copier;
    Aes128CreateParamsComparator create_comparator;
    Aes128CryptoParamsComparator crypto_comparator;
    MockSupportPlugin mockPlugin;

    mockPlugin.installComparator("AES128_HANDLE", aes128_comparator);
    mockPlugin.installCopier("AES128_HANDLE", aes128_copier);
    mockPlugin.installComparator("AES128_CREATE_PARAMS", create_comparator);
    mockPlugin.installComparator("AES128_CRYPTO_PARAMS", crypto_comparator);
    TestRegistry::getCurrentRegistry()->installPlugin(&mockPlugin);

    return CommandLineTestRunner::RunAllTests(ac, av);
}
