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

#include "fileread.h"

FileRead::FileRead(std::shared_ptr<Passable> passable)
    : Function(passable)
{
    name = "fileRead";
}

std::shared_ptr<Variable> FileRead::run(std::shared_ptr<Token> token, std::shared_ptr<Scope> globalScope,
                                        std::shared_ptr<Scope> scope,
                                        std::vector<std::shared_ptr<Node>> variables)
{
    std::shared_ptr<Variable> returnNode;
    if (variables.size() == 1)
    {
        IO file;
        std::shared_ptr<Node> fileLocation = variables.at(0);
        if (fileLocation != nullptr)
        {
            std::shared_ptr<Variable> var = fileLocation->execute(globalScope, scope);
            if (var == nullptr)
            {
                passable->errors->add(passable->errorFactory->invalidArgument(RUNTIME_ERROR, token, name));
                return null;
            }

            std::string stream = file.read(var->toString());
            return std::make_shared<StringVariable>(passable, "",stream);
        }
        else
        {
            passable->errors->add(passable->errorFactory->invalidArgument(RUNTIME_ERROR, token, name));
            return null;
        }
    }
    else
    {
        passable->errors->add(passable->errorFactory->requiresArguments(token, name, "", 1));
    }
    return returnNode;
}
