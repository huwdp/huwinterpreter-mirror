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

namespace HuwInterpreter {
    namespace Tokens {
        Tokens::Tokens()
        {
            init();
        }

        void Tokens::init()
        {
            types.clear();
            types[Types::RIGHTPARENTHESIS] = ")";
            types[Types::LEFTPARENTHESIS] = "(";
            types[Types::MULTIPLICATION] = "*";
            types[Types::DIVISION] = "/";
            types[Types::SUBTRACTION] = "-";
            types[Types::MOD] = "%";
            types[Types::EQUALS] = "=";
            types[Types::IFEQUALS] = "==";
            types[Types::IFNOTEQUALS] = "!=";
            types[Types::IFLESSTHAN] = "<";
            types[Types::IFLESSTHANOREQUAL] = "<=";
            types[Types::IFGREATER] = ">";
            types[Types::IFGREATERTHANOREQUAL] = ">=";
            types[Types::LEFTBRACKET] = "{";
            types[Types::RIGHTBRACKET] = "}";
            types[Types::SEMICOLON] = ";";
            types[Types::COMMA] = ",";
            types[Types::QUOTE] = "\"";
            types[Types::DOT] = ".";
            types[Types::NOT] = "!";
            types[Types::ADDITION] = "+";
            types[Types::BITWISEAND] = "&";
            types[Types::BITWISEOR] = "|";
            types[Types::AND] = "&&";
            types[Types::OR] = "||";
            types[Types::MULTIPLICATIONEQUAL] = "*=";
            types[Types::DIVISIONEQUAL] = "/=";
            types[Types::ADDITIONEQUAL] = "+=";
            types[Types::SUBTRACTIONEQUAL] = "-=";
            types[Types::INCREMENT] = "++";
            types[Types::DECREMENT] = "--";
            types[Types::TABINDENTATION] = "\t";
            types[Types::INDENTATION] = " ";
            types[Types::BITWISEXOR] = "^";
            types[Types::BITWISECOMPLEMENT] = "~";
            types[Types::LEFTSQUAREBRACKET] = "[";
            types[Types::RIGHTSQUAREBRACKET] = "]";
        }

        std::string Tokens::get(Types::TokenType value)
        {
            return types[value];
        }

        Types::TokenType Tokens::get(std::string value)
        {
            for (std::unordered_map<ushort, std::string>::iterator it = types.begin(); it != types.end(); ++it)
            {
                if (it->second == value)
                {
                    return (Types::TokenType)it->first;
                }
            }
            return Types::WORD;
        }

        bool Tokens::compare(std::string value1, Types::TokenType value)
        {
            std::unordered_map<ushort, std::string>::const_iterator got = types.find(value);
            if (got != types.end())
            {
                if (got->second == value1)
                {
                    return true;
                }
            }
            return false;
        }

        bool Tokens::compare(char value1, Types::TokenType value)
        {
            std::stringstream ss;
            std::string temp;
            ss << value1;
            ss >> temp;
            return compare(temp, value);
        }

        bool Tokens::exists(Types::TokenType value)
        {
            return types.find(value) != types.end();
        }

        bool Tokens::exists(std::string value)
        {
            return std::find_if(types.begin(), types.end(),
                [value](const std::unordered_map<ushort, std::string>::value_type& item) { return item.second == value; }) != types.end();
        }

        void Tokens::add(std::string text, Types::TokenType tokenType)
        {
            if (!exists(tokenType))
            {
                types[tokenType] = text;
            }
        }
    }
}
