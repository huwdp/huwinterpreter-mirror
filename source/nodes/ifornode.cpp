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

#include "ifornode.h"

IfOrNode::IfOrNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right) : Node(token)
{
    this->left = left;
    this->right = right;
    Debug::print("Or");
}

std::shared_ptr<Variable> IfOrNode::execute(std::shared_ptr<Scope> scope)
{
    Debug::print("Or");
    if (left != nullptr && right != nullptr)
    {
        std::shared_ptr<Variable> l = left->execute(scope);
        if (l == nullptr)
        {
            Errors::add(std::make_shared<Error>(ERROR, "Invalid expression", token));
            return null;
        }
        if (l->toBool())
        {
            return std::make_shared<NumberVariable>(true);
        }

        std::shared_ptr<Variable> r = right->execute(scope);
        if (r == nullptr)
        {
            Errors::add(std::make_shared<Error>(ERROR, "Invalid expression", token));
            return null;
        }
        if (r->toBool() || l->toBool())
        {
            return std::make_shared<NumberVariable>(true);
        }
        return std::make_shared<NumberVariable>(false);
    }
    Debug::print("Could not or.");
    return null;
}
