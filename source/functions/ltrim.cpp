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

#include "ltrim.h"

std::shared_ptr<Variable> LTrim::run(std::shared_ptr<Token> token, std::vector<std::shared_ptr<Node>> variables)
{
    std::shared_ptr<Variable> answer;
    if (variables.size() == 1)
    {
        Node *node = variables.at(0).get();
        std::shared_ptr<Variable> var = node->execute();
        if (var != nullptr)
        {
            std::string temp = var->toString();
            
            std::string::iterator it = temp.begin();
            while(it != temp.end())
            {
                if ((*it) != ' ' && (*it) != '\t')
                {
                    break;
                }
                else
                {
                    temp.erase(it);
                    it--;
                }
                ++it;
            }
            answer = std::make_shared<FakeString>("", temp);
        }
    }
    else
    {
        Errors::add(std::make_shared<Error>(FUNCTION_ERROR, "LTrim function requires one argument", token));
    }

    return answer;
}
