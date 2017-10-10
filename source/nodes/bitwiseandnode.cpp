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

#include "bitwiseandnode.h"

BitwiseAndNode::BitwiseAndNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right)
    : Node(passable, token)
{
    this->left = left;
    this->right = right;
}

NodeType BitwiseAndNode::getType()
{
    return BITWISEANDNODETYPE;
}

std::shared_ptr<Variable> BitwiseAndNode::execute(std::shared_ptr<Scope> scope)
{
    Debug::print("BitwiseAndNode");
    if (scope->getReturnValue() != nullptr)
    {
        return scope->getReturnValue();
    }
    if (left != nullptr && right != nullptr)
    {
        std::shared_ptr<Variable> l = left->execute(scope);
        std::shared_ptr<Variable> r = right->execute(scope);
        if (l == nullptr)
        {
            passable->errors->add(std::make_shared<Error>(ERROR, "Invalid expression", token));
            return null;
        }
        if (r == nullptr)
        {
            passable->errors->add(std::make_shared<Error>(ERROR, "Invalid expression", token));
            return null;
        }
        return l->bitwiseAnd(r);
    }
    Debug::print("Could not bitwiseAnd");
    return null;
}

std::string BitwiseAndNode::toString()
{
    std::string output;
    if (left != nullptr && right != nullptr)
    {
        output.append(left->toString()).append("&").append(right->toString());
    }
    return output;
}
