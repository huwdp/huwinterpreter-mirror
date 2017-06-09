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

#include "left.h"

std::shared_ptr<Variable> Left::run(std::shared_ptr<Token> token,
                                    std::shared_ptr<Scope> scope,
                                    std::vector<std::shared_ptr<Node>> variables)
{
    std::shared_ptr<Variable> answer;
    if (variables.size() == 2)
    {
        std::shared_ptr<Node> node1 = variables.at(0);
        std::shared_ptr<Node> node2 = variables.at(1);
        std::shared_ptr<Variable> var1 = node1->execute(scope);
        std::shared_ptr<Variable> var2 = node2->execute(scope);
        if (var1 != nullptr && var2 != nullptr)
        {
            std::string str = var1->toString();
            try
            {
                int position = std::round(var2->toDouble());
                str = str.substr(0, position);
                answer = std::make_shared<StringVariable>("", str);
            }
            catch (const std::invalid_argument ex)
            {
                Errors::add(std::make_shared<Error>(FUNCTION_ERROR, "Invalid argument in Left", token));
            }
            catch (const std::out_of_range ex)
            {
                Errors::add(std::make_shared<Error>(FUNCTION_ERROR, "Out of range in Left", token));
            }
            catch (const std::exception& ex)
            {
                Errors::add(std::make_shared<Error>(FUNCTION_ERROR, ex.what(), token));
            }
        }
    }
    else
    {
        Errors::add(std::make_shared<Error>(FUNCTION_ERROR, "Left function requires two arguments", token));
    }
    return answer;
}
