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

#include "jsifnode.h"

JSIfNode::JSIfNode(std::shared_ptr<Token> token, std::shared_ptr<Node> condition, std::shared_ptr<Node> body, std::shared_ptr<Node> elseNode)
    : IfNode(token, condition, body, elseNode)
{
}

std::string JSIfNode::toString()
{
    std::string output;
    output.append("if (");
    if (condition != nullptr)
    {
        output.append(condition->toString());
    }
    output.append("){");
    if (body != nullptr)
    {
        output.append(body->toString());
    }
    output.append("}");
    if (elseNode != nullptr)
    {
        output.append("else").append("{").append(elseNode->toString()).append("}");
    }
    return output;
}
