#include "Parser.h"

Parser::Parser(std::string filename)
    : current_instruction { NULL }, input_file { std::ifstream(filename) }
{}

// bool Parser::has_more_lines()
// {
    // Is this method useless?
    // Please, read: http://nand2tetris-questions-and-answers-forum.52.s1.nabble.com/How-to-handle-comments-using-API-td4032033.html
    //
    // Thanks to the response by WBahn on how to correctly implement these methods.
    // Read: http://nand2tetris-questions-and-answers-forum.52.s1.nabble.com/hasMoreLines-and-advance-Methods-How-to-properly-implement-them-td4036441.html
    // 
    // I am removing has_more_lines() and advance(). I am making a new method find_next_instruction() that will perform the job of the previoys two methods.
// } 

// void Parser::advance()
// { }

bool Parser::find_next_instruction()
{
    std::string line;
    std::regex wsac("[\\t ]+|(\\/\\/.*)+"); // wsac = White Spaces And Comments
    // Regex for white space or comment: [\t ]+|(\/\/.*)+
    bool found_instruction;

    do
    {
        std::getline(this->input_file, line); // Read next line.
        line = std::regex_replace(line, wsac, ""); // Remove the white space.
    } while (!this->input_file.eof() && line.size() == 0);
    // Precedence: https://en.cppreference.com/w/cpp/language/operator_precedence

    if (line.size() == 0) found_instruction = false;
    else
    {
        found_instruction = true;
        this->current_instruction = line;
    }

    return found_instruction;
    //  Note for later optimizations. A valid A-instruction.
    // (@([0-9]+|([A-Za-z_.$:]+[A-Za-z_.$:0-9]*)+)){1}
}

Parser::~Parser()
{
    if (this->input_file.is_open()) this->input_file.close();
    return;
}

int Parser::instruction_type()
{
    return 0;
}

std::string Parser::symbol()
{
    return "";
}

std::string Parser::dest()
{
    return "";
}

std::string Parser::comp()
{
    return "";
}

std::string Parser::jump()
{
    return "";
}