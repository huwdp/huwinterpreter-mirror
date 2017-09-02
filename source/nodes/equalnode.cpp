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

#include "equalnode.h"

EqualNode::EqualNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right, std::shared_ptr<Node> next, std::shared_ptr<Scope> scope)
    : Node(token)
{
    this->left = left;
    this->right = right;
    this->next = next;
    this->scope = scope;
    Debug::print("Equals");
}

std::shared_ptr<Variable> EqualNode::execute(std::shared_ptr<Scope> scope)
{
    Debug::print("Equals");
    if (scope->getReturnValue() != nullptr)
    {
        return scope->getReturnValue();
    }
    std::shared_ptr<Variable> l = left->execute(scope);
    std::shared_ptr<Node> left = std::make_shared<SetVarNode>(token, l->getName(), right, nullptr);
    this->left = left;
    if (next != nullptr)
    {
        std::shared_ptr<Variable> value = next->execute(scope);
        if (value != nullptr)
        {
            return value->copy();
        }
    }
    return null;
}

std::string EqualNode::toString()
{
    std::string output;
    if (left != nullptr && right != nullptr)
    {
        output.append(left->toString()).append("=").append(right->toString()).append(";");
    }
    if (next != nullptr)
    {
        output.append(next->toString());
    }
    return output;
}
