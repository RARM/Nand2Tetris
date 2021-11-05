#include "Core.h"

std::string Core::dest(std::string mnemonic)
{
    std::string output;

    output = (mnemonic.find("A") != std::string::npos) ? "1" : "0";
    output += (mnemonic.find("D") != std::string::npos) ? "1" : "0";
    output += (mnemonic.find("M") != std::string::npos) ? "1" : "0";

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