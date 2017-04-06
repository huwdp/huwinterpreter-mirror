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

#include "round.h"

std::shared_ptr<Variable> Round::run(std::shared_ptr<Token> token, std::vector<std::shared_ptr<Node>> variables)
{
    std::shared_ptr<Variable> answer;
    if (variables.size() == 1)
    {
        Node *node = variables.at(0).get();
        std::shared_ptr<Variable> var = node->execute();
        if (var != nullptr)
        {
            try
            {
                double temp = var->toDouble();
                double output = std::round(temp);
                
                answer = std::make_shared<FakeNumber>(output);
            }
            catch (const std::invalid_argument ex)
            {
                Errors::add(std::make_shared<Error>(FUNCTION_ERROR, "Could not round", token));
            }
            catch (const std::out_of_range ex)
            {
                Errors::add(std::make_shared<Error>(FUNCTION_ERROR, "Out of range in Round", token));
            }
            catch (const std::exception& ex)
            {
                Errors::add(std::make_shared<Error>(FUNCTION_ERROR, ex.what(), token));
            }
        }
        
    }
    else
    {
        Errors::add(std::make_shared<Error>(FUNCTION_ERROR, "Round function requires one argument", token));

    }
    
    return answer;
}

