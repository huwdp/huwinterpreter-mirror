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

#include "semicolonnode.h"

namespace HuwInterpreter {
    namespace Nodes {
        SemicolonNode::SemicolonNode(std::shared_ptr<HuwInterpreter::Passable> passable, std::shared_ptr<Nodes::Node> node)
            : Node("SemicolonNode", passable, nullptr)
        {
            ErrorReporting::Debug::print(getName());
            this->node = node;
        }

        NodeType SemicolonNode::getType()
        {
            return SEMICOLONNODETYPE;
        }

        std::shared_ptr<Variables::Variable> SemicolonNode::execute(std::shared_ptr<Variables::Scope> globalScope, std::shared_ptr<Variables::Scope> scope)
        {
            ErrorReporting::Debug::print(getName());
            if (passable->getErrorManager()->count() > 0)
            {
                return nullVariable;
            }
            if (node != nullptr)
            {
                return node->execute(globalScope, scope);
            }
            return nullVariable;
        }

        std::string SemicolonNode::toString()
        {
            std::string output;
            if (node != nullptr)
            {
                output += node->toString();
                if (node->getType() != SEMICOLONNODETYPE)
                {
                    output += ";";
                }
            }
            return output;
        }
    }
}
