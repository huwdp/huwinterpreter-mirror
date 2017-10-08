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

#include "ifnotequalnode.h"

IfNotEqualNode::IfNotEqualNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right)
    : Node(passible, token)
{
    this->left = left;
    this->right = right;
    Debug::print("NotEqualNode");
}

NodeType IfNotEqualNode::getType()
{
    return IFNOTEQUALNODETYPE;
}

std::shared_ptr<Variable> IfNotEqualNode::execute(std::shared_ptr<Scope> scope)
{
    Debug::print("NotEqualNode");
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
            passible->errors->add(std::make_shared<Error>(ERROR, "Invalid expression", token));
            return null;
        }
        if (r == nullptr)
        {
            passible->errors->add(std::make_shared<Error>(ERROR, "Invalid expression", token));
            return null;
        }
        std::shared_ptr<Variable> v = l->ifNotEqual(r);
        return v;
    }
    Debug::print("Could not compare.");
    return null;
}

std::string IfNotEqualNode::toString()
{
    std::string output;
    if (left != nullptr && right != nullptr)
    {
        output.append(left->toString()).append("!=").append(right->toString());
    }
    return output;
}
