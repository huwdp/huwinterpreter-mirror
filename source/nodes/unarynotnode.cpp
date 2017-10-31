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

#include "unarynotnode.h"

UnaryNotNode::UnaryNotNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token, std::shared_ptr<Node> node)
    : Node("UnaryNotNode", passable, token)
{
    this->node = node;
}

NodeType UnaryNotNode::getType()
{
    return UNARYNOTNODETYPE;
}

std::shared_ptr<Variable> UnaryNotNode::execute(std::shared_ptr<Scope> globalScope, std::shared_ptr<Scope> scope)
{
    Debug::print("UnaryNot");
    if (scope->getReturnValue() != null)
    {
        return scope->getReturnValue();
    }
    if (node != nullptr)
    {
        std::shared_ptr<Variable> var = node->execute(globalScope, scope);
        if (var != nullptr)
        {
            if (var->toBool())
            {
                return std::make_shared<NumberVariable>(passable, 0.0);
            }
            return std::make_shared<NumberVariable>(passable, 1.0);
        }
        passable->errors->add(passable->errorFactory->invalidExpression(RUNTIME_ERROR, token, internalName));
    }
    return null;
}

std::string UnaryNotNode::toString()
{
    std::string output;
    if (node != nullptr)
    {
        output.append("!").append(node->toString());
    }
    return output;
}
