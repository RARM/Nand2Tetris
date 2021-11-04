// Hack Assembler Less Symbol - This is phase one of the Hack Assembler project.
#include <iostream>
#include "Parser.h"

int main(int argc, const char* argv[])
{
    if (argc < 2) std::cout << "No arguments were passed.\n";
    else
    {
        Parser parser(argv[1]);
        bool is_open{ parser.is_open() };
        
        std::cout << "Is file \"" << argv[1] << "\" opened? " << ((is_open) ? "Yes" : "No") << ".\n\n";

        if (is_open)
        {
            while (parser.find_next_instruction())
            {
                std::cout << "Instruction found: \"" << parser.get_instruction() << "\".\n"
                          << "This is ";

                switch (parser.instruction_type())
                {
                case Parser::A_INSTRUCTION:
                    std::cout << "an a-instruction.\n"
                              << "Integer or symbol: \"" << parser.symbol() << "\"";
                    break;
                case Parser::L_INSTRUCTION:
                    std::cout << "a label.\n"
                              << "Label found: \"" << parser.symbol() << "\"";

                    break;
                case Parser::C_INSTRUCTION:
                    std::cout << "a c-instruction."
                              << "\nCOMP found: \"" << parser.comp() << "\""
                              << ((parser.dest().empty()) ? "" : "\nDEST found: \"" + parser.dest() + "\"")
                              << ((parser.jump().empty()) ? "" : "\nJUMP found: \"" + parser.jump() + "\"");
                    break;
                default:
                    std::cout << "an invalid instruction.";
                }

                std::cout << "\n\n";
            }
        }
        
    }

    return 0;
}