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

#include "variablestringfactory.h"

namespace HuwInterpreter {
    namespace Variables {
        std::string VariableStringFactory::toString(Types::VarType  varType)
        {
            std::string result;
            switch (varType)
            {
            case Types::INTEGER:
                    result = "integer";
                    break;
            case Types::DOUBLE:
                result = "double";
                break;
            case Types::ARRAY:
                result = "array";
                break;
            case Types::STRING:
                result = "string";
                break;
            case Types::NONE:
                result = "none";
                break;
            default:
                result = "";
                break;
            }
            return result;
        }
}
}
