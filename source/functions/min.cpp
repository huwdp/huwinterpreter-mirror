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

std::shared_ptr<Variable> Min::run(std::shared_ptr<Token> token,
                                   std::shared_ptr<Scope> scope,
                                   std::vector<std::shared_ptr<Node>> variables)
{
    std::shared_ptr<Variable> returnNode;
    if (variables.size() > 1)
    {
        double min = std::numeric_limits<double>::max();
        for (std::vector<std::shared_ptr<Node>>::iterator it = variables.begin(); it != variables.end(); ++it)
        {
            std::shared_ptr<Variable> var = (*it)->execute(scope);
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
                passable->errors->add(std::make_shared<Error>(FUNCTION_ERROR, "Invalid argument in Min", token));
            }
            catch (const std::out_of_range ex)
            {
                passable->errors->add(std::make_shared<Error>(FUNCTION_ERROR, "Out of range in Min", token));
            }
            catch (const std::exception& ex)
            {
                passable->errors->add(std::make_shared<Error>(FUNCTION_ERROR, ex.what(), token));
            }
            
        }
        returnNode = std::make_shared<NumberVariable>(passable, min);
    }
    else
    {
        passable->errors->add(std::make_shared<Error>(FUNCTION_ERROR, "Max function requires at least two arguments", token));
    }
    
    return returnNode;
}

