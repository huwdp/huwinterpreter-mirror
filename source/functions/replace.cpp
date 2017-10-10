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

#include "replace.h"

Replace::Replace(std::shared_ptr<Passable> passable)
    : Function(passable)
{
    name = "replace";
}

std::shared_ptr<Variable> Replace::run(std::shared_ptr<Token> token,
                                       std::shared_ptr<Scope> scope,
                                       std::vector<std::shared_ptr<Node>> variables)
{
    std::shared_ptr<Variable> returnNode;
    if (variables.size() == 3)
    {
        std::shared_ptr<Node> node1 = variables.at(0);
        std::shared_ptr<Node> node2 = variables.at(1);
        std::shared_ptr<Node> node3 = variables.at(2);
        if (node1 == nullptr || node2 == nullptr || node3 == nullptr)
        {
            return null;
        }

        std::shared_ptr<Variable> var1 = node1->execute(scope);
        std::shared_ptr<Variable> var2 = node2->execute(scope);
        std::shared_ptr<Variable> var3 = node3->execute(scope);

        if (var1 != nullptr && var2 != nullptr && var3 != nullptr)
        {
            std::string temp1 = var1->toString();
            std::string temp2 = var2->toString();
            std::string temp3 = var3->toString();
            temp1.replace(temp1.find(temp2),temp2.length(),temp3);
            returnNode = std::make_shared<StringVariable>(passable, "", temp1);
        }
    }
    else
    {
        passable->errors->add("Replace requires three argument");
    }

    return returnNode;
}
