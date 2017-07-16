#ifndef UNUSABLETOKENS_H
#define UNUSABLETOKENS_H

#include "types/tokentypes.h"
#include <unordered_map>
#include <algorithm>

class UnusableTokens
{
private:
    std::unordered_map<std::string, TokenType> items;
public:
    UnusableTokens();
    void init();
    bool exists(TokenType tokenType);
    bool exists(std::string text);
    bool exists(char character);
    void add(TokenType tokenType, std::string text);
};

#endif // UNUSABLETOKENS_H
