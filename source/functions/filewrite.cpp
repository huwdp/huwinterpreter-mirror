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

std::shared_ptr<Variable> FileWrite::run(std::shared_ptr<Token> token,
                                         std::shared_ptr<Scope> scope,
                                         std::vector<std::shared_ptr<Node>> variables)
{
    std::shared_ptr<Variable> answer;
    if (variables.size() == 2)
    {
        Node *node1 = variables.at(0).get();
        Node *node2 = variables.at(1).get();

        if (node1 != nullptr && node2 != nullptr)
        {
            std::shared_ptr<Variable> var1 = node1->execute(scope);
            std::shared_ptr<Variable> var2 = node2->execute(scope);

            if (var1 != nullptr && var2 != nullptr)
            {
                std::string fileLocation = var1->toString();
                std::string output = var2->toString();
                IO file;
                if (file.write(fileLocation, output))
                {
                    answer = std::make_shared<FakeNumber>(1.0);
                }
            }
            else
            {
                answer = std::make_shared<FakeNumber>(0.0);
            }
        }
        else
        {
           answer = std::make_shared<FakeNumber>(0.0);
        }
    }
    else
    {
        Errors::add(std::make_shared<Error>(FUNCTION_ERROR, "FileWrite requires two arguments", token));
    }
    return answer;
}
