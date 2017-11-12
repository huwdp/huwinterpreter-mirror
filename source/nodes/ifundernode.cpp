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

#include "ifundernode.h"

IfUnderNode::IfUnderNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right)
    : Node("IfUnderNode", passable, token)
{
    this->left = left;
    this->right = right;
    Debug::print("UnderNode");
}

NodeType IfUnderNode::getType()
{
    return IFUNDERNODETYPE;
}

std::shared_ptr<Variable> IfUnderNode::execute(std::shared_ptr<Scope> globalScope, std::shared_ptr<Scope> scope)
{
    Debug::print("UnderNode");
    if (passable->errors->count() > 0)
    {
        return null;
    }
    if (scope->getReturnValue() != nullptr)
    {
        return scope->getReturnValue();
    }
    if (left != nullptr && right != nullptr)
    {
        std::shared_ptr<Variable> l = left->execute(globalScope, scope);
        std::shared_ptr<Variable> r = right->execute(globalScope, scope);

        if (l == nullptr)
        {
            passable->errors->add(passable->errorFactory->invalidExpression(RUNTIME_ERROR, token, internalName));
            return null;
        }
        if (r == nullptr)
        {
            passable->errors->add(passable->errorFactory->invalidExpression(RUNTIME_ERROR, token, internalName));
            return null;
        }
        std::shared_ptr<Variable> v = l->ifUnder(r, token);
        return v;
    }
    Debug::print("Could not compare.");
    return null;
}

std::string IfUnderNode::toString()
{
    std::string output;
    if (left != nullptr && right != nullptr)
    {
        output.append(left->toString()).append("<").append(right->toString());
    }
    return output;
}
