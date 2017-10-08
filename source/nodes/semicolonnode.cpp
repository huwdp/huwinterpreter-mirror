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

#include "semicolonnode.h"

SemicolonNode::SemicolonNode(std::shared_ptr<Passible> passible, std::shared_ptr<Node> node)
    : Node(passible, nullptr)
{
    this->node = node;
}

NodeType SemicolonNode::getType()
{
    return SEMICOLONNODETYPE;
}

std::shared_ptr<Variable> SemicolonNode::execute(std::shared_ptr<Scope> scope)
{
    Debug::print("SemicolonNode");
    if (node != nullptr)
    {
        return node->execute(scope);
    }
    return null;
}

std::string SemicolonNode::toString()
{
    std::string output;
    if (node != nullptr)
    {
        output += node->toString();
        if (node->getType() != SEMICOLONNODETYPE)
        {
            output += ";";
        }
    }
    return output;
}
