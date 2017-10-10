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

#include "getvarnode.h"

GetVarNode::GetVarNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token, std::string name)
    : Node(passable, token)
{
    this->name = name;
    Debug::print("GetVarNode");
}

NodeType GetVarNode::getType()
{
    return GETVARNODETYPE;
}

std::shared_ptr<Variable> GetVarNode::execute(std::shared_ptr<Scope> scope)
{
    Debug::print("GetVarNode");
    if (scope->getReturnValue() != nullptr)
    {
        return scope->getReturnValue();
    }
    std::shared_ptr<Variable> var = scope->getVariables()->get(name);
    if (var != nullptr)
    {
        return var;
    }
    Debug::print("Could not find variable.");
    return null;
}

std::string GetVarNode::toString()
{
    return name;
}
