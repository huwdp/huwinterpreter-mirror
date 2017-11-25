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

#include "modnode.h"

ModNode::ModNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right)
    : Node("ModNode", passable, token)
{
    this->left = left;
    this->right = right;
    Debug::print("Mod");
}

NodeType ModNode::getType()
{
    return MODNODETYPE;
}

std::shared_ptr<Variable> ModNode::execute(std::shared_ptr<Scope> globalScope, std::shared_ptr<Scope> scope)
{
    Debug::print("Mod");
    if (passable->getErrors()->count() > 0)
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
            passable->getErrors()->add(passable->getErrorFactory()->invalidExpression(RUNTIME_ERROR, token, internalName));
            return null;
        }
        if (r == nullptr)
        {
            passable->getErrors()->add(passable->getErrorFactory()->invalidExpression(RUNTIME_ERROR, token, internalName));
            return null;
        }
        std::shared_ptr<Variable> v = l->mod(r, token);
        return v;
    }
    Debug::print("Could not mod.");
    return null;
}

std::string ModNode::toString()
{
    std::string output;
    if (left != nullptr && right != nullptr)
    {
        output.append(left->toString()).append("%").append(right->toString());
    }
    return output;
}
