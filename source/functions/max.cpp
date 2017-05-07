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

#include "max.h"

std::shared_ptr<Variable> Max::run(std::shared_ptr<Token> token,
                                   std::shared_ptr<Scope> scope,
                                   std::vector<std::shared_ptr<Node>> variables)
{
    std::shared_ptr<Variable> answer;
    if (variables.size() > 0)
    {
        double max = std::numeric_limits<double>::min();
        for (std::vector<std::shared_ptr<Node>>::iterator it = variables.begin(); it != variables.end(); it++)
        {
            std::shared_ptr<Variable> var = (*it).get()->execute(scope);
            try
            {
                double temp = var->toDouble();
                
                if (temp > max)
                {
                    max = temp;
                }
            }
            catch (const std::invalid_argument ex)
            {
                Errors::add(std::make_shared<Error>(FUNCTION_ERROR, "Invalid argument in Max", token));
            }
            catch (const std::out_of_range ex)
            {
                Errors::add(std::make_shared<Error>(FUNCTION_ERROR, "Out of range in Max", token));
            }
            catch (const std::exception& ex)
            {
                Errors::add(std::make_shared<Error>(FUNCTION_ERROR, ex.what(), token));
            }
            
        }
        answer = std::make_shared<FakeNumber>(max);
    }
    else
    {
        Errors::add(std::make_shared<Error>(FUNCTION_ERROR, "Max function requires at least two arguments", token));
    }

    return answer;
}

