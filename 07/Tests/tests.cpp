// Run this program to tests the Parser and CodeWriter modules of the main project.
#include <iostream>
#include <vector>
#include "../VM Translator/Parser.h"

// Tests Methods

void find_next_command_test();
void command_type_test_1();

int main(void)
{
    find_next_command_test();
    command_type_test_1();
    return 0;
}

// Implementation of test methods.

void find_next_command_test()
{
    std::cout << "Testing \"find_next_command\" method of the Parser class (using SimpleAdd.vm file).\n";
    
    Parser my_parser(std::string("SimpleAdd.vm"));
    std::vector<std::string> expected_results{
        "push constant 7",
        "push constant 8",
        "add"
    };

    for (size_t i = 0; i < 3; i++)
    {
        my_parser.find_next_command();
        std::string output(my_parser.get_current_command());

        std::cout << ((output == expected_results.at(i)) ? "Passed." : "Not passed: \"" + output + "\" is not equal to \"" + expected_results.at(i) + "\".") << "\n";
    }

    std::cout << "\n\n";

    return;
}

void command_type_test_1()
{
    std::cout << "Testing \"command_type\" method of the Parser class (using SimpleAdd.vm file).\n";

    Parser my_parser(std::string("SimpleAdd.vm"));

    /*while (my_parser.find_next_command())
    {
        if (my_parser.command_type() == Parser::INVALID_INS)
            std::cout << my_parser.get_error_message() << "\n";
    }*/

    return;
}
