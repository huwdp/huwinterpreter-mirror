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

#include "mulnode.h"

MulNode::MulNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right)
    : Node(passible, token)
{
    this->left = left;
    this->right = right;
    Debug::print("MulNode");
}

NodeType MulNode::getType()
{
    return MULNODETYPE;
}

std::shared_ptr<Variable> MulNode::execute(std::shared_ptr<Scope> scope)
{
    Debug::print("MulNode");
    if (scope->getReturnValue() != null)
    {
        return scope->getReturnValue();
    }
    if (left != nullptr && right != nullptr)
    {
        std::shared_ptr<Variable> l = left->execute(scope);
        std::shared_ptr<Variable> r = right->execute(scope);

        if (l == nullptr)
        {
            passible->errors->add(std::make_shared<Error>(ERROR, "Invalid expression", token));
            return null;
        }
        if (r == nullptr)
        {
            passible->errors->add(std::make_shared<Error>(ERROR, "Invalid expression", token));
            return null;
        }
        std::shared_ptr<Variable> v = l->mul(r);
        return v;
    }
    Debug::print("Could not mul.");
    return null;
}

std::string MulNode::toString()
{
    std::string output;
    if (left != nullptr && right != nullptr)
    {
        output.append(left->toString()).append("*").append(right->toString());
    }
    return output;
}
