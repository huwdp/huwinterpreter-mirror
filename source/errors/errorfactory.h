/*
    HuwInterpreter is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (std::shared_ptr<Token> token, at your option) any later version.

    HuwInterpreter is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with HuwInterpreter.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ERRORFACTORY_H
#define ERRORFACTORY_H

#include "error.h"
#include "variables/variablestringfactory.h"

namespace HuwInterpreter {
    namespace ErrorReporting {

        using namespace Tokens;
        using namespace Variables;

        class ErrorFactory
        {
        private:
            std::shared_ptr<VariableStringFactory> variableStringFactory;
        public:
            ErrorFactory();
            std::shared_ptr<Error> invalidArgument(std::shared_ptr<Token> token, ErrorTypes errorTypes, std::string name, std::string other);
            std::shared_ptr<Error> invalidArgument(std::shared_ptr<Token> token, ErrorTypes errorTypes, std::string name);
            std::shared_ptr<Error> outOfRange(std::shared_ptr<Token> token, std::string name, std::string other);
            std::shared_ptr<Error> requiresArguments(std::shared_ptr<Token> token, std::string name, std::string method, ulong arguments);
            std::shared_ptr<Error> firstParameterIsNotTypeOfArray(std::shared_ptr<Token> token, std::string varName, std::string funcName);
            std::shared_ptr<Error> requiresAtLeastXArguments(std::shared_ptr<Token> token, std::string name, ulong arguments);
            std::shared_ptr<Error> couldNotParseTime(std::shared_ptr<Token> token, std::string name);
            std::shared_ptr<Error> functionNotDeclared(std::shared_ptr<Token> token, std::string name);
            std::shared_ptr<Error> invalidExpression(ErrorTypes errorTypes, std::shared_ptr<Token> token, std::string name);
            std::shared_ptr<Error> variableNotDeclared(std::shared_ptr<Token> token, std::string name);
            std::shared_ptr<Error> constantNotDeclared(std::shared_ptr<Token> token, std::string className);
            std::shared_ptr<Error> failedToCompare(std::shared_ptr<Token> token, std::string method);
            std::shared_ptr<Error> failedToCompare(std::shared_ptr<Token> token, std::string method, std::string name, Types::VarType type1);
            std::shared_ptr<Error> failedToCompare(std::shared_ptr<Token> token, std::string method, std::string name, Types::VarType type1, Types::VarType type2);
            std::shared_ptr<Error> syntaxError(std::shared_ptr<Token> token, std::string info);
            std::shared_ptr<Error> couldNotConvertStringToNumber(std::shared_ptr<Token> token, std::string name, std::string method, std::string other);
            std::shared_ptr<Error> couldNotconvertNumberToInteger(std::shared_ptr<Token> token, std::string className, std::string method, std::string other);
            std::shared_ptr<Error> couldNotConvert(std::shared_ptr<Token> token, std::string name, std::string methodName, Types::VarType varType, std::string other);
            std::shared_ptr<Error> cannotCallFunction(std::shared_ptr<Token> token, Types::VarType varType, std::string name, std::string method, std::string other);
            std::shared_ptr<Error> cannotCallFunction(std::shared_ptr<Token> token, std::string name, Types::VarType varType, std::string method, std::string other);
            std::shared_ptr<Error> otherFunctionError(std::shared_ptr<Token> token, std::string name, std::string other);
            std::shared_ptr<Error> unmatchedSpecifiedNumberOfArguments(std::shared_ptr<Token> token, std::string name);
            std::shared_ptr<Error> outOfBounds(std::shared_ptr<Token> token, std::string name);
            std::shared_ptr<Error> variableDeclared(std::shared_ptr<Token> token, std::string name);
            std::shared_ptr<Error> constantDeclared(std::shared_ptr<Token> token, std::string name);

            std::shared_ptr<Error> cannotChangeConstant(std::shared_ptr<Token> token, std::string name);
            std::shared_ptr<Error> isNotAnArray(std::shared_ptr<Token> token, std::string name);
        };
    }
}

#endif // ERRORFACTORY_H
