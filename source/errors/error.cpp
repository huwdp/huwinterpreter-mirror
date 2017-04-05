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

#include "error.h"

Error::Error()
{
    this->errorType = INFO;
    error = "";
    this->token = nullptr;
    this->internalFile = "";
    this->internalLine = 0;
}

Error::Error(ErrorTypes errorType, std::string error)
{
    this->errorType = errorType;
    this->error = error;
    this->token = nullptr;
    this->internalFile = "";
    this->internalLine = 0;
}

Error::Error(ErrorTypes errorType, std::string error, std::shared_ptr<Token> token)
{
    this->errorType = errorType;
    this->error = error;
    this->token = token;
    this->internalFile = "";
    this->internalLine = 0;
}

Error::Error(ErrorTypes errorType, std::string error, std::shared_ptr<Token> token, std::__cxx11::string internalFile, int internalLine)
{
    this->errorType = errorType;
    this->error = error;
    this->token = token;
    this->internalFile = internalFile;
    this->internalLine = internalLine;
}

std::string Error::getError()
{
    return error;
}

void Error::setError(std::string error)
{
    this->error = error;
}

std::string Error::getMessage()
{
    ErrorTypeStringFactory errorTypeStringFactory;
    std::string message = errorTypeStringFactory.createErrorString(errorType);
    message.append(": ");
    if (error != "")
    {
        message.append(error);
    }
    if (token != nullptr)
    {
        std::shared_ptr<LineInfo> lineInfo = token->getLineInfo();
        if (lineInfo != nullptr)
        {
            if (lineInfo.get()->getLineNumber() >= 0)
            {
                message.append(" on line ");
                message.append(std::to_string(lineInfo.get()->getLineNumber()));
            }
            if (lineInfo.get()->getCharNumber() > 0)
            {
                message.append(" on character");
                message.append(std::to_string(lineInfo.get()->getCharNumber()));
            }
        }
    }
    message.append(".");
    return message;
}
