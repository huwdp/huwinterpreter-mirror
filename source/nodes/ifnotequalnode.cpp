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

#include "ifnotequalnode.h"

namespace HuwInterpreter {
    namespace Nodes {
        IfNotEqualNode::IfNotEqualNode(std::shared_ptr<Passable> passable, std::shared_ptr<Tokens::Token> token, std::shared_ptr<Nodes::Node> left, std::shared_ptr<Nodes::Node> right)
            : Node("IfNotEqualNode", passable, token)
        {
            this->left = left;
            this->right = right;
            ErrorReporting::Debug::print("NotEqualNode");
        }

        NodeType IfNotEqualNode::getType()
        {
            return IFNOTEQUALNODETYPE;
        }

        std::shared_ptr<Variables::Variable> IfNotEqualNode::execute(std::shared_ptr<Variables::Scope> globalScope, std::shared_ptr<Variables::Scope> scope)
        {
            ErrorReporting::Debug::print("NotEqualNode");
            if (passable->getErrorManager()->count() > 0)
            {
                return null;
            }
            if (scope->getReturnValue() != nullptr)
            {
                return scope->getReturnValue();
            }
            if (left != nullptr && right != nullptr)
            {
                std::shared_ptr<Variables::Variable> l = left->execute(globalScope, scope);
                std::shared_ptr<Variables::Variable> r = right->execute(globalScope, scope);

                if (l == nullptr)
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->invalidExpression(RUNTIME_ERROR, token, internalName));
                    return null;
                }
                if (r == nullptr)
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->invalidExpression(RUNTIME_ERROR, token, internalName));
                    return null;
                }
                std::shared_ptr<Variables::Variable> v = l->ifNotEqual(r, token);
                return v;
            }
            ErrorReporting::Debug::print("Could not compare.");
            return null;
        }

        std::string IfNotEqualNode::toString()
        {
            std::string output;
            if (left != nullptr && right != nullptr)
            {
                output.append(left->toString()).append("!=").append(right->toString());
            }
            return output;
        }
    }
}
