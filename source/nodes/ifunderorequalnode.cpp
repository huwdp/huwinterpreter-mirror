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

#include "ifunderorequalnode.h"

namespace HuwInterpreter {
    namespace Nodes {
        IfUnderOrEqualNode::IfUnderOrEqualNode(std::shared_ptr<Passable> passable, std::shared_ptr<Tokens::Token> token, std::shared_ptr<Nodes::Node> left, std::shared_ptr<Nodes::Node> right)
            : Node("IfUnderOrEqualNode", passable, token)
        {
            this->left = left;
            this->right = right;
            ErrorReporting::Debug::print("UnderOrEqualNode");
        }

        NodeType IfUnderOrEqualNode::getType()
        {
            return IFUNDERORRQUALNODETYPE;
        }

        std::shared_ptr<Variables::Variable> IfUnderOrEqualNode::execute(std::shared_ptr<Variables::Scope> globalScope, std::shared_ptr<Variables::Scope> scope)
        {
            ErrorReporting::Debug::print("UnderOrEqualNode");
            if (passable->getErrorManager()->count() > 0)
            {
                return nullVariable;
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
                    return nullVariable;
                }
                if (r == nullptr)
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->invalidExpression(RUNTIME_ERROR, token, internalName));
                    return nullVariable;
                }
                std::shared_ptr<Variables::Variable> v = l->ifUnderOrEqual(r, token);
                return v;
            }
            ErrorReporting::Debug::print("Could not compare.");
            return nullVariable;
        }

        std::string IfUnderOrEqualNode::toString()
        {
            std::string output;
            if (left != nullptr && right != nullptr)
            {
                output.append(left->toString()).append("<=").append(right->toString());
            }
            return output;
        }
    }
}
