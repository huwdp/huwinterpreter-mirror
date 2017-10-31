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

#include "unaryminusnode.h"

UnaryMinusNode::UnaryMinusNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token, std::shared_ptr<Node> node)
    : Node("UnaryMinusNode", passable, token)
{
    this->node = node;
}

NodeType UnaryMinusNode::getType()
{
    return UNARYMINUSNODETYPE;
}

std::shared_ptr<Variable> UnaryMinusNode::execute(std::shared_ptr<Scope> globalScope, std::shared_ptr<Scope> scope)
{
    Debug::print("UnaryMinusNode");
    if (scope->getReturnValue() != nullptr)
    {
        return scope->getReturnValue();
    }
    if (node != nullptr)
    {
        std::shared_ptr<Variable> value = node->execute(globalScope, scope);
        if (value != nullptr)
        {
            return value->mul(std::make_shared<IntegerVariable>(passable, -1));
        }
        else
        {
            passable->errors->add(passable->errorFactory->invalidExpression(RUNTIME_ERROR, token, internalName));
        }
    }
    return null;
}

std::string UnaryMinusNode::toString()
{
    std::string output;
    if (node != nullptr)
    {
        output.append("-").append(node->toString());
    }
    return output;
}
