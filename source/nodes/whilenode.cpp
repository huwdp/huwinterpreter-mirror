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

#include "whilenode.h"

WhileNode::WhileNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token, std::shared_ptr<Node> condition, std::shared_ptr<Node> body, std::shared_ptr<Node> next)
    : Node("WhileNode", passable, token)
{
    this->condition = condition;
    this->body = body;
    this->next = next;
    Debug::print("WhileNode");
}

NodeType WhileNode::getType()
{
    return WHILENODETYPE;
}

std::shared_ptr<Variable> WhileNode::execute(std::shared_ptr<Scope> globalScope, std::shared_ptr<Scope> scope)
{
    Debug::print("WhileNode");
    if (scope->getReturnValue() != nullptr)
    {
        return scope->getReturnValue();
    }
    if (condition != nullptr)
    {
        std::shared_ptr<Variable> c = this->condition->execute(globalScope, scope);

        if (c == null)
        {
            passable->errors->add(passable->errorFactory->invalidExpression(RUNTIME_ERROR, token, internalName));
            return null;
        }
        bool loop = c->toBool();
        while (loop)
        {
            if (scope->getReturnValue() != nullptr)
            {
                return scope->getReturnValue();
            }
            body->execute(globalScope, scope);
            c = condition->execute(globalScope, scope);
            loop = c->toBool();
            if (c == null)
            {
                passable->errors->add(passable->errorFactory->invalidExpression(RUNTIME_ERROR, token, internalName));
                return null;
            }
        }
    }
    else
    {
        passable->errors->add(passable->errorFactory->failedToCompare(token, internalName));
        return null;
    }
    if (next != nullptr)
    {
        return next->execute(globalScope, scope);
    }
    return null;
}

std::string WhileNode::toString()
{
    std::string output;
    output.append("while (");
    if (condition != nullptr)
    {
        output.append(condition->toString());
    }
    output.append("){");
    if (body != nullptr)
    {
        output.append(body->toString());
    }
    output.append("}");
    if (next != nullptr)
    {
        output.append(next->toString());
    }
    return output;
}
