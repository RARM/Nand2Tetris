// Hack Assembler Less Symbol - This is phase one of the Hack Assembler project.
#include <iostream>
#include <string>
#include <fstream>

int main(int argc, const char* argv[])
{
    std::cout << "Arguments passed to this programs: ";
    for (int i{ 1 }; i < argc; i++)
        std::cout << argv[i] << " ";
    std::cout << std::endl;

    std::ofstream f0(argv[1]);

    f0 << "This is the sample output file.";

    f0.close();

    return 0;
}