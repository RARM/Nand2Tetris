#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <fstream>
#include <regex>

class Parser
{
public:
	// Constants static variables.
	
	static constexpr int INVALID_INS = 0;
	static constexpr int A_INSTRUCTION = 1;
	static constexpr int C_INSTRUCTION = 2;
	static constexpr int L_INSTRUCTION = 3;
	
	// Constructor: provide input filename as argument.
	Parser(std::string filename);

	// Returns true if there are more lines to process in the input file.
	// bool has_more_lines();

	// Updates the current instruction.
	// void advance();

	// Read more about why did I delete these methods on the Parser.cpp file.

	// Returns true if it finds the next valid instruction. If it find one, then it makes it the current instruction.
	bool find_next_instruction();

	// Return the current instruction's type.
	int instruction_type();

	// Returns the symbol in the current instruction if it is an A or L instruction. It returns a blank string otherwise.
	std::string symbol();

	// Returns the dest part of the current instruction if it is a C instruction. It returns a blank string otherwise.
	std::string dest();

	// Returns the comp part of the current instruction. This is found by removing the jump and dest instructions, so there may be a return value even if the current instruction is not a C instruction.
	std::string comp();

	// Returns the jump part of the current instruction if it is a C instruction. It returns a blank string otherwise.
	std::string jump();

	// ----- Some extra functions. Getters.

	// Is input file open? Returns true if so.
	bool is_open();

	// Returns current instruction.
	std::string get_instruction();

private:
	std::ifstream input_file;
	std::string current_instruction;
};



#endif
