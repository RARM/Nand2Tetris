// Hack Assembler Less Symbol - This is phase one of the Hack Assembler project.
#include <iostream>
#include "Parser.h"

int main(int argc, const char* argv[])
{
    if (argc < 2) std::cout << "No arguments were passed.\n";
    else
    {
        Parser parser(argv[1]);
        std::cout << "Is file \"" << argv[1] << "\" opened? " << ((parser.input_file.is_open()) ? "Yes" : "No") << ".\n";
        
        if (parser.find_next_instruction())
            std::cout << "First instruction found: \"" << parser.current_instruction << "\".\n";
    }

    return 0;
}