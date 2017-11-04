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

Scan::Scan(std::shared_ptr<Passable> passable)
    : Function(passable)
{
    name = "scan";
}

std::shared_ptr<Variable> Scan::execute(std::shared_ptr<Token> token, std::shared_ptr<Scope> globalScope,
                                    std::shared_ptr<Scope> scope,
                                    std::vector<std::shared_ptr<Node>> variables)
{
    std::shared_ptr<Variable> returnNode;
    for (std::vector<std::shared_ptr<Node>>::iterator it = variables.begin(); it != variables.end(); ++it)
    {
        if ((*it) != nullptr)
        {
            std::shared_ptr<Node> node = (*it);
            if (node != nullptr)
            {
                std::shared_ptr<Variable> var = (*it)->execute(globalScope, scope);
                if (var == nullptr)
                {
                    passable->errors->add(passable->errorFactory->invalidArgument(RUNTIME_ERROR, token, name));
                    return null;
                }

                std::string input;
                std::cin >> input;
                var->setValue(input);
            }
            else
            {
                passable->errors->add(passable->errorFactory->invalidArgument(RUNTIME_ERROR, token, name));
                return null;
            }
        }
    }
    
    return returnNode;
}
