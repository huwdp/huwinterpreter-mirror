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

#ifndef STACKTRACE_H
#define STACKTRACE_H

#include <string>
#include <memory>
#include "../tokens/lineinfo.h"

namespace HuwInterpreter
{
    namespace ErrorReporting {
        class StackTrace
        {
        public:
            std::string functionName;
            std::shared_ptr<Tokens::LineInfo> lineInfo;
            StackTrace(std::string functionName, std::shared_ptr<Tokens::LineInfo> lineInfo);
            const std::string getFunctionName();
            void setFunctionName(std::string functionName);
            const std::shared_ptr<Tokens::LineInfo> getLineInfo();
            void setLineInfo(std::shared_ptr<Tokens::LineInfo> lineInfo);
            const std::string toString();
        };
    }
}

#endif // STACKTRACE_H
