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

#include "regexreplace.h"

RegexReplace::RegexReplace(std::shared_ptr<Passable> passable)
    : Function(passable)
{
    name = "regexReplace";
}

std::shared_ptr<Variable> RegexReplace::run(std::shared_ptr<Token> token, std::shared_ptr<Scope> globalScope,
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
           passable->errors->add(passable->errorFactory->invalidArgument(RUNTIME_ERROR, token, name));
           return null;
        }

        std::shared_ptr<Variable> var1 = node1->execute(globalScope, scope);
        std::shared_ptr<Variable> var2 = node2->execute(globalScope, scope);
        std::shared_ptr<Variable> var3 = node3->execute(globalScope, scope);

        if (var1 == nullptr || var2 == nullptr || var3 == nullptr)
        {
           passable->errors->add(passable->errorFactory->invalidArgument(RUNTIME_ERROR, token, name));
           return null;
        }

        std::string str = var1->toString();
        std::string str2 = var2->toString();
        std::string str3 = var3->toString();
        std::regex arg2(str2);
        std::string result;
        try
        {
            result = std::regex_replace(str, arg2, str3);
        }
        catch (std::regex_error ex)
        {
            passable->errors->add(passable->errorFactory->otherFunctionError(token, name, "", ex.what()));
            return null;
        }
        return std::make_shared<StringVariable>(passable, result);
    }
    else
    {
       passable->errors->add(passable->errorFactory->requiresArguments(token, name, "", 2));
    }
    return returnNode;
}
