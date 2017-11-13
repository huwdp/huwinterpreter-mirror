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

ErrorFactory::ErrorFactory()
{
    variableStringFactory = std::make_shared<VariableStringFactory>();
}

std::shared_ptr<Error> ErrorFactory::invalidArgument(std::shared_ptr<Token> token, ErrorTypes errorTypes, std::string name, std::string other)
{
    if (other.empty())
    {
        return std::make_shared<Error>(errorTypes, "Invalid argument in '" + name + "'.", token);
    }
    return std::make_shared<Error>(errorTypes, "Invalid argument in '" + name + "'." + other, token);
}

std::shared_ptr<Error> ErrorFactory::invalidArgument(std::shared_ptr<Token> token, ErrorTypes errorTypes, std::string name)
{
    return std::make_shared<Error>(errorTypes, "Invalid argument in '" + name + "'", token);
}

std::shared_ptr<Error> ErrorFactory::outOfRange(std::shared_ptr<Token> token, std::string name, std::string other)
{
    if (other.empty())
    {
        return std::make_shared<Error>(FUNCTION_ERROR, "Out of range in '" + name + "'", token);
    }
    return std::make_shared<Error>(FUNCTION_ERROR, "Out of range in '" + name + "'. " + other, token);
}

std::shared_ptr<Error> ErrorFactory::requiresArguments(std::shared_ptr<Token> token, std::string name, std::string method, ulong arguments)
{
    return std::make_shared<Error>(FUNCTION_ERROR, "'" + name + "' function requires " + std::to_string(arguments) + " argument", token);
}

std::shared_ptr<Error> ErrorFactory::firstParameterIsNotTypeOfArray(std::shared_ptr<Token> token, std::string varName, std::string funcName)
{
    return std::make_shared<Error>(FUNCTION_ERROR, varName + " variable is not an array" + " in '" + funcName + "'", token);
}

std::shared_ptr<Error> ErrorFactory::requiresAtLeastXArguments(std::shared_ptr<Token> token, std::string name, ulong arguments)
{
    return std::make_shared<Error>(FUNCTION_ERROR, "'" + name + "' function requires " + std::to_string(arguments) + " argument", token);
}

std::shared_ptr<Error> ErrorFactory::couldNotParseTime(std::shared_ptr<Token> token, std::string name)
{
    return std::make_shared<Error>(FUNCTION_ERROR, "Could not parse time in '" + name + "'", token);
}

std::shared_ptr<Error> ErrorFactory::functionNotDeclared(std::shared_ptr<Token> token, std::string name)
{
    return std::make_shared<Error>(RUNTIME_ERROR, "Function '" + name + "' not declared", token);
}

std::shared_ptr<Error> ErrorFactory::invalidExpression(ErrorTypes errorTypes, std::shared_ptr<Token> token, std::string name)
{
    return std::make_shared<Error>(RUNTIME_ERROR, "Invalid expression in '" + name + "'", token);
}

std::shared_ptr<Error> ErrorFactory::variableNotDeclared(std::shared_ptr<Token> token, std::string name)
{
    return std::make_shared<Error>(RUNTIME_ERROR, "Variable '" + name + "' not declared", token);
}

std::shared_ptr<Error> ErrorFactory::constantNotDeclared(std::shared_ptr<Token> token, std::string name)
{
    return std::make_shared<Error>(RUNTIME_ERROR, "Variable '" + name + "' not declared", token);
}

std::shared_ptr<Error> ErrorFactory::failedToCompare(std::shared_ptr<Token> token, std::string method)
{
    return std::make_shared<Error>(RUNTIME_ERROR, "Failed to compare in '" + method + "'",token);
}

std::shared_ptr<Error> ErrorFactory::failedToCompare(std::shared_ptr<Token> token, std::string method, std::string name, VarType type1)
{
    return std::make_shared<Error>(RUNTIME_ERROR, "Cannot compare variable '" + name + "' type of " + variableStringFactory->toString(type1) + " to null variable", token);
}

std::shared_ptr<Error> ErrorFactory::failedToCompare(std::shared_ptr<Token> token, std::string method, std::string name, VarType type1, VarType type2)
{
    return std::make_shared<Error>(RUNTIME_ERROR, method + " : Cannot compare variable '" + name + "' type of " + variableStringFactory->toString(type1) + " to " + variableStringFactory->toString(type2), token);
}

std::shared_ptr<Error> ErrorFactory::syntaxError(std::shared_ptr<Token> token, std::string info)
{
    return std::make_shared<Error>(PARSER_ERROR, "Syntax error: " + info, token);
}

std::shared_ptr<Error> ErrorFactory::couldNotConvertStringToNumber(std::shared_ptr<Token> token, std::string name, std::string method, std::string other)
{
    if (name.empty())
    {
        return std::make_shared<Error>(RUNTIME_ERROR, "Could not convert variable string to number", token);
    }
    return std::make_shared<Error>(RUNTIME_ERROR, "Could not convert variable '" + name + "' string to number", token);
}

std::shared_ptr<Error> ErrorFactory::couldNotConvert(std::shared_ptr<Token> token, std::string name, std::string methodName, VarType varType, std::string other)
{
    if (other.empty())
    {
        return std::make_shared<Error>(RUNTIME_ERROR, methodName + " could not convert variable '" + name + "' to " + variableStringFactory->toString(varType), token);
    }
    return std::make_shared<Error>(RUNTIME_ERROR, methodName + " could not convert variable '" + name + "' to " + variableStringFactory->toString(varType) + "." + other, token);
}

std::shared_ptr<Error> ErrorFactory::cannotCallFunction(std::shared_ptr<Token> token, std::string className, VarType varType, std::string method, std::string other)
{
    if (other.empty())
    {
        return std::make_shared<Error>(RUNTIME_ERROR, "Cannot call '" + method + "' method in '" + className + "' " +  variableStringFactory->toString(varType) + " variable", token);
    }
    return std::make_shared<Error>(RUNTIME_ERROR, "Cannot call '" + method + "' method in '" + className + "' " + variableStringFactory->toString(varType) + " variable. " + other, token);
}

std::shared_ptr<Error> ErrorFactory::otherFunctionError(std::shared_ptr<Token> token, std::string name, std::string other)
{
    return std::make_shared<Error>(FUNCTION_ERROR, "'" + name + "' :" + other, token);
}

std::shared_ptr<Error> ErrorFactory::unmatchedSpecifiedNumberOfArguments(std::shared_ptr<Token> token, std::string name)
{
    return std::make_shared<Error>(
        RUNTIME_ERROR,
        "Unmatched specified number of arguments",
        token
        );
}

std::shared_ptr<Error> ErrorFactory::outOfBounds(std::shared_ptr<Token> token, std::string name)
{
    return std::make_shared<Error>(RUNTIME_ERROR, "Out of bounds error in '" + name + "'", token);
}

std::shared_ptr<Error> ErrorFactory::variableDeclared(std::shared_ptr<Token> token, std::string name)
{
    return std::make_shared<Error>(RUNTIME_ERROR, "Variable '" + name + "' already declared", token);
}

std::shared_ptr<Error> ErrorFactory::constantDeclared(std::shared_ptr<Token> token, std::string name)
{
    return std::make_shared<Error>(RUNTIME_ERROR, "Constant '" + name + "' already declared", token);
}

std::shared_ptr<Error> ErrorFactory::cannotChangeConstant(std::shared_ptr<Token> token, std::string name)
{
    return std::make_shared<Error>(RUNTIME_ERROR, "Invalid assignment to const '" + name + "'", token);
}
