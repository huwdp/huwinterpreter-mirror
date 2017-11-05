/*
    HuwInterpreter is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    HuwInterpreter is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with HuwInterpreter.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "unusabletokens.h"

UnusableTokens::UnusableTokens()
{
    init();
    tokens = std::make_shared<Tokens>();
}

void UnusableTokens::init()
{
    items.clear();
    items.push_back(RIGHTPARENTHESIS);
    items.push_back(LEFTPARENTHESIS);
    items.push_back(MULTIPLICATION);
    items.push_back(DIVISION);
    items.push_back(SUBTRACTION);
    items.push_back(MOD);
    items.push_back(EQUALS);
    items.push_back(IFEQUALS);
    items.push_back(IFNOTEQUALS);
    items.push_back(IFLESSTHAN);
    items.push_back(IFLESSTHANOREQUAL);
    items.push_back(IFGREATER);
    items.push_back(IFGREATERTHANOREQUAL);
    items.push_back(LEFTBRACKET);
    items.push_back(RIGHTBRACKET);
    items.push_back(SEMICOLON);
    items.push_back(COMMA);
    items.push_back(QUOTE);
    items.push_back(NOT);
    items.push_back(LEFTPARENTHESIS);
    items.push_back(MULTIPLICATION);
    items.push_back(DIVISION);
    items.push_back(ADDITION);
    items.push_back(AND);
    items.push_back(OR);
    items.push_back(BITWISEAND);
    items.push_back(BITWISEOR);
    items.push_back(BITWISEXOR);
    items.push_back(DOT);
    items.push_back(MULTIPLICATIONEQUAL);
    items.push_back(DIVISIONEQUAL);
    items.push_back(ADDITIONEQUAL);
    items.push_back(SUBTRACTIONEQUAL);
    items.push_back(INCREMENT);
    items.push_back(DECREMENT);
    items.push_back(BITWISECOMPLEMENT);
}

bool UnusableTokens::tokenExists(TokenType tokenType)
{
    for (std::vector<TokenType>::iterator it = items.begin(); it != items.end(); ++it)
    {
        if ((*it) == tokenType)
        {
            return true;
        }
    }
    return false;
}

bool UnusableTokens::exists(std::string value)
{
    return tokenExists(tokens->get(value));
}

bool UnusableTokens::exists(char value)
{
    std::stringstream ss;
    std::string temp;
    ss << value;
    ss >> temp;
    return exists(temp);
}

void UnusableTokens::add(TokenType tokenType)
{
    if (!exists(tokenType))
    {
        items.push_back(tokenType);
    }
}





