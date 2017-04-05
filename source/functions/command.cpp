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

#include "command.h"

std::shared_ptr<Variable> Command::run(std::shared_ptr<Token> token, std::vector<std::shared_ptr<Node>> variables)
{
    std::shared_ptr<Variable> answer;
    if (variables.size() == 0)
    {
        Debug::print("Command function requires at least 1 argument");
        Errors::add(std::make_shared<Error>(FUNCTION_ERROR, "Commands function requires at least one argument", token));
        std::shared_ptr<Variable> null;
        return null;
    }
    for (std::vector<std::shared_ptr<Node>>::iterator it = variables.begin(); it != variables.end(); ++it)
    {
        if ((*it).get() != nullptr)
        {
            std::shared_ptr<Variable> var = (*it)->execute();
            if (var != nullptr)
            {
                system(var.get()->toString().c_str());
            }
        }
    }
    return answer;
}