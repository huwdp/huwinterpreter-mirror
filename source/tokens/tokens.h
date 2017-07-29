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

#ifndef TOKENDETECTOR_H
#define TOKENDETECTOR_H

#include <unordered_map>
#include <string>
#include <sstream>
#include "types/tokentypes.h"
#include <algorithm>

class Tokens
{
private:
    std::unordered_map<ushort, std::string> types;
public:
    Tokens();
    void init();
    std::string get(TokenType value);
    TokenType get(std::string value);
    bool compare(std::string value1, TokenType value2);
    bool compare(char value1, TokenType value2);
    bool exists(TokenType value);
    bool exists(std::string value);
    void add(std::string text, TokenType tokenType);
};

#endif // TOKENDETECTOR_H
