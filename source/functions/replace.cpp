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

std::shared_ptr<Variable> Replace::run(std::shared_ptr<Token> token, std::vector<std::shared_ptr<Node>> variables)
{
    std::shared_ptr<Variable> answer;
    if (variables.size() == 3)
    {
        Node *node1 = variables.at(0).get();
        Node *node2 = variables.at(1).get();
        Node *node3 = variables.at(2).get();
        std::shared_ptr<Variable> var1 = node1->execute();
        std::shared_ptr<Variable> var2 = node2->execute();
        std::shared_ptr<Variable> var3 = node3->execute();

        if (var1 != nullptr && var2 != nullptr && var3 != nullptr)
        {
            std::string temp1 = var1->toString();
            std::string temp2 = var2->toString();
            std::string temp3 = var3->toString();
            temp1.replace(temp1.find(temp2),temp2.length(),temp3);

            auto a = std::shared_ptr<FakeString>(new FakeString("", temp1));
            answer = (a);
        }
    }
    else
    {
        Errors::add("Replace requires three argument");
    }

    return answer;
}