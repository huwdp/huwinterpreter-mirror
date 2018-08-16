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

#include "errortypestringfactory.h"

namespace HuwInterpreter {
    namespace ErrorReporting {
        ErrorTypeStringFactory::ErrorTypeStringFactory()
        {}

        std::string ErrorTypeStringFactory::createErrorString(ErrorTypes errorTypes)
        {
            switch (errorTypes)
            {
                case ERROR:
                    return "ERROR";
                case WARNING:
                    return "WARNING";
                case INFO:
                    return "INFO";
                case FUNCTION_ERROR:
                    return "FUNCTION_ERROR";
                case PARSER_ERROR:
                    return "PARSER_ERROR";
                case STATEMENT_ERROR:
                    return "STATEMENT_ERROR";
                case RUNTIME_ERROR:
                    return "RUNTIME_ERROR";
                default:
                    return "UNKNOWN ERROR";
            }
        }
    }
}
