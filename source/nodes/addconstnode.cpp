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

AddConstNode::AddConstNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token, std::string name, std::shared_ptr<Node> value)
    : Node("AddConstNode", passable, token)
{
    this->name = name;
    this->value = value;
    Debug::print("AddConstNode");
}

NodeType AddConstNode::getType()
{
    return ADDCONSTNODETYPE;
}

std::shared_ptr<Variable> AddConstNode::execute(std::shared_ptr<Scope> globalScope, std::shared_ptr<Scope> scope)
{
    Debug::print("AddConstNode");
    if (scope->getReturnValue() != nullptr)
    {
        return scope->getReturnValue();
    }
    if (scope->getVariables()->exists(name))
    {
        std::shared_ptr<Variable> v = value->execute(globalScope, scope);
        if (v != nullptr)
        {
            scope->getVariables()->setVariable(name, v->copy(token));
        }
        else
        {
            scope->getVariables()->setVariable(name, null);
        }
    }
    else
    {
        std::shared_ptr<Variable> var;
        var = value->execute(globalScope, scope);
        if (scope->getReturnValue() != nullptr)
        {
            return scope->getReturnValue();
        }

        if (var != nullptr)
        {
            if (globalScope->getVariables()->exists(name))
            {
                passable->errors->add(passable->errorFactory->constantDeclared(token, name));
                return null;
            }
            else if (!scope->getVariables()->addVariable(name, var))
            {
                passable->errors->add(passable->errorFactory->constantNotDeclared(token, name));
            }
        }
        else
        {
            passable->errors->add(passable->errorFactory->invalidExpression(RUNTIME_ERROR, token, internalName));
        }
    }
    return null;
}

std::string AddConstNode::toString()
{
    std::string output;
    if (value != nullptr)
    {
        output.append("const ").append(name).append("=").append(value->toString());
    }
    return output;
}
