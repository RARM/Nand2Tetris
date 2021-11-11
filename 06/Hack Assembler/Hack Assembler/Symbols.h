#ifndef _SYMBOLS_H_
#define _SYMBOLS_H_

#include <map>
#include <string>

class Symbols
{
public:
	// Default constructor is used.

	// Adds <symbol,address> to the table.
	void addEntry(std::string symbol, unsigned address);
	
	// Does the symbol table contain the given symbol?
	bool contains(const std::string& symbol);
	
	// Returns the address associated with the symbol. It returns -1 if no address was found.
	int getAddress(const std::string& symbol);

private:
	std::map<std::string, unsigned> table;
};

#endif