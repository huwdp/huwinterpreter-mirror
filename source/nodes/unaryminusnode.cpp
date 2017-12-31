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

namespace HuwInterpreter {
    namespace Nodes {
        UnaryMinusNode::UnaryMinusNode(std::shared_ptr<Passable> passable, std::shared_ptr<Tokens::Token> token, std::shared_ptr<Nodes::Node> node)
            : Node("UnaryMinusNode", passable, token)
        {
            this->node = node;
        }

        NodeType UnaryMinusNode::getType()
        {
            return UNARYMINUSNODETYPE;
        }

        std::shared_ptr<Variables::Variable> UnaryMinusNode::execute(std::shared_ptr<Variables::Scope> globalScope, std::shared_ptr<Variables::Scope> scope)
        {
            ErrorReporting::Debug::print("UnaryMinusNode");
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
                std::shared_ptr<Variables::Variable> value = node->execute(globalScope, scope);
                if (value != nullptr)
                {
                    return value->mul(std::make_shared<Variables::IntegerVariable>(passable, -1), token);
                }
                else
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->invalidExpression(RUNTIME_ERROR, token, internalName));
                }
            }
            return nullVariable;
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
    }
}
