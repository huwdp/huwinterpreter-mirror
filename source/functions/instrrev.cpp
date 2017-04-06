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

#include "instrrev.h"

std::shared_ptr<Variable> InStrRev::run(std::shared_ptr<Token> token, std::vector<std::shared_ptr<Node>> variables)
{
    std::shared_ptr<Variable> answer;
    if (variables.size() == 2)
    {
        Node *node1 = variables.at(0).get();
        std::shared_ptr<Variable> var1 = node1->execute();
        Node *node2 = variables.at(0).get();
        std::shared_ptr<Variable> var2 = node2->execute();
        if (var1 != nullptr && var2 != nullptr)
        {
            std::string str = var1->toString();
            std::string str2 = var2->toString();
            std::size_t found = str.find_last_of(str2);
            if (found != std::string::npos)
            {
                answer = std::make_shared<FakeNumber>((double)found);
            }
            else
            {
                answer = std::make_shared<FakeNumber>(-1.0);
            }
        }
    }
    else
    {
        Errors::add(std::make_shared<Error>(FUNCTION_ERROR, "InStrRev function requires two arguments", token));
    }
    return answer;
}
