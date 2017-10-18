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

#include "filewrite.h"

FileWrite::FileWrite(std::shared_ptr<Passable> passable)
    : Function(passable)
{
    name = "fileWrite";
}

std::shared_ptr<Variable> FileWrite::run(std::shared_ptr<Token> token,
                                         std::shared_ptr<Scope> scope,
                                         std::vector<std::shared_ptr<Node>> variables)
{
    std::shared_ptr<Variable> returnNode;
    if (variables.size() == 2)
    {
        std::shared_ptr<Node> node1 = variables.at(0);
        std::shared_ptr<Node> node2 = variables.at(1);
        if (node1 != nullptr && node2 != nullptr)
        {
            std::shared_ptr<Variable> var1 = node1->execute(scope);
            std::shared_ptr<Variable> var2 = node2->execute(scope);

            if (var1 == nullptr || var2 == nullptr)
            {
                passable->errors->add(passable->errorFactory->invalidArgument(RUNTIME_ERROR, token, name));
                returnNode = std::make_shared<NumberVariable>(passable, 0.0);
            }

            std::string fileLocation = var1->toString();
            std::string output = var2->toString();
            IO file;
            if (file.write(fileLocation, output))
            {
                returnNode = std::make_shared<NumberVariable>(passable, 1.0);
            }
        }
        else
        {
            passable->errors->add(passable->errorFactory->invalidArgument(RUNTIME_ERROR, token, name));
            returnNode = std::make_shared<NumberVariable>(passable, 0.0);
        }
    }
    else
    {
        passable->errors->add(passable->errorFactory->requiresArguments(token, name, "", 2));
    }
    return returnNode;
}
