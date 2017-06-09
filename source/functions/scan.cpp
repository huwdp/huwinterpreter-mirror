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

#include "scan.h"

std::shared_ptr<Variable> Scan::run(std::shared_ptr<Token> token,
                                    std::shared_ptr<Scope> scope,
                                    std::vector<std::shared_ptr<Node>> variables)
{
    std::shared_ptr<Variable> answer;
    for (std::vector<std::shared_ptr<Node>>::iterator it = variables.begin(); it != variables.end(); ++it)
    {
        if ((*it) != nullptr)
        {
            std::shared_ptr<Node> node = (*it);
            std::shared_ptr<Variable> var = (*it)->execute(scope);
            if (var != nullptr)
            {
                std::shared_ptr<Variable> var = node->execute(scope);
                std::string input;
                std::cin >> input;
                var->setValue(input);
            }
            
        }
    }
    
    return answer;
}
