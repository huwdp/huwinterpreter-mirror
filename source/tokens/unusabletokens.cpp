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

namespace HuwInterpreter {
    namespace Tokens {
        UnusableTokens::UnusableTokens()
        {
            init();
            tokens = std::make_shared<Tokens>();
        }

        void UnusableTokens::init()
        {
            items.clear();
            items.push_back(Types::RIGHTPARENTHESIS);
            items.push_back(Types::LEFTPARENTHESIS);
            items.push_back(Types::MULTIPLICATION);
            items.push_back(Types::DIVISION);
            items.push_back(Types::SUBTRACTION);
            items.push_back(Types::MOD);
            items.push_back(Types::EQUALS);
            items.push_back(Types::IFEQUALS);
            items.push_back(Types::IFNOTEQUALS);
            items.push_back(Types::IFLESSTHAN);
            items.push_back(Types::IFLESSTHANOREQUAL);
            items.push_back(Types::IFGREATER);
            items.push_back(Types::IFGREATERTHANOREQUAL);
            items.push_back(Types::LEFTBRACKET);
            items.push_back(Types::RIGHTBRACKET);
            items.push_back(Types::SEMICOLON);
            items.push_back(Types::COMMA);
            items.push_back(Types::QUOTE);
            items.push_back(Types::NOT);
            items.push_back(Types::LEFTPARENTHESIS);
            items.push_back(Types::MULTIPLICATION);
            items.push_back(Types::DIVISION);
            items.push_back(Types::ADDITION);
            items.push_back(Types::AND);
            items.push_back(Types::OR);
            items.push_back(Types::BITWISEAND);
            items.push_back(Types::BITWISEOR);
            items.push_back(Types::BITWISEXOR);
            items.push_back(Types::DOT);
            items.push_back(Types::MULTIPLICATIONEQUAL);
            items.push_back(Types::DIVISIONEQUAL);
            items.push_back(Types::ADDITIONEQUAL);
            items.push_back(Types::SUBTRACTIONEQUAL);
            items.push_back(Types::INCREMENT);
            items.push_back(Types::DECREMENT);
            items.push_back(Types::BITWISECOMPLEMENT);
            items.push_back(Types::LEFTSHIFT);
        }

        bool UnusableTokens::tokenExists(Types::TokenType tokenType)
        {
            for (std::vector<Types::TokenType>::iterator it = items.begin(); it != items.end(); ++it)
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

        void UnusableTokens::add(Types::TokenType tokenType)
        {
            if (!exists(tokenType))
            {
                items.push_back(tokenType);
            }
        }
    }
}
