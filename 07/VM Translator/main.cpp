// VM Translator
#include <iostream>
#include <string>
#include "Parser.h"

int main(int argc, char* argv[])
{
    // The current_line and current_command attributes of the Parser class were made public for this test.
    // Note to self: remember to put them back as private classes.
    std::cout << "Initializing Parser with \"" << argv[1] << "\".\n";
    std::string filename(argv[1]);
    Parser parser(filename);

    std::cout << "Printing instructions along with line in which they were found.\n\n"
              << "Commands found:\n";

    while (parser.find_next_command())
        std::cout << parser.current_line << ": " << parser.current_command << "\n";

    std::cout << "\n";

    return 0;
}