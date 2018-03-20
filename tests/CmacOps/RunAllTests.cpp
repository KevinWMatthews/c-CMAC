#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestPlugin.h"
#include "CppUTest/TestRegistry.h"
#include "CppUTestExt/MockSupportPlugin.h"
#include "Aes128CryptoParamsComparator.h"

int main(int ac, char **av)
{
    Aes128CryptoParamsComparator crypto_comparator;
    MockSupportPlugin mockPlugin;

    mockPlugin.installComparator("AES128_CRYPTO_PARAMS", crypto_comparator);
    TestRegistry::getCurrentRegistry()->installPlugin(&mockPlugin);

    return CommandLineTestRunner::RunAllTests(ac, av);
}
