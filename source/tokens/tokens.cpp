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

#include "tokens.h"

Tokens::Tokens()
{
    init();
}

void Tokens::init()
{
    types.clear();
    types[RIGHTPARENTHESIS] = ")";
    types[LEFTPARENTHESIS] = "(";
    types[MULTIPLICATION] = "*";
    types[DIVISION] = "/";
    types[SUBTRACTION] = "-";
    types[MOD] = "%";
    types[EQUALS] = "=";
    types[IFEQUALS] = "==";
    types[IFNOTEQUALS] = "!=";
    types[IFLESSTHAN] = "<";
    types[IFLESSTHANOREQUAL] = "<=";
    types[IFGREATER] = ">";
    types[IFGREATERTHANOREQUAL] = ">=";
    types[LEFTBRACKET] = "{";
    types[RIGHTBRACKET] = "}";
    types[SEMICOLON] = ";";
    types[COMMA] = ",";
    types[QUOTE] = "\"";
    types[DOT] = ".";
    types[NOT] = "!";
    types[ADDITION] = "+";
    types[BITWISEAND] = "&";
    types[BITWISEOR] = "|";
    types[AND] = "&&";
    types[OR] = "||";
    types[MULTIPLICATIONEQUAL] = "*=";
    types[DIVISIONEQUAL] = "/=";
    types[ADDITIONEQUAL] = "+=";
    types[SUBTRACTIONEQUAL] = "-=";
    types[INCREMENT] = "++";
    types[DECREMENT] = "--";
    types[TABINDENTATION] = "\t";
    types[INDENTATION] = " ";
    types[BITWISEXOR] = "^";
}

std::string Tokens::get(TokenType value)
{
    return types[value];
}

TokenType Tokens::get(std::string value)
{
    for (std::unordered_map<ushort, std::string>::iterator it = types.begin(); it != types.end(); ++it)
    {
        if (it->second == value)
        {
            return (TokenType)it->first;
        }
    }
    return WORD;
}

bool Tokens::compare(std::string value1, TokenType value2)
{
    std::unordered_map<ushort, std::string>::const_iterator got = types.find(value2);
    if (got != types.end())
    {
        if (got->second == value1)
        {
            return true;
        }
    }
    return false;
}

bool Tokens::compare(char value1, TokenType value2)
{
    std::stringstream ss;
    std::string temp;
    ss << value1;
    ss >> temp;
    return compare(temp, value2);
}

bool Tokens::exists(TokenType value)
{
    return types.find(value) != types.end();
}

bool Tokens::exists(std::string value)
{
    return std::find_if(types.begin(), types.end(),
        [value](const std::unordered_map<ushort, std::string>::value_type& item) { return item.second == value; }) != types.end();
}

void Tokens::add(std::string text, TokenType tokenType)
{
    if (!exists(tokenType))
    {
        types[tokenType] = text;
    }
}
