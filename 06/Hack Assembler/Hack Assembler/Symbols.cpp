#include "Symbols.h"

void Symbols::addEntry(std::string symbol, unsigned address)
{
    // Structure binding unpacking used for managing the return values.
    // Read more about it here: https://subscription.packtpub.com/book/application-development/9781787120495/1/ch01lvl1sec10/using-structured-bindings-to-unpack-bundled-return-values
    // Possible subtition if I want to check if inserted.
    // const auto [iteratable_to_inserted, success] = this->table.insert({symbol, address});
    // The success variable would contain the bool to check if inserted correctly.
    this->table.insert({symbol, address});
    return;
}

bool Symbols::contains(const std::string& symbol)
{
    return this->table.contains(symbol);
}

int Symbols::getAddress(const std::string& symbol)
{
    // Read more here: https://en.cppreference.com/w/cpp/container/map/find
    const auto search = this->table.find(symbol);
    return (search != this->table.end()) ? search->second : -1;
}