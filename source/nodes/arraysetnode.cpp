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
                                   std::vector<std::shared_ptr<Nodes::Node>> indexes,
                                   std::shared_ptr<Node> value)
            : Node("ArraySetNode", passable, token)
        {
            ErrorReporting::Debug::print("ArraySetNode");
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
                //passable->getErrorManager()->add(passable->getErrorFactory()->variableNotDeclared(token, ""));
                return nullVariable;
            }

            std::shared_ptr<Variable> var = array->execute(globalScope, scope);

            /*if (var != nullptr)
            {
                //passable->getErrorManager()->add(passable->getErrorFactory()->invalidExpression(RUNTIME_ERROR, token, array->getName()));
                return nullVariable;
            }*/

            if (!var->isArray())
            {
                //passable->getErrorManager()->add(passable->getErrorFactory()->isNotAnArray(token, var->getName()));
                return nullVariable;
            }

            if (indexes.size() == 0)
            {
                //passable->getErrorManager()->add(passable->getErrorFactory()->requiresAtLeastXArguments(token, var->getName(), 1));
                return nullVariable;
            }

            std::vector<std::shared_ptr<Nodes::Node>>::iterator indexIt = indexes.begin();

            if (indexes.size() > 1)
            {
                while (indexIt != (indexes.end()-1))
                {
                    if ((*indexIt) == nullptr)
                    {
                        return nullVariable;
                    }

                    std::shared_ptr<Variable> index = (*indexIt)->execute(globalScope, scope);

                    if (index == nullptr)
                    {
                        // Report here error here. Index cannot be null
                        return nullVariable;
                    }

                    std::shared_ptr<Variable> variable = var->get(index->toString(), token);

                    if (variable == nullptr)
                    {
                        std::shared_ptr<Variable> newHashTable = std::make_shared<Variables::HashTableVariable>(passable);
                        var->set(index->toString(), std::move(newHashTable), token);
                    }

                    var = var->get(index->toString(), token);
                    ++indexIt;
                }
                //--indexIt;
            }

            if ((*indexIt) == nullptr)
            {
                //passable->getErrorManager()->add(passable->getErrorFactory()->invalidArgument(token, RUNTIME_ERROR, array->getName()));
                return nullVariable;
            }

            std::shared_ptr<Variable> finalIndex = (*indexIt)->execute(globalScope, scope);

            if (finalIndex == nullptr)
            {
                return nullVariable;
            }
            var->set(finalIndex->toString(), this->value->execute(globalScope, scope), this->token);
            return nullVariable;
        }

        std::string ArraySetNode::toString()
        {
            std::string output;
            if (array == nullptr)
            {
                return "";
            }
            output = array->toString();

            for (std::vector<std::shared_ptr<Nodes::Node>>::iterator it = indexes.begin(); it != indexes.end(); ++it)
            {
                output += ("[" + (*it)->toString() + "]");
            }

            if (value == nullptr)
            {
                return output;
            }
            output += ("=" + value->toString());
            return output;
        }
    }
}
