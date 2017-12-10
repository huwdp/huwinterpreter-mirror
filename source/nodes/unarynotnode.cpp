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

namespace HuwInterpreter {
    namespace Nodes {
        UnaryNotNode::UnaryNotNode(std::shared_ptr<Passable> passable, std::shared_ptr<Tokens::Token> token, std::shared_ptr<Nodes::Node> node)
            : Node("UnaryNotNode", passable, token)
        {
            this->node = node;
        }

        NodeType UnaryNotNode::getType()
        {
            return UNARYNOTNODETYPE;
        }

        std::shared_ptr<Variables::Variable> UnaryNotNode::execute(std::shared_ptr<Variables::Scope> globalScope, std::shared_ptr<Variables::Scope> scope)
        {
            ErrorReporting::Debug::print("UnaryNot");
            if (passable->getErrorManager()->count() > 0)
            {
                return null;
            }
            if (scope->getReturnValue() != null)
            {
                return scope->getReturnValue();
            }
            if (node != nullptr)
            {
                std::shared_ptr<Variables::Variable> var = node->execute(globalScope, scope);
                if (var != nullptr)
                {
                    if (var->toBool())
                    {
                        return std::make_shared<Variables::NumberVariable>(passable, 0.0);
                    }
                    return std::make_shared<Variables::NumberVariable>(passable, 1.0);
                }
                passable->getErrorManager()->add(passable->getErrorFactory()->invalidExpression(RUNTIME_ERROR, token, internalName));
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
    }
}
