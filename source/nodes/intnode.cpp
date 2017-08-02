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

#include "intnode.h"

IntNode::IntNode(std::shared_ptr<Token> token, std::shared_ptr<Node> node)
    : Node(token)
{
    this->node = node;
}

std::shared_ptr<Variable> IntNode::execute(std::shared_ptr<Scope> scope)
{
    Debug::print("IntNode");
    if (scope->getReturnValue() != nullptr)
    {
        return scope->getReturnValue();
    }
    if (node != nullptr)
    {
        std::shared_ptr<Variable> n = node->execute(scope);
        if (n == nullptr)
        {
            Errors::add(std::make_shared<Error>(ERROR, "Invalid expression", token));
            return null;
        }
        return std::move(std::make_shared<NumberVariable>(n->toInt()));
    }
    Debug::print("Could not IntNode.");
    return null;
}
