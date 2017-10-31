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

#include "errorfactory.h"

std::shared_ptr<Error> ErrorFactory::invalidArgument(ErrorTypes errorTypes, std::shared_ptr<Token> token, std::string className, std::string other)
{
    return std::make_shared<Error>(errorTypes, "Invalid argument in " + className + "." + other, token);
}

std::shared_ptr<Error> ErrorFactory::invalidArgument(ErrorTypes errorTypes, std::shared_ptr<Token> token, std::string className)
{
    return std::make_shared<Error>(errorTypes, "Invalid argument in " + className, token);
}

std::shared_ptr<Error> ErrorFactory::outOfRange(std::shared_ptr<Token> token, std::string className, std::string other)
{
    return std::make_shared<Error>(FUNCTION_ERROR, "Out of range in Abs. " + other, token);
}

std::shared_ptr<Error> ErrorFactory::requiresArguments(std::shared_ptr<Token> token, std::string className, std::string method, ulong arguments)
{
    return std::make_shared<Error>(FUNCTION_ERROR, className + "function requires " + std::to_string(arguments) + " argument", token);
}

std::shared_ptr<Error> ErrorFactory::firstParameterIsNotTypeOfArray(std::shared_ptr<Token> token, std::string className, std::string method)
{
    return std::make_shared<Error>(FUNCTION_ERROR, "Invalid expression in " + className + " in " + method, token);
}

std::shared_ptr<Error> ErrorFactory::requiresAtLeastXArguments(std::shared_ptr<Token> token, std::string className, ulong arguments)
{
    return std::make_shared<Error>(FUNCTION_ERROR, className + " function requires " + std::to_string(arguments) + " argument", token);
}

std::shared_ptr<Error> ErrorFactory::couldNotParseTime(std::shared_ptr<Token> token, std::string className)
{
    return std::make_shared<Error>(FUNCTION_ERROR, "Could not parse time in " + className, token);
}

std::shared_ptr<Error> ErrorFactory::functionNotDeclared(std::shared_ptr<Token> token, std::string className)
{
    return std::make_shared<Error>(RUNTIME_ERROR, "Function " + className + "not declared", token);
}

std::shared_ptr<Error> ErrorFactory::invalidExpression(ErrorTypes errorTypes, std::shared_ptr<Token> token, std::string className)
{
    return std::make_shared<Error>(RUNTIME_ERROR, "", token);
}

std::shared_ptr<Error> ErrorFactory::variableNotDeclared(std::shared_ptr<Token> token, std::string className)
{
    return std::make_shared<Error>(RUNTIME_ERROR, "Variable not declared in " + className, token);
}

std::shared_ptr<Error> ErrorFactory::constantNotDeclared(std::shared_ptr<Token> token, std::string className)
{
    return std::make_shared<Error>(RUNTIME_ERROR, "Variable not declared", token);
}

std::shared_ptr<Error> ErrorFactory::failedToCompare(std::shared_ptr<Token> token, std::string className)
{
    return std::make_shared<Error>(RUNTIME_ERROR, "Failed to compare", token);
}

std::shared_ptr<Error> ErrorFactory::syntaxError(std::shared_ptr<Token> token, std::string info)
{
    return std::make_shared<Error>(PARSER_ERROR, "Syntax error: " + info, token);
}

std::shared_ptr<Error> ErrorFactory::couldNotConvertStringToNumber(std::shared_ptr<Token> token, std::string className, std::string method, std::string other)
{
    return std::make_shared<Error>(RUNTIME_ERROR, "Could not convert string to number", token);
}

std::shared_ptr<Error> ErrorFactory::couldNotConvertStringToNumber(std::string className, std::string method, std::string other)
{
    return std::make_shared<Error>(RUNTIME_ERROR, "Could not convert string to number. " + other);
}

std::shared_ptr<Error> ErrorFactory::couldNotconvertNumberToInteger(std::string className, std::string method, std::string other)
{
    return std::make_shared<Error>(RUNTIME_ERROR, "Could not convert number to integer");
}

std::shared_ptr<Error> ErrorFactory::couldNotConvert(std::shared_ptr<Token> token, std::string className, std::string method, std::string other)
{
    return std::make_shared<Error>(RUNTIME_ERROR, "", token);
}

std::shared_ptr<Error> ErrorFactory::cannotCallFunction(std::shared_ptr<Token> token, std::string className, std::string method, std::string other)
{
    return std::make_shared<Error>(RUNTIME_ERROR, "Cannot call " + method + " method in " + className, token);
}

std::shared_ptr<Error> ErrorFactory::cannotCallFunction(std::string className, std::string method, std::string other)
{
    return std::make_shared<Error>(RUNTIME_ERROR, "Cannot call " + method + " method in " + className);
}

std::shared_ptr<Error> ErrorFactory::otherFunctionError(std::shared_ptr<Token> token, std::string className, std::string method, std::string other)
{
    return std::make_shared<Error>(FUNCTION_ERROR, other, token);
}

std::shared_ptr<Error> ErrorFactory::unmatchedSpecifiedNumberOfArguments(std::shared_ptr<Token> token)
{
    return std::make_shared<Error>(
        RUNTIME_ERROR,
        "Unmatched specified number of arguments",
        token
        );
}

std::shared_ptr<Error> ErrorFactory::outOfBounds(std::string name)
{
    return std::make_shared<Error>(RUNTIME_ERROR, "Out of bounds error in " + name);
}

std::shared_ptr<Error> ErrorFactory::variableDeclared(std::shared_ptr<Token> token, std::string className, std::string name)
{
    return std::make_shared<Error>(RUNTIME_ERROR, "Variable " + name + " already declared" + " in " + className, token);
}

std::shared_ptr<Error> ErrorFactory::constantDeclared(std::shared_ptr<Token> token, std::string className, std::string name)
{
    return std::make_shared<Error>(RUNTIME_ERROR, "Constant " + name + " already declared" + " in " + className, token);
}
