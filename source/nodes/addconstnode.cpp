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

#include "addconstnode.h"

namespace HuwInterpreter {
    namespace Nodes {
        AddConstNode::AddConstNode(std::shared_ptr<Passable> passable, std::shared_ptr<Tokens::Token> token, std::string name, std::shared_ptr<Nodes::Node> value)
            : Node("AddConstNode", passable, token)
        {
	    ErrorReporting::Debug::print("AddConstNode");
            this->name = name;
            this->value = value;
        }

        NodeType AddConstNode::getType()
        {
            return ADDCONSTNODETYPE;
        }

        std::shared_ptr<Variables::Variable> AddConstNode::execute(std::shared_ptr<Variables::Scope> globalScope, std::shared_ptr<Variables::Scope> scope)
        {
            ErrorReporting::Debug::print("AddConstNode");
            if (passable->getErrorManager()->count() > 0)
            {
                return nullVariable;
            }
            if (scope->getReturnValue() != nullptr)
            {
                return scope->getReturnValue();
            }
            if (!scope->getVariableManager()->exists(name))
            {
                std::shared_ptr<Variables::Variable> var = value->execute(globalScope, scope);
                if (passable->getErrorManager()->count() > 0)
                {
                    return nullVariable;
                }
                if (scope->getReturnValue() != nullptr)
                {
                    return scope->getReturnValue();
                }
                if (var != nullptr)
                {
                    if (globalScope->getVariableManager()->exists(name))
                    {
                        passable->getErrorManager()->add(passable->getErrorFactory()->constantDeclared(token, name));
                        return nullVariable;
                    }
                    else if (!scope->getVariableManager()->addVariable(name, std::make_shared<Variables::ConstantVariable>(passable, var)))
                    {
                        passable->getErrorManager()->add(passable->getErrorFactory()->constantDeclared(token, name));
                    }
                }
                else
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->invalidExpression(RUNTIME_ERROR, token, internalName));
                }
                return nullVariable;
            }
            passable->getErrorManager()->add(passable->getErrorFactory()->constantDeclared(token, name));
            return nullVariable;
        }

        std::string AddConstNode::toString()
        {
            std::string output;
            if (value != nullptr)
            {
                output.append("const ").append(name).append("=").append(value->toString());
            }
            return output;
        }
    }
}
