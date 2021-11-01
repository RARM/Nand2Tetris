#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <fstream>

class Parser
{
public:
	// Constants static variables.
	
	static constexpr int A_INSTRUCTION = 0;
	static constexpr int C_INSTRUCTION = 1;
	static constexpr int L_INSTRUCTION = 2;
	
	// Constructor: provide input filename as argument.
	Parser(std::string filename);
	~Parser();

	// Returns true if there are more lines to process in the input file.
	bool has_more_lines();

	// Updates the current instruction.
	void advance();

	// Return the current instruction's type.
	int instruction_type();

	// Returns the symbol in the current instruction if it is an A or L instruction. It returns a blank string otherwise.
	std::string symbol();

	// Returns the dest part of the current instruction if it is a C instruction. It returns a blank string otherwise.
	std::string dest();

	// Returns the comp part of the current instruction if it is a C instruction. It returns a blank string otherwise.
	std::string comp();

	// Returns the jump part of the current instruction if it is a C instruction. It returns a blank string otherwise.
	std::string jump();

private:
	std::ifstream input_file;
	std::string current_instruction;
};



#endif
