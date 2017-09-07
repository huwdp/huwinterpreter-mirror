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

#include "addconstnode.h"

AddConstNode::AddConstNode(std::shared_ptr<Token> token, std::string name, std::shared_ptr<Node> value, std::shared_ptr<Node> next)
    : Node(token)
{
    this->name = name;
    this->value = value;
    this->next = next;
    Debug::print("AddConstNode");
}

NodeType AddConstNode::getType()
{
    return ADDCONSTNODETYPE;
}

std::shared_ptr<Variable> AddConstNode::execute(std::shared_ptr<Scope> scope)
{
    Debug::print("AddConstNode");
    if (scope->getReturnValue() != nullptr)
    {
        return scope->getReturnValue();
    }
    if (scope->getVariables()->exists(name))
    {
        std::shared_ptr<Variable> v = value->execute(scope);
        scope->getVariables()->set(name, v->toString());
    }
    else
    {
        std::shared_ptr<Variable> var;
        var = value->execute(scope);
        if (scope->getReturnValue() != nullptr)
        {
            return scope->getReturnValue();
        }

        if (var != nullptr)
        {
            if (!scope->getVariables()->addVariable(name, var))
            {
                Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "Constant not declared", token));
            }
        }
    }
    if (next != nullptr)
    {
        return next->execute(scope);
    }
    return null;
}

std::string AddConstNode::toString()
{
    std::string output;
    if (value != nullptr && next != nullptr)
    {
        output.append("const ").append(name).append("=").append(value->toString());
        std::string right = next->toString();
        if (right.size() > 0)
        {
            output.append(";").append(next->toString());
        }
    }
    else if (value != nullptr)
    {
        output.append("let ").append(name).append("=").append(value->toString());
    }
    else if (next != nullptr)
    {
        output.append(next->toString());
    }
    return output;
}
