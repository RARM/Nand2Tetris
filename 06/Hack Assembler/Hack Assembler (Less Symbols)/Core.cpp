#include "Core.h"

std::string Core::dest(std::string mnemonic)
{
    std::string output;

    output = (mnemonic.find("A") != std::string::npos) ? "1" : "0";
    output += (mnemonic.find("D") != std::string::npos) ? "1" : "0";
    output += (mnemonic.find("M") != std::string::npos) ? "1" : "0";

    return output;
}