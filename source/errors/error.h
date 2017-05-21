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

#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <iostream>
#include <vector>
#include "tokens/token.h"
#include "errortypes.h"
#include "errortypestringfactory.h"

class Error
{
private:
    std::string error;
    std::shared_ptr<Token> token;
    std::string internalFile;
    int internalLine;
    ErrorTypes errorType;
public:
    Error();
    Error(ErrorTypes errorTypes, std::string error);
    Error(ErrorTypes errorTypes, std::string error, std::shared_ptr<Token> token);
    Error(ErrorTypes errorTypes, std::string error, std::shared_ptr<Token> token, std::string internalFile, int internalLine);
    std::string getError();
    void setError(std::string error);
    std::string getMessage();
};

#endif // ERROR_H
