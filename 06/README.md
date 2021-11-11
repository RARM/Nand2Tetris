# Project 06: The Assembler

I am going to implement the assembler using C++.

This project is organized as follows:
- `Test-Programs`: `.asm` programs provided by the course.
- `AssemblerL`: Contains implementation of the first stage of the assembler. This assembler translates assembly programs that **do not** contain symbols (Assembler Less Symbols).
- `Assembler`: Phase two implementation. This assembler translates assembly programs that **do** contain symbols.

Open the Hack Assembler solution in Visual Studio 2019 to view each project in detail.

Unit Testing: https://devblogs.microsoft.com/cppblog/cpp-testing-in-visual-studio/

## Extra Challenges
To implement...
- `AssemblerB`: (Extra) The previous assemblers translate Hack assembly code to a text file with the characters `0`, `1`, and the newline character only. This assembler translate the Hack assembly code to an actual binary file.

## Possible Optimizations
- Compilation speed could be improved.
    - Possible solution: create the symbol table in the first pass, use multi-threading for the second pass.
