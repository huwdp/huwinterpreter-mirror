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

#include "tokendetector.h"

void TokenDetector::init()
{

}

TokenDetector::TokenDetector()
{
    types[")"] = TokenType::RIGHTPARENTHESIS;
    types["("] = TokenType::LEFTARENTHESIS;
    types["*"] = TokenType::MULTIPLICATION;
    types["/"] = TokenType::DIVISION;
    types["+"] = TokenType::ADDITION;
    types["-"] = TokenType::SUBTRACTION;
    types["%"] = TokenType::MOD;
    types["="] = TokenType::EQUALS;
    types["=="] = TokenType::IFEQUALS;
    types["!="] = TokenType::IFNOTEQUALS;
    types["<"] = TokenType::IFLESSTHAN;
    types["<="] = TokenType::IFLESSTHANOREQUAL;
    types[">"] = TokenType::IFGREATER;
    types[">="] = TokenType::IFGREATERTHANOREQUAL;
    types["{"] = TokenType::LEFTBRACKET;
    types["}"] = TokenType::RIGHTBRACKET;
    types[";"] = TokenType::SEMICOLON;
    types[","] = TokenType::COMMA;
    types["\""] = TokenType::QUOTE;
    types["."] = TokenType::DOT;
    types["!"] = TokenType::NOT;
}

std::string TokenDetector::getString(TokenType token)
{
    for (std::unordered_map<std::string, TokenType>::iterator it = types.begin(); it != types.end(); ++it)
    {
        if (it->second == token)
        {
            return it->first;
        }
    }
    return "";
}

TokenType TokenDetector::getToken(std::string value)
{
    return types[value];
}

bool TokenDetector::compare(std::string value1, TokenType value2)
{
    std::unordered_map<std::string,TokenType>::const_iterator got = types.find(value1);
    if (got != types.end())
    {
        if (got->second == value2)
        {
            return true;
        }
    }
    return false;
}

bool TokenDetector::compare(char value1, TokenType value2)
{
    std::stringstream ss;
    std::string temp;
    ss << value1;
    ss >> temp;
    return compare(temp, value2);
}
