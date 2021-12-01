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
    this->current_command = "";
    
    // Tool for regex: https://regex101.com/

    do
    {
        std::getline(this->input_file, line);
    } while (&& !this->input_file.eof());
}