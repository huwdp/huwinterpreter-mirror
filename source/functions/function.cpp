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

#include "function.h"

std::string Function::getName()
{
    return name;
}

void Function::setName(std::string name)
{
    this->name = name;
}

std::string Function::toString(std::vector<std::shared_ptr<Node>> variables)    // Rename variables to arguments TODO
{
    std::string output;
    output.append(name).append("(");
    for (std::vector<std::shared_ptr<Node>>::iterator it = variables.begin(); it != variables.end(); ++it)
    {
        output.append((*it)->toString());
        if (it != variables.end())
        {
            output.append(",");
        }
    }
    output.append(")");
    return output;
}
