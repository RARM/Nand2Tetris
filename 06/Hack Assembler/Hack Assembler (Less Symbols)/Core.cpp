#include "Core.h"

std::string Core::dest(std::string mnemonic)
{
    std::string output;

    output = (mnemonic.find("A") != std::string::npos) ? "1" : "0";
    output += (mnemonic.find("D") != std::string::npos) ? "1" : "0";
    output += (mnemonic.find("M") != std::string::npos) ? "1" : "0";

    return output;
}

std::string Core::comp(std::string mnemonic)
{
    std::string output;

    // Brute force.
    if (mnemonic == "0") output = "101010";
    else if (mnemonic == "1") output = "111111";
    else if (mnemonic == "-1") output = "111010";
    else if (mnemonic == "D") output = "001100";
    else if (mnemonic == "A" || mnemonic == "M") output = "110000";
    else if (mnemonic == "!D") output = "001101";
    else if (mnemonic == "!A" || mnemonic == "!M") output = "110001";
    else if (mnemonic == "-D") output = "001111";
    else if (mnemonic == "-A" || mnemonic == "-M") output = "110011";
    else if (mnemonic == "D+1") output = "011111";
    else if (mnemonic == "A+1" || mnemonic == "M+1") output = "110111";
    else if (mnemonic == "D-1") output = "001110";
    else if (mnemonic == "A-1" || mnemonic == "M-1") output = "110010";
    else if (mnemonic == "D+A" || mnemonic == "D+M") output = "000010";
    else if (mnemonic == "D-A" || mnemonic == "D-M") output = "010011";
    else if (mnemonic == "A-D" || mnemonic == "M-D") output = "000111";
    else if (mnemonic == "D&A" || mnemonic == "D&M") output = "000000";
    else if (mnemonic == "D|A" || mnemonic == "D|M") output = "010101";
    else output = "000000"; // Returns  D&A if not valid instruction is found?

    output = ((mnemonic.find("M") == std::string::npos) ? "0" : "1") + output;

    return output;
}

std::string Core::jump(std::string mnemonic)
{
    std::string output;

    if (mnemonic == "JGT") output = "001";
    else if (mnemonic == "JEQ") output = "010";
    else if (mnemonic == "JGE") output = "011";
    else if (mnemonic == "JLT") output = "100";
    else if (mnemonic == "JNE") output = "101";
    else if (mnemonic == "JLE") output = "110";
    else if (mnemonic == "JMP") output = "111";
    else output = "000";

    return output;
}