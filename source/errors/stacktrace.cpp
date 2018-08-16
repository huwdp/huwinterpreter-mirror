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

#include "stacktrace.h"

namespace HuwInterpreter {
    namespace ErrorReporting {
        StackTrace::StackTrace(std::string functionName, std::shared_ptr<Tokens::LineInfo> lineInfo)
        {
            this->functionName = functionName;
            this->lineInfo = lineInfo;
        }

        const std::string StackTrace::getFunctionName()
        {
            return functionName;
        }

        void StackTrace::setFunctionName(std::string functionName)
        {
            this->functionName = functionName;
        }

        const std::shared_ptr<Tokens::LineInfo> StackTrace::getLineInfo()
        {
            return lineInfo;
        }

        void StackTrace::setLineInfo(std::shared_ptr<Tokens::LineInfo> lineInfo)
        {
            this->lineInfo = lineInfo;
        }

        const std::string StackTrace::toString()
        {
            std::string message = functionName;
            if (lineInfo != nullptr)
            {
                if (lineInfo->getLineNumber() >= 0)
                {
                    message.append(" at line number ");
                    message.append(std::to_string(lineInfo->getLineNumber()));
                }
                if (lineInfo->getCharNumber() > 0)
                {
                    message.append(" on character");
                    message.append(std::to_string(lineInfo->getCharNumber()));
                }
            }
            return message;
        }
    }
}
