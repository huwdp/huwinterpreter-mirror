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

#include "fileexists.h"

FileExists::FileExists(std::shared_ptr<Passable> passable)
    : Function(passable)
{
    name = "fileExists";
}

std::shared_ptr<Variable> FileExists::execute(std::shared_ptr<Token> token, std::shared_ptr<Scope> globalScope,
                                        std::shared_ptr<Scope> scope,
                                        std::vector<std::shared_ptr<Node>> arguments)
{
    std::shared_ptr<Variable> returnNode = std::make_shared<NumberVariable>(passable, false);
    if (arguments.size() == 1)
    {
        IO file;
        std::shared_ptr<Node> fileLocation = arguments.at(0);
        if (fileLocation != nullptr)
        {
            std::shared_ptr<Variable> var = fileLocation->execute(globalScope, scope);
            if (var == nullptr)
            {
                passable->getErrors()->add(passable->getErrorFactory()->invalidArgument(token, RUNTIME_ERROR, name));
                return null;
            }

            if (file.fileExists(var->toString()))
            {
                returnNode = std::make_shared<NumberVariable>(passable, true);
            }
        }
        else
        {
            passable->getErrors()->add(passable->getErrorFactory()->invalidArgument(token, RUNTIME_ERROR, name));
            return null;
        }
    }
    else
    {
        passable->getErrors()->add(passable->getErrorFactory()->requiresArguments(token, name, "", 1));
    }
    return returnNode;
}
