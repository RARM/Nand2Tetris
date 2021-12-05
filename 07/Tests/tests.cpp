// Run this program to tests the Parser and CodeWriter modules of the main project.
#include <iostream>
#include "../VM Translator/Parser.h"

// Tests Methods

void find_next_command_test();

int main(void)
{
    find_next_command_test();
    return 0;
}

// Implementation of test methods.

void find_next_command_test()
{
    std::cout << "Testing \"find_next_command\" method of the Parser attribute.\n";

    Parser my_parser(std::string("Test.vm"));
    my_parser.find_next_command();
    std::string output(my_parser.get_current_command());
    std::string expected("push constant 7");

    std::cout << ((output == expected) ? "Passed." : "Not passed: \"" + output + "\" is not equal to \"" + expected + "\".");

    std::cout << "\n\n";

    return;
}