// Hack Assembler -- Phase 2 assembler. It processes symbols as well.
#include <iostream>
#include <string>
#include <fstream>
#include "Parser.h"
#include "Core.h"

int main(int argc, char* argv[])
{
    if (argc <= 1) std::cout << "No arguments...\n\n";
    else
    {
        for (size_t i = 1; i < argc; i++) // Compiles every file passed as argument.
        {
            // Check if file ends in ".asm".
            const std::string ext(".asm");
            std::string filename(argv[i]);

            if (filename.compare(filename.length() - ext.length(), ext.length(), ext) != 0)
                std::cout << "The file \"" << argv[i] << "\" is not of the extension \".asm\".\n";
            else
            {
                // Compile file if the extension is correct.
                Parser parser(filename);

                // Create or rewrite target file.
                filename.erase(filename.length() - ext.length(), ext.length());
                std::ofstream file_output(filename + ".hack");

                if (file_output.is_open())
                {
                    int line(-1);
                    while (parser.find_next_instruction())
                    {   // Translation.
                        line++;
                        switch (parser.instruction_type())
                        {
                        case Parser::A_INSTRUCTION:
                            file_output << "0" << Core::integer(parser.symbol()) << "\n";
                            break;
                        case Parser::C_INSTRUCTION:
                            file_output << "111" << Core::comp(parser.comp()) << Core::dest(parser.dest()) << Core::jump(parser.jump()) << "\n";
                            break;
                        default:
                            std::cout << "An invalid instruction \"" << parser.get_instruction() << "\" has been found in the source code at line " << line << ".\n";
                            break;
                        }
                    }
                }
                else std::cout << "Could open \"" << filename << ".hack\" for writing.\n";

                file_output.close();
            }
        }
    }

    return 0;
}