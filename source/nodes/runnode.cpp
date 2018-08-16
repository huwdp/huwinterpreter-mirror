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

#include "runnode.h"

namespace HuwInterpreter {
    namespace Nodes {
        RunNode::RunNode(std::shared_ptr<Passable> passable, std::shared_ptr<Tokens::Token> token, std::shared_ptr<Nodes::Node> left, std::shared_ptr<Nodes::Node> right)
            : Node("RunNode", passable, token)
        {
            ErrorReporting::Debug::print("RunNode");
            this->left = left;
            this->right = right;
        }

        NodeType RunNode::getType()
        {
            return RUNNODETYPE;
        }

        std::shared_ptr<Variables::Variable> RunNode::execute(std::shared_ptr<Variables::Scope> globalScope, std::shared_ptr<Variables::Scope> scope)
        {
            ErrorReporting::Debug::print("RunNode");
            if (passable->getErrorManager()->count() > 0)
            {
                return nullVariable;
            }
            if (scope->getReturnValue() != nullptr)
            {
                return scope->getReturnValue();
            }
            if (left != nullptr)
            {
                left->execute(globalScope, scope);
                if (passable->getErrorManager()->count() > 0)
                {
                    return nullVariable;
                }
                if (scope->getReturnValue() != nullptr)
                {
                    return scope->getReturnValue();
                }
            }
            if (right != nullptr)
            {
                right->execute(globalScope, scope);
                if (passable->getErrorManager()->count() > 0)
                {
                    return nullVariable;
                }
                if (scope->getReturnValue() != nullptr)
                {
                    return scope->getReturnValue();
                }
            }
            return nullVariable;
        }

        std::string RunNode::toString()
        {
            std::string output;
            if (left != nullptr && right != nullptr)
            {
                output.append(left->toString()).append(right->toString());
                return output;
            }
            if (left != nullptr)
            {
                output.append(left->toString());
            }
            if (right != nullptr)
            {
                output.append(right->toString());
            }
            return output;
        }
    }
}
