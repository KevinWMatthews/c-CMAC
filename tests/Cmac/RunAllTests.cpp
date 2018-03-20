#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestPlugin.h"
#include "CppUTest/TestRegistry.h"
#include "CppUTestExt/MockSupportPlugin.h"
#include "Aes128Comparator.h"

int main(int ac, char **av)
{
    Aes128Comparator comparator;
    MockSupportPlugin mockPlugin;

    mockPlugin.installComparator("AES_KEY_128", comparator);
    TestRegistry::getCurrentRegistry()->installPlugin(&mockPlugin);

    return CommandLineTestRunner::RunAllTests(ac, av);
}
