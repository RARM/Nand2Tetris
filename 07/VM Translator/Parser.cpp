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