#include "Parser.h"
#include <vector>

Parser::Parser(std::string input_filename)
    : current_command{ std::string("") }, input_file{ std::ifstream(input_filename) }, current_line{ 0 }
{}

Parser::~Parser()
{
    this->input_file.close();
}

bool Parser::find_next_command()
{
    std::string line;
    bool command_found;

    do
    {
        std::getline(this->input_file, line);
        this->current_line++;

        line = this->clean_command(line);

    } while (!this->input_file.eof() && line.size() == 0);

    command_found = (line.size() > 0) ? true : false;
    if (command_found) this->current_command = line;

    return command_found;
}

std::string Parser::clean_command(std::string command)
{
    size_t pos{ 0 };
    char current_char;

    while (pos < command.size())
    { // Remove leading space.
        current_char = command.at(pos);
        if (current_char != ' ') break;
        
        pos++;
    }

    command = command.substr(pos);
    pos = 0;

    while (pos + 1 < command.size())
    { // Remove comments.
        if (command.at(pos) == '/' && command.at(pos + 1) == '/') break;
        else pos++;
    }

    if (pos + 1 < command.size())
        command = command.substr(0, pos);

    return command;
}

uint8_t Parser::command_type()
{
    unsigned total_words(this->words_number());
    std::string command(this->current_command.substr(0, this->current_command.find(" "))); // First word.
    uint8_t command_type(Parser::INVALID_INS);

    if (is_al_command(command))
    {
        if (total_words != 1)
            this->error_message = "Error at line (" + std::to_string(this->current_line) + "): Arithmetic-logial command has too many arguments.";
        else
            command_type = Parser::C_ARITHMETIC;
    }

    else
        this->error_message = "Error at line (" + std::to_string(this->current_line) + "): Uknown command \"" + command + "\".";

    return command_type;
}

unsigned Parser::words_number()
{
    size_t pos = 0;
    unsigned total_words = 0;
    bool in_word = false;

    while (pos < this->current_command.size())
    {
        if (!in_word && this->current_command.at(pos) != ' ')
        {
            in_word = true;
            total_words++;
            pos++;
        }

        else if (in_word && this->current_command.at(pos) == ' ')
        {
            in_word = false;
            pos++;
        }

        else pos++;
    }

    return total_words;
}

bool Parser::is_al_command(std::string word)
{
    bool valid{ false };
    // Valid Arithmetic-Logical commands.
    const std::vector<std::string> valid_al_commands{
        "add",
        "sub",
        "neg",
        "eq",
        "gt",
        "lt",
        "and",
        "or",
        "not"
    };

    for (auto valid_al_command : valid_al_commands)
        if (word.compare(valid_al_command) == 0)
        {
            valid = true;
            break;
        }
    
    return valid;
}
