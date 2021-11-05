#ifndef _CORE_H_
#define _CORE_H_

#include <string>

class Core
{
public:
	// It returns the binary code (as a string) for the dest mnemonic.
	static std::string dest(std::string mnemonic);
	
	// It returns the binary code (as a string) for the comp mnemonic.
	static std::string comp(std::string mnemonic);
	
	// It returns the binary code (as a string) for the jump mnemonic.
	static std::string jump(std::string mnemonic);

	// It returns the binary code (as a string) of an integers less than 32,768 (15-bit).
	static std::string integer(std::string number);
};

#endif