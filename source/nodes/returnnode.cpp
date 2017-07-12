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

#include "returnnode.h"

ReturnNode::ReturnNode(std::shared_ptr<Node> node)
    : Node(nullptr)
{
    this->node = node;
}

std::shared_ptr<Variable> ReturnNode::execute(std::shared_ptr<Scope> scope)
{
    Debug::print("ReturnNode");
    if (scope->getReturnValue() != nullptr)
    {
        return scope->getReturnValue();
    }
    return node->execute(scope);
}
