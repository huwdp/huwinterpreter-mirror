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

namespace HuwInterpreter {
    namespace Nodes {
        BitwiseComplementNode::BitwiseComplementNode(std::shared_ptr<Passable> passable, std::shared_ptr<Tokens::Token> token, std::shared_ptr<Nodes::Node> node)
            : Node("BitwiseComplementNode", passable, token)
        {
            ErrorReporting::Debug::print("BitwiseComplementNode");
            this->node = node;
        }

        NodeType BitwiseComplementNode::getType()
        {
            return BITWISECOMPLEMENTNODETYPE;
        }

        std::shared_ptr<Variables::Variable> BitwiseComplementNode::execute(std::shared_ptr<Variables::Scope> globalScope, std::shared_ptr<Variables::Scope> scope)
        {
            ErrorReporting::Debug::print("BitwiseComplementNode");
            if (passable->getErrorManager()->count() > 0)
            {
                return nullVariable;
            }
            if (scope->getReturnValue() != nullptr)
            {
                return scope->getReturnValue();
            }
            if (node != nullptr)
            {
                std::shared_ptr<Variables::Variable> var = node->execute(globalScope, scope);
                if (var != nullptr)
                {
                    return var->bitwiseComplement(token);
                }
                passable->getErrorManager()->add(passable->getErrorFactory()->invalidExpression(RUNTIME_ERROR, token, internalName));
            }
            return nullVariable;
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
    }
}

