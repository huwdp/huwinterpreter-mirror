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

#include "runnode.h"

RunNode::RunNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right) : Node(token)
{
    this->left = left;
    this->right = right;
    Debug::print("RunNode");
}

std::shared_ptr<Variable> RunNode::execute(std::shared_ptr<Scope> scope)
{
    Debug::print("RunNode");
    if (scope->getReturnValue() != nullptr)
    {
        return scope->getReturnValue();
    }
    if (left != nullptr)
    {
        left->execute(scope);
        if (scope->getReturnValue() != nullptr)
        {
            return scope->getReturnValue();
        }
    }
    if (right != nullptr)
    {
        right->execute(scope);
        if (scope->getReturnValue() != nullptr)
        {
            return scope->getReturnValue();
        }
    }
    return null;
}
