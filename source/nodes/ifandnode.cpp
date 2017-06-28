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

#include "ifandnode.h"

IfAndNode::IfAndNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right) : Node(token)
{
    this->left = left;
    this->right = right;
    Debug::print("And");
}

std::shared_ptr<Variable> IfAndNode::execute(std::shared_ptr<Scope> scope)
{
    Debug::print("And");
    if (left != nullptr && right != nullptr)
    {
        std::shared_ptr<Variable> l = left->execute(scope);
        if (l == nullptr)
        {
            Errors::add(std::make_shared<Error>(ERROR, "Invalid expression", token));
            return null;
        }
        if (!l->toBool())
        {
            return std::make_shared<NumberVariable>(false);
        }

        std::shared_ptr<Variable> r = right->execute(scope);
        if (r == nullptr)
        {
            Errors::add(std::make_shared<Error>(ERROR, "Invalid expression", token));
            return null;
        }

        if (r->toBool() && l->toBool())
        {
            return std::make_shared<NumberVariable>(true);
        }
        return std::make_shared<NumberVariable>(false);
    }
    Debug::print("Could not and");
    return null;
}
