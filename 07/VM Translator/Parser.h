#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <fstream>

class Parser
{
public:
	// Opens the input file and gets it ready to parse it.
	Parser(std::string input_filename);
	~Parser();

	// bool hasMoreLines();
	// void advance();
	// Has it was done in chapter 06. These methods are being combined.
	// Read implementation of the Parser on the previous chapter for more information.

	// Loads the next command into current_command. Returns false when there are no more commands.
	bool find_next_command();

	// Returns a constant representing the intruction type of the current instruction.
	uint8_t command_type();

	// Instruction types.
	
	static constexpr uint8_t INVALID_INS = 0;
	static constexpr uint8_t C_ARITHMETIC = 1;
	static constexpr uint8_t C_PUSH = 2;
	static constexpr uint8_t C_POP = 3;
	static constexpr uint8_t C_LABEL = 4;
	static constexpr uint8_t C_GOTO = 5;
	static constexpr uint8_t C_IF = 6;
	static constexpr uint8_t C_FUNCTION = 7;
	static constexpr uint8_t C_RETURN = 8;
	static constexpr uint8_t C_CALL = 9;

	// Returns the first argument of the current command.
	std::string arg1();

	// Return the second argument of the current command.
	int arg2();

private:
	std::ifstream input_file;
	std::string current_command;
	unsigned current_line;
};

#endif