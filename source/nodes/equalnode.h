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

#ifndef EQUALNODE_H
#define EQUALNODE_H

#include "node.h"
#include "setvarnode.h"

namespace HuwInterpreter {
    namespace Nodes {
        class EqualNode : public Node
        {
        protected:
            std::shared_ptr<Nodes::Node> left;
            std::shared_ptr<Nodes::Node> right;
            std::shared_ptr<Nodes::Node> next;
            std::shared_ptr<Variables::Scope> scope;
        public:
            EqualNode(std::shared_ptr<Passable> passable, std::shared_ptr<Tokens::Token> token, std::shared_ptr<Nodes::Node> left, std::shared_ptr<Nodes::Node> right, std::shared_ptr<Nodes::Node> next, std::shared_ptr<Variables::Scope> scope);
            NodeType getType();
            std::shared_ptr<Variables::Variable> execute(std::shared_ptr<Variables::Scope> globalScope, std::shared_ptr<Variables::Scope> scope);
            std::string toString();
        };
    }
}

#endif // EQUALNODE_H
