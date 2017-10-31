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

#include "bracketnode.h"

BracketNode::BracketNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token, std::shared_ptr<Node> node)
    : Node("BracketNode", passable, token)
{
    this->node = node;
    Debug::print("Bracket");
}

NodeType BracketNode::getType()
{
    return BRACKETNODETYPE;
}

std::shared_ptr<Variable> BracketNode::execute(std::shared_ptr<Scope> globalScope, std::shared_ptr<Scope> scope)
{
    Debug::print("Bracket");
    if (scope->getReturnValue() != nullptr)
    {
        return scope->getReturnValue();
    }
    if (node != nullptr)
    {
        std::shared_ptr<Variable> n = node->execute(globalScope, scope);
        if (n == nullptr)
        {
            passable->errors->add(passable->errorFactory->invalidExpression(RUNTIME_ERROR, token, internalName));
            return null;
        }
        return n;
    }
    Debug::print("Could not bracket.");
    return null;
}

std::string BracketNode::toString()
{
    if (node != nullptr)
    {
        return "(" + node->toString() + ")";
    }
    return "";
}
