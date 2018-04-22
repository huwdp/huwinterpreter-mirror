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

#include "arraysetnode.h"

namespace HuwInterpreter {
    namespace Nodes {
        ArraySetNode::ArraySetNode(std::shared_ptr<Passable> passable,
                                   std::shared_ptr<Tokens::Token> token,
                                   std::shared_ptr<Nodes::Node> array,
                                   std::queue<std::shared_ptr<Nodes::Node>> indexes,
                                   std::shared_ptr<Node> value)
            : Node("ArraySetNode", passable, token)
        {
            this->array = array;
            this->indexes = indexes;
            this->value = value;
        }

        NodeType ArraySetNode::getType()
        {
            return ARRAYSETNODE;
        }

        std::shared_ptr<Variables::Variable> ArraySetNode::execute(std::shared_ptr<Variables::Scope> globalScope, std::shared_ptr<Variables::Scope> scope)
        {
            if (array == nullptr)
            {
                return nullVariable;
            }

            std::shared_ptr<Variable> var = array->execute(globalScope, scope);

            if (!var->isArray())
            {
                // Throw error
                return nullVariable;
            }

            if (indexes.size() == 0)
            {
                return nullVariable;
            }

            while (indexes.size() > 1)
            {
                if (indexes.front() == nullptr)
                {
                    return nullVariable;
                }

                std::shared_ptr<Variable> index = indexes.front()->execute(globalScope, scope);
                indexes.pop();

                if (index == nullptr)
                {
                    return nullVariable;
                }

                std::shared_ptr<Variable> variable = var->get(index->toString(), token);

                if (variable == nullptr)
                {
                    std::shared_ptr<Variable> newHashTable = std::make_shared<Variables::HashTableVariable>(passable);
                    var->set(index->toString(), newHashTable, token);
                    //var = var->get(index->toString(), token);
                }

                var = var->get(index->toString(), token);
            }

            if (indexes.front() == nullptr)
            {
                return nullVariable;
            }

            std::shared_ptr<Variable> finalIndex = indexes.front()->execute(globalScope, scope);
            indexes.pop(); // Cleanup

            if (finalIndex == nullptr)
            {
                return nullVariable;
            }
            var->set(finalIndex->toString(), this->value->execute(globalScope, scope), this->token);
            return nullVariable;
        }

        std::string ArraySetNode::toString()
        {
            return "";
        }
    }
}
