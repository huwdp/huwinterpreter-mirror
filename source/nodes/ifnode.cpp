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

#include "ifnode.h"

IfNode::IfNode(std::shared_ptr<Token> token, std::shared_ptr<Node> condition, std::shared_ptr<Node> body, std::shared_ptr<Node> elseNode) : Node(token)
{
    Debug::print("IfNode");
    this->condition = condition;
    this->body = body;
    this->elseNode = elseNode;
}

std::shared_ptr<Variable> IfNode::execute(std::shared_ptr<Scope> scope)
{
    
    Debug::print("IfNode");
    std::shared_ptr<Variable> c = condition->execute(scope);
    if (c != nullptr)
    {
        if (c->toBool())
        {
            if (body != nullptr)
            {
                body->execute(scope);
            }
        }
        else
        {
            if (elseNode != nullptr)
            {
                elseNode->execute(scope);
            }
        }
    }
    else
    {
        Errors::add(std::make_shared<Error>(STATEMENT_ERROR, "Could not compare."));
    }
    return null;
}
