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

#include "regexsearch.h"

RegexSearch::RegexSearch(std::shared_ptr<Passable> passable)
    : Function(passable)
{
    name = "regexSearch";
}

std::shared_ptr<Variable> RegexSearch::execute(std::shared_ptr<Token> token,
                                           std::shared_ptr<Scope> globalScope,
                                           std::shared_ptr<Scope> scope,
                                           std::vector<std::shared_ptr<Node>> arguments)
{
    std::shared_ptr<Variable> returnNode;
    if (arguments.size() == 2)
    {
        std::shared_ptr<Node> node1 = arguments.at(0);
        std::shared_ptr<Node> node2 = arguments.at(1);
        if (node1 == nullptr || node2 == nullptr)
        {
            passable->errors->add(passable->errorFactory->invalidArgument(token, RUNTIME_ERROR, name));
            return null;
        }

        std::shared_ptr<Variable> var1 = node1->execute(globalScope, scope);
        std::shared_ptr<Variable> var2 = node2->execute(globalScope, scope);

        if (var1 == nullptr || var2 == nullptr)
        {
            passable->errors->add(passable->errorFactory->invalidArgument(token, RUNTIME_ERROR, name));
            return null;
        }

        std::string str = var1->toString();
        std::string str2 = var2->toString();
        std::regex regex(str2);
        bool result = std::regex_search(str, regex);
        return std::make_shared<NumberVariable>(passable, result);
    }
    else
    {
        passable->errors->add(passable->errorFactory->requiresArguments(token, name, "", 2));
    }
    return returnNode;
}
