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

#include "ifnode.h"

namespace HuwInterpreter {
    namespace Nodes {
        IfNode::IfNode(std::shared_ptr<Passable> passable, std::shared_ptr<Tokens::Token> token, std::shared_ptr<Nodes::Node> condition, std::shared_ptr<Nodes::Node> body, std::shared_ptr<Nodes::Node> elseNode)
            : Node("IfNode", passable, token)
        {
            ErrorReporting::Debug::print("IfNode");
            this->condition = condition;
            this->body = body;
            this->elseNode = elseNode;
        }

        NodeType IfNode::getType()
        {
            return IFNODETYPE;
        }

        std::shared_ptr<Variables::Variable> IfNode::execute(std::shared_ptr<Variables::Scope> globalScope, std::shared_ptr<Variables::Scope> scope)
        {
            ErrorReporting::Debug::print("IfNode");
            if (passable->getErrorManager()->count() > 0)
            {
                return nullVariable;
            }
            if (scope->getReturnValue() != nullptr)
            {
                return scope->getReturnValue();
            }
            std::shared_ptr<Variables::Variable> c = condition->execute(globalScope, scope);
            if (c != nullptr)
            {
                if (c->toBool())
                {
                    if (body != nullptr)
                    {
                        body->execute(globalScope, scope);
                        if (passable->getErrorManager()->count() > 0)
                        {
                            return nullVariable;
                        }
                        if (scope->getReturnValue() != nullptr)
                        {
                            return scope->getReturnValue();
                        }
                    }
                    else
                    {
                        passable->getErrorManager()->add(passable->getErrorFactory()->invalidExpression(RUNTIME_ERROR, token, internalName));
                    }
                }
                else
                {
                    if (elseNode != nullptr)
                    {
                        elseNode->execute(globalScope, scope);
                        if (passable->getErrorManager()->count() > 0)
                        {
                            return nullVariable;
                        }
                        if (scope->getReturnValue() != nullptr)
                        {
                            return scope->getReturnValue();
                        }
                    }
                }
            }
            else
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, internalName));
            }
            return nullVariable;
        }

        std::string IfNode::toString()
        {
            std::string output;
            output.append("if (");
            if (condition != nullptr)
            {
                output.append(condition->toString());
            }
            output.append("){");
            if (body != nullptr)
            {
                output.append(body->toString());
            }
            output.append("}");
            if (elseNode != nullptr)
            {
                output.append("else").append("{").append(elseNode->toString()).append("}");
            }
            return output;
        }
    }
}
