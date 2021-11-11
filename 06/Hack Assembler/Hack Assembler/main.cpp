// Hack Assembler -- Phase 2 assembler. It processes symbols as well.
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <utility>
#include "Parser.h"
#include "Core.h"
#include "Symbols.h"

// Helper functions.

void initialize_table(Symbols& table);
bool is_number(const std::string& text);
std::pair<bool, std::string> construct_a(Parser& parser, Symbols& table);

int main(int argc, char* argv[])
{
    if (argc <= 1) std::cout << "No arguments...\n";
    else
    {
        for (int i = 1; i < argc; i++) // Compiles every file passed as argument.
        {
            // Check if file ends in ".asm".
            const std::string ext(".asm");
            std::string filename(argv[i]);

            if (filename.compare(filename.length() - ext.length(), ext.length(), ext) != 0)
                std::cout << "The file \"" << argv[i] << "\" is not of the extension \".asm\".\n";
            else
            {
                // Initialization.
                Parser parser(filename);
                Symbols table;

                if (parser.is_open())
                {
                    // Create or rewrite target file.
                    filename.erase(filename.length() - ext.length(), ext.length());
                    std::ofstream file_output(filename + ".hack");

                    if (file_output.is_open())
                    {
                        // If everything is good to go, initialize table and start first pass.
                        initialize_table(table);
                        int line_number{ 0 };
                        bool invalid_instruction{ false };

                        // First pass.
                        while (parser.find_next_instruction() && !invalid_instruction)
                        {
                            switch (parser.instruction_type())
                            {
                            case Parser::A_INSTRUCTION:
                            case Parser::C_INSTRUCTION:
                                line_number++;
                                break;
                            case Parser::L_INSTRUCTION:
                                if (table.contains(parser.symbol()))
                                {
                                    std::cout << "Label: \"" << parser.get_instruction() << "\" was declared twice.\n";
                                    invalid_instruction = true;
                                }
                                else table.addEntry(parser.symbol(), line_number);
                                break;
                            default:
                                invalid_instruction = true;
                                std::cout << "Invalid instruction: \"" << parser.get_instruction() << "\" at " << line_number << ".\n";
                                break;
                            }
                        }

                        // Second pass.
                        parser.rewind();
                        if (!invalid_instruction)
                        {
                            bool fail{ false };

                            while (parser.find_next_instruction() && !fail)
                            {
                                switch (parser.instruction_type())
                                {
                                case Parser::A_INSTRUCTION:
                                {
                                    const auto [success, a_ins] = construct_a(parser, table);
                                    if (success)
                                        file_output << a_ins;
                                    else
                                    {
                                        std::cout << "Error: ran out of RAM.\n";
                                        fail = true;
                                    }
                                }
                                    break;

                                case Parser::C_INSTRUCTION:
                                    file_output << "111" << Core::comp(parser.comp()) << Core::dest(parser.dest()) << Core::jump(parser.jump()) << "\n";
                                    break;

                                case Parser::L_INSTRUCTION:
                                    break; // Labels are ignored.

                                default:
                                    std::cout << "Error: instruction not recognized: \"" << parser.get_instruction() << "\".\n";
                                    fail = true;
                                    break;
                                }
                            }

                            if (!fail)
                                std::cout << "Total instructions assembled: " << --line_number << ".\n";
                        }
                    }

                    else
                        if (!file_output.is_open()) std::cout << "Could not open \"" << filename << ".hack\" for writing.\n";

                    file_output.close();
                }

                else std::cout << "Could not open \"" << filename << "\" for reading.\n";

            }
        }
    }

    std::cout << "\n";

    return 0;
}

void initialize_table(Symbols& table)
{
    // Adding predefined symbols.

    // Registers.
    table.addEntry("R0", 0);
    table.addEntry("R1", 1);
    table.addEntry("R2", 2);
    table.addEntry("R3", 3);
    table.addEntry("R4", 4);
    table.addEntry("R5", 5);
    table.addEntry("R6", 6);
    table.addEntry("R7", 7);
    table.addEntry("R8", 8);
    table.addEntry("R9", 9);
    table.addEntry("R10", 10);
    table.addEntry("R11", 11);
    table.addEntry("R12", 12);
    table.addEntry("R13", 13);
    table.addEntry("R14", 14);
    table.addEntry("R15", 15);

    // VM symbols.
    table.addEntry("SP", 0);
    table.addEntry("LCL", 1);
    table.addEntry("ARG", 2);
    table.addEntry("THIS", 3);
    table.addEntry("THAT", 4);

    // IO mappings.
    table.addEntry("SCREEN", 16384);
    table.addEntry("KBD", 24576);

    return;
}

bool is_number(const std::string& text)
{
    const std::regex number("[0-9]+"); // https://regexr.com/

    return std::regex_match(text, number);
}

std::pair<bool, std::string> construct_a(Parser& parser, Symbols& table)
{
    static int counter{ 16 };
    bool success;
    std::string a_string("0");

    if (is_number(parser.symbol())) // If it is just a number.
    {
        a_string += Core::integer(parser.symbol()) + "\n";
        success = true;
    }

    else if (table.contains(parser.symbol())) // If it is a symbol already on the table.
    {
        a_string += Core::integer(std::to_string(table.getAddress(parser.symbol()))) + "\n";
        success = true;
    }

    else if (counter >= 16384)
        // If there is no more space in the RAM.
        // 16384 is where the screen starts.
    {
        a_string = "";
        success = false;
    }

    else // If it is a symbol, it is not on the table, and there is space for a new symbol.
    {
        table.addEntry(parser.symbol(), counter);
        a_string += Core::integer(std::to_string(counter++));
        success = true;
    }

    return std::pair<bool, std::string>(success, a_string);
}
