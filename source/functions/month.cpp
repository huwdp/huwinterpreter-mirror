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

#include "month.h"

Month::Month(std::shared_ptr<Passable> passable)
    : Function(passable)
{
    name = "month";
}

std::shared_ptr<Variable> Month::execute(std::shared_ptr<Token> token, std::shared_ptr<Scope> globalScope,
                                     std::shared_ptr<Scope> scope,
                                     std::vector<std::shared_ptr<Node>> arguments)
{
    std::shared_ptr<Variable> returnNode;
    if (arguments.size() == 1)
    {
        std::shared_ptr<Node> node = arguments.at(0);
        if (node == nullptr)
        {
            passable->errors->add(passable->errorFactory->invalidArgument(token, RUNTIME_ERROR, name));
            return null;
        }

        std::shared_ptr<Variable> var = node->execute(globalScope, scope);
        if (var == nullptr)
        {
            passable->errors->add(passable->errorFactory->invalidArgument(token, RUNTIME_ERROR, name));
            return null;
        }

        try
        {
            double d = var->toDouble();
            long value = (long)d;
            std::time_t t = (int)value;
            std::tm tm = *std::localtime(&t);
            std::stringstream ss;
            ss << std::put_time(&tm, "%m");
            returnNode = std::make_shared<StringVariable>(passable, "", ss.str());
        }
        catch (const std::invalid_argument ex)
        {
            passable->errors->add(passable->errorFactory->invalidArgument(token, FUNCTION_ERROR, name, ex.what()));
        }
        catch (const std::out_of_range ex)
        {
            passable->errors->add(passable->errorFactory->outOfRange(token, name, ex.what()));
        }
        catch (const std::exception& ex)
        {
            passable->errors->add(passable->errorFactory->otherFunctionError(token, name, ex.what()));
        }
    }
    else
    {
        passable->errors->add(passable->errorFactory->requiresArguments(token, name, "", 1));
    }
    
    return returnNode;
}
