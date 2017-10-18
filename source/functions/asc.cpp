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

#include "asc.h"

Asc::Asc(std::shared_ptr<Passable> passable)
    : Function(passable)
{
    name = "asc";
}

std::shared_ptr<Variable> Asc::run(std::shared_ptr<Token> token,
                                   std::shared_ptr<Scope> scope,
                                   std::vector<std::shared_ptr<Node>> variables)
{
    std::shared_ptr<Variable> returnNode;
    if (variables.size() == 1)
    {
        std::shared_ptr<Node> node = variables.at(0);
        if (node == nullptr)
        {
            passable->errors->add(passable->errorFactory->invalidArgument(RUNTIME_ERROR, token, name));
            return null;
        }

        std::shared_ptr<Variable> var = node->execute(scope);
        if (var == nullptr)
        {
            passable->errors->add(passable->errorFactory->invalidArgument(RUNTIME_ERROR, token, name));
            return null;
        }

        std::string temp = var->toString();
        if (temp.size() == 1)
        {
            int temp2 = temp.at(0);
            double ascii = (double)temp2;
            returnNode = std::make_shared<NumberVariable>(passable, ascii);
        }
    }
    else
    {
        returnNode = std::make_shared<StringVariable>(passable);
        passable->errors->add(passable->errorFactory->requiresArguments(token, name, "", 1));
    }
    
    return returnNode;
}

