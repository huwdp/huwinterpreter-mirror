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

#include "setvarnode.h"

SetVarNode::SetVarNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token, std::string name, std::shared_ptr<Node> value)
    : Node("SetVarNode", passable, token)
{
    this->name = name;
    this->value = value;
    Debug::print("SetVarNode");
}

NodeType SetVarNode::getType()
{
    return SETVARNODETYPE;
}

std::shared_ptr<Variable> SetVarNode::execute(std::shared_ptr<Scope> globalScope, std::shared_ptr<Scope> scope)
{
    Debug::print("SetVarNode");
    if (passable->errors->count() > 0)
    {
        return null;
    }
    if (scope->getReturnValue() != nullptr)
    {
        return scope->getReturnValue();
    }
    std::shared_ptr<Variable> v = value->execute(globalScope, scope);

    std::shared_ptr<Variable> globalVar = globalScope->getVariables()->get(name);
    std::shared_ptr<Variable> localVar = globalScope->getVariables()->get(name);

    if (globalScope->getVariables()->exists(name))
    {

        if (globalVar != nullptr && globalVar->isConst())
        {
            passable->errors->add(passable->errorFactory->cannotChangeConstant(token, name));
            return null;
        }

        if (v != nullptr)
        {
            globalScope->getVariables()->setVariable(name, v->copy(token));
        }
        else
        {
            globalScope->getVariables()->setVariable(name, null);
        }
    }
    else if (scope->getVariables()->exists(name))
    {
        if (localVar != nullptr && localVar->isConst())
        {
            passable->errors->add(passable->errorFactory->cannotChangeConstant(token, name));
            return null;
        }

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
        if (globalVar != nullptr && globalVar->isConst())
        {
            passable->errors->add(passable->errorFactory->cannotChangeConstant(token, name));
        }
        else if (localVar != nullptr && localVar->isConst())
        {
            passable->errors->add(passable->errorFactory->cannotChangeConstant(token, name));
        }
        else
        {
            passable->errors->add(passable->errorFactory->variableDeclared(token, name));
        }
    }
    return null;
}

std::string SetVarNode::toString()
{
    std::string output;
    if (value != nullptr)
    {
        output.append("let ").append(name).append("=").append(value->toString());
    }
    return output;
}

