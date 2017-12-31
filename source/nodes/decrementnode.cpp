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

#include "decrementnode.h"

namespace HuwInterpreter {
    namespace Nodes {
        DecrementNode::DecrementNode(std::shared_ptr<Passable> passable, std::shared_ptr<Tokens::Token> token, std::shared_ptr<Nodes::Node> node)
            : Node("DecrementNode", passable, token)
        {
            this->node = node;
            ErrorReporting::Debug::print("Decrement");
        }

        NodeType DecrementNode::getType()
        {
            return DECREMENTNODETYPE;
        }

        std::shared_ptr<Variables::Variable> DecrementNode::execute(std::shared_ptr<Variables::Scope> globalScope, std::shared_ptr<Variables::Scope> scope)
        {
            ErrorReporting::Debug::print("Decrement");
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
                std::shared_ptr<Variables::Variable> n = node->execute(globalScope, scope);
                if (n == nullptr)
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->invalidExpression(RUNTIME_ERROR, token, internalName));
                    return nullVariable;
                }
                return n->decrement(token);
            }
            ErrorReporting::Debug::print("Could not increment.");
            return nullVariable;
        }

        std::string DecrementNode::toString()
        {
            if (node != nullptr)
            {
                return node->toString() + "--";
            }
            return "";
        }
    }
}
