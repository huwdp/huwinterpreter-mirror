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

BracketNode::BracketNode(std::shared_ptr<Token> token, std::shared_ptr<Node> node) : Node(token)
{
    this->node = node;
    Debug::print("Bracket");
}

std::shared_ptr<Variable> BracketNode::execute(std::shared_ptr<Scope> scope)
{
    std::shared_ptr<Variable> null;
    Debug::print("Bracket");
    if (node != nullptr)
    {
        std::shared_ptr<Variable> n = node->execute(scope);
        if (n == nullptr)
        {
            Errors::add(std::make_shared<Error>(ERROR, "Invalid expression", token));
            return null;
        }
        return (n);
    }
    Debug::print("Could not bracket.");
    return null;
}
