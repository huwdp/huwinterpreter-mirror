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

#include "min.h"

Min::Min(std::shared_ptr<Passable> passable)
    : Function(passable)
{
    name = "min";
}

std::shared_ptr<Variable> Min::execute(std::shared_ptr<Token> token, std::shared_ptr<Scope> globalScope,
                                   std::shared_ptr<Scope> scope,
                                   std::vector<std::shared_ptr<Node>> arguments)
{
    std::shared_ptr<Variable> returnNode;
    if (arguments.size() > 1)
    {
        double min = std::numeric_limits<double>::max();
        for (std::vector<std::shared_ptr<Node>>::iterator it = arguments.begin(); it != arguments.end(); ++it)
        {
            if ((*it) != nullptr)
            {

                std::shared_ptr<Variable> var = (*it)->execute(globalScope, scope);
                if (var == nullptr)
                {
                    passable->errors->add(passable->errorFactory->invalidArgument(RUNTIME_ERROR, token, name));
                    return null;
                }

                try
                {
                    double temp = var->toDouble();
                    if (temp < min)
                    {
                        min = temp;
                    }
                }
                catch (const std::invalid_argument ex)
                {
                    passable->errors->add(passable->errorFactory->invalidArgument(FUNCTION_ERROR, token, name, ex.what()));
                }
                catch (const std::out_of_range ex)
                {
                    passable->errors->add(passable->errorFactory->outOfRange(token, name, ex.what()));
                }
                catch (const std::exception& ex)
                {
                    passable->errors->add(passable->errorFactory->otherFunctionError(token, name, "", ex.what()));
                }
            }
        }
        returnNode = std::make_shared<NumberVariable>(passable, min);
    }
    else
    {
        passable->errors->add(passable->errorFactory->requiresAtLeastXArguments(token, name, 2));
    }
    return returnNode;
}

