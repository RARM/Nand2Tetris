#include "Parser.h"

Parser::Parser(std::string filename)
    : current_instruction { NULL }, input_file { std::ifstream(filename) }
{}

Parser::~Parser()
{
    if (this->input_file.is_open()) this->input_file.close();
    return;
}

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
    const std::regex wsac("[\\t ]+|(\\/\\/.*)+"); // wsac = White Spaces And Comments
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
}

int Parser::instruction_type()
{
    const std::regex a_ins("(@([0-9]+|([A-Za-z_.$:]+[A-Za-z_.$:0-9]*)+)){1}"); // Regex that matches an A-Instruction.
    const std::regex label("\\(([0-9]+|([A-Za-z_.$:]+[A-Za-z_.$:0-9]*)+){1}\\)"); // Label.
    const std::regex c_ins("A?D?M?=?[ADM01\\-!+&|]{1,3};?[JGTEQLNMP]{0,3}"); // C_Instruction <- This regex could be improved.
    
    int ins_type;

    if (std::regex_match(this->current_instruction, a_ins)) ins_type = Parser::A_INSTRUCTION;
    else if (std::regex_match(this->current_instruction, label)) ins_type = Parser::L_INSTRUCTION;
    else if (std::regex_match(this->current_instruction, c_ins)) ins_type = Parser::C_INSTRUCTION;
    else ins_type = Parser::INVALID_INS;
    
    return ins_type;
}

std::string Parser::symbol()
{
    std::string symb_found;
    const std::regex symb_regx("\\(([0-9]+|([A-Za-z_.$:]+[A-Za-z_.$:0-9]*)+){1}\\)"); // A valid label.
    const std::regex par("\\(|\\)"); // Parentheses.
    std::smatch match_found;

    std::regex_search(this->current_instruction, match_found, symb_regx);

    if (!match_found.empty())
    {
        symb_found = match_found.str();
        symb_found = std::regex_replace(symb_found, par, ""); // Removing parentheses.
    }
    else symb_found = "";
    
    return symb_found;
}

std::string Parser::dest()
{
    std::string dest_found;
    const std::regex dest_regx(";[JGTEQLNMP]{3}"); // The JUMP instruction.
    std::smatch match_found;

    std::regex_search(this->current_instruction, match_found, dest_regx);

    if (!match_found.empty())
    {
        dest_found = match_found.str();
        dest_found = std::regex_replace(dest_found, std::regex(";"), ""); // Removing colon.
    }
    else dest_found = "";

    return dest_found;
}

std::string Parser::comp()
{
    return "";
}

std::string Parser::jump()
{
    return "";
}