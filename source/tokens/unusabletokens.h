#ifndef UNUSABLETOKENS_H
#define UNUSABLETOKENS_H

#include "types/tokentypes.h"
#include "tokens.h"
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <memory>

class UnusableTokens
{
private:
    std::vector<TokenType> items;
    std::shared_ptr<Tokens> tokens;
public:
    UnusableTokens();
    void init();
    bool tokenExists(TokenType tokenType);
    bool exists(std::string value);
    bool exists(char value);
    void add(TokenType tokenType);
};

#endif // UNUSABLETOKENS_H
