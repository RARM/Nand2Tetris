#include "Parser.h"
#include <vector>

Parser::Parser(std::string input_filename)
    : current_command{ std::string("") }, input_file{ std::ifstream(input_filename) }, current_line{ 0 }, error_message{ "" }, current_command_words{}
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
    if (command_found)
    {
        this->current_command = line;
        this->split_command_words();
    }

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

void Parser::split_command_words()
{
    unsigned pos{ 0 };
    std::string word;
    bool in_word{ false };

    this->current_command_words.clear();
    
    while (pos < this->current_command.size())
    {
        if (!in_word && this->current_command.at(pos) != ' ')
        {
            in_word = true;
            word.push_back(this->current_command.at(pos++));
        }

        else if (in_word && this->current_command.at(pos) == ' ')
        {
            in_word = false;
            this->current_command_words.push_back(word);
            word.clear();
            pos++;
        }

        else if (in_word && this->current_command.at(pos) != ' ')
            word.push_back(this->current_command.at(pos++));

        else pos++;
    }

    this->current_command_words.push_back(word);
}

uint8_t Parser::command_type()
{
    uint8_t command_type(Parser::INVALID_INS);

    // Arithmetic-logic command.
    if (this->is_al_command())
        if (this->current_command_words.size() != 1)
            this->error_message = "Error at line (" + std::to_string(this->current_line) + "): Arithmetic-logial command has too many arguments.";
        else
            command_type = Parser::C_ARITHMETIC;

    // Push command.
    if (this->current_command_words.at(0) == "push")
        if (this->current_command_words.size() < 3)
            this->error_message = "Error at line (" + std::to_string(this->current_line) + "): Push command has too few arguments.";
        else if (this->current_command_words.size() > 3)
            this->error_message = "Error at line (" + std::to_string(this->current_line) + "): Push command has too many arguments.";
        else if (!this->has_valid_segment())
            this->error_message = "Error at line (" + std::to_string(this->current_line) + "): Push command has invalid segment \"" + this->current_command_words.at(1) + "\".";
        // else if () // Check range of the index.
        else
            command_type = Parser::C_PUSH;

    else
        this->error_message = "Error at line (" + std::to_string(this->current_line) + "): Uknown command \"" + this->current_command_words.at(0) + "\".";

    return command_type;
}

bool Parser::is_al_command()
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
        if (this->current_command_words.at(0).compare(valid_al_command) == 0)
        {
            valid = true;
            break;
        }
    
    return valid;
}

bool Parser::has_valid_segment()
{

}
