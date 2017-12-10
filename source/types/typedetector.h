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

#ifndef TYPEDETECTOR_H
#define TYPEDETECTOR_H

#include <string>
#include <stdexcept>
#include <sstream>
#include "tokentypes.h"

namespace  HuwInterpreter {

    using namespace Types;

    namespace  Helpers {
        class TypeDetector
        {
        public:
            static bool isInteger(std::string value);
            static bool isInteger(char value);
            static bool isNumeric(std::string value);
            static bool isNumeric(char value);
            static bool isWord(std::string value);
            static bool isWord(char value);
            static VarType getType(std::string value);
            static VarType getToken(std::string value);
            static bool compare(std::string value1, TokenType value2);
        };
    }
}

#endif // TYPEDETECTOR_H
