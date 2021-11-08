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

std::string Core::integer(std::string number)
{
    std::string output("");
    int int_num(std::stoi(number));

    if (int_num < 32768)
        for (int i = 14; i >= 0; i--) // For 15 bit.
            output += ((int_num >> i) & 0x0001) ? "1" : "0";
    else output = "000000000000000"; // 15 bits of 0 if invalid integer.

    return output;
}