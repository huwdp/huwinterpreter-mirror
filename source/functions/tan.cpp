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

#include "tan.h"

Tan::Tan(std::shared_ptr<Passable> passable)
    : Function(passable)
{
    name = "tan";
}

std::shared_ptr<Variable> Tan::execute(std::shared_ptr<Token> token, std::shared_ptr<Scope> globalScope,
                                   std::shared_ptr<Scope> scope,
                                   std::vector<std::shared_ptr<Node>> arguments)
{
    std::shared_ptr<Variable> returnNode;
    if (arguments.size() == 1)
    {
        std::shared_ptr<Node> node = arguments.at(0);
        if (node == nullptr)
        {
            passable->getErrors()->add(passable->getErrorFactory()->invalidArgument(token, RUNTIME_ERROR, name));
            return null;
        }

        std::shared_ptr<Variable> var = node->execute(globalScope, scope);
        if (var == nullptr)
        {
            passable->getErrors()->add(passable->getErrorFactory()->invalidArgument(token, RUNTIME_ERROR, name));
            return null;
        }
        try
        {
            double temp = var->toDouble();
            double output = std::tan(temp);
            returnNode = std::make_shared<NumberVariable>(passable, output);
        }
        catch (const std::invalid_argument ex)
        {
            passable->getErrors()->add(passable->getErrorFactory()->invalidArgument(token, FUNCTION_ERROR, name, ex.what()));
        }
        catch (const std::out_of_range ex)
        {
            passable->getErrors()->add(passable->getErrorFactory()->outOfRange(token, name, ex.what()));
        }
        catch (const std::exception& ex)
        {
            passable->getErrors()->add(passable->getErrorFactory()->otherFunctionError(token, name, ex.what()));
        }
    }
    else
    {
        passable->getErrors()->add(passable->getErrorFactory()->requiresArguments(token, name, "", 1));
    }
    
    return returnNode;
}
