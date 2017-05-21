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

#include "customfunction.h"

CustomFunction::CustomFunction(std::shared_ptr<Token> token, std::vector<std::string> arguments, std::shared_ptr<Node> block)
{
    this->arguments = arguments;
    this->block = block;
}

std::shared_ptr<Variable> CustomFunction::run(std::shared_ptr<Token> token,
                                              std::shared_ptr<Scope> scope,
                                              std::vector<std::shared_ptr<Node>> variables)
{

    // New scope
    std::shared_ptr<Scope> newScope = std::make_shared<Scope>();

    if (arguments.size() != variables.size())
    {
        Errors::add(
                    std::make_shared<Error>(
                        RUNTIME_ERROR,
                        "Unmatch specified number of arguments",
                        token
                        )
                    );
        return null;
    }

    // Clean code below: TODO
    std::vector<std::shared_ptr<Node>>::iterator variableIt = variables.begin();
    for (std::vector<std::string>::iterator argumentIt = arguments.begin(); argumentIt != arguments.end(); ++argumentIt)
    {
        newScope->getVariables()->addVariable((*argumentIt), (*variableIt)->execute(scope)->toString());
        ++variableIt;
    }

    if (block != nullptr)
    {
        std::shared_ptr<Variable> output = block->execute(newScope);

        // Remove arguments given from scope
        for (std::vector<std::string>::iterator it1 = arguments.begin(); it1 != arguments.end(); ++it1)
        {
            newScope->getVariables()->removeVariable((*it1));
        }
        return output;
    }
    return null;
}

