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

#include "setreturnnode.h"

namespace HuwInterpreter {
    namespace Nodes {
        SetReturnNode::SetReturnNode(std::shared_ptr<Passable> passable, std::shared_ptr<Nodes::Node> node)
            : Node("SetReturnNode", passable, nullptr)
        {
            this->node = node;
        }

        NodeType SetReturnNode::getType()
        {
            return SETRETURNNODETYPE;
        }

        std::shared_ptr<Variables::Variable> SetReturnNode::execute(std::shared_ptr<Variables::Scope> globalScope, std::shared_ptr<Variables::Scope> scope)
        {
            ErrorReporting::Debug::print("SetReturnNode");
            if (passable->getErrorManager()->count() > 0)
            {
                return nullVariable;
            }
            if (scope->getReturnValue() != nullptr)
            {
                return scope->getReturnValue();
            }
            scope->setReturnValue(node->execute(globalScope, scope));
            return scope->getReturnValue();
            return nullVariable;
        }

        std::string SetReturnNode::toString()
        {
            std::string output;
            if (node != nullptr)
            {
                output.append("return ").append(node->toString());
            }
            return output;
        }
    }
}
