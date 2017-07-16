#ifndef TOKENMAP_H
#define TOKENMAP_H

#include <unordered_map>
#include <algorithm>
#include "types/tokentypes.h"

class Tokens
{
private:
    std::unordered_map<std::string, TokenType> items;
public:
    Tokens();
    void init();
    bool exists(TokenType tokenType);
    bool exists(std::string text);
    void add(TokenType tokenType, std::string text);
};

#endif // TOKENMAP_H
