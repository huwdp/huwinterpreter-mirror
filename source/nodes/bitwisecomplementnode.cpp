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

#include "bitwisecomplementnode.h"

BitwiseComplementNode::BitwiseComplementNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token, std::shared_ptr<Node> node)
    : Node("BitwiseComplementNode", passable, token)
{
    this->node = node;
}

NodeType BitwiseComplementNode::getType()
{
    return BITWISECOMPLEMENTNODETYPE;
}

std::shared_ptr<Variable> BitwiseComplementNode::execute(std::shared_ptr<Scope> globalScope, std::shared_ptr<Scope> scope)
{
    Debug::print("BitwiseComplementNode");
    if (scope->getReturnValue() != null)
    {
        return scope->getReturnValue();
    }
    if (node != nullptr)
    {
        std::shared_ptr<Variable> var = node->execute(globalScope, scope);
        if (var != nullptr)
        {
            return var->bitwiseComplement();
        }
        passable->errors->add(passable->errorFactory->invalidExpression(RUNTIME_ERROR, token, internalName));
    }
    return null;
}

std::string BitwiseComplementNode::toString()
{
    std::string output;
    if (node != nullptr)
    {
        output.append("~").append(node->toString());
    }
    return output;
}

