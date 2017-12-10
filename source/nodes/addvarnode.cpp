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

#include "addvarnode.h"

namespace HuwInterpreter {
    namespace Nodes {
        AddVarNode::AddVarNode(std::shared_ptr<Passable> passable, std::shared_ptr<Tokens::Token> token, std::string name, std::shared_ptr<Nodes::Node> value)
            : Node("AddVarNode", passable, token)
        {
            this->name = name;
            this->value = value;
            ErrorReporting::Debug::print("AddVarNode");
        }

        NodeType AddVarNode::getType()
        {
            return ADDVARNODETYPE;
        }

        std::shared_ptr<Variables::Variable> AddVarNode::execute(std::shared_ptr<Variables::Scope> globalScope, std::shared_ptr<Variables::Scope> scope)
        {
            ErrorReporting::Debug::print("AddVarNode");
            if (passable->getErrorManager()->count() > 0)
            {
                return null;
            }
            if (scope->getReturnValue() != nullptr)
            {
                return scope->getReturnValue();
            }
            if (scope->getVariableManager()->exists(name))
            {
                std::shared_ptr<Variables::Variable> v = value->execute(globalScope, scope);
                if (v != nullptr)
                {
                    scope->getVariableManager()->setVariable(name, v->copy(token));
                }
                else
                {
                    scope->getVariableManager()->setVariable(name, null);
                }
            }
            else
            {
                std::shared_ptr<Variables::Variable> var;
                var = value->execute(globalScope, scope);
                if (passable->getErrorManager()->count() > 0)
                {
                    return null;
                }
                if (scope->getReturnValue() != nullptr)
                {
                    return scope->getReturnValue();
                }

                if (var != nullptr)
                {
                    if (globalScope->getVariableManager()->exists(name))
                    {
                        passable->getErrorManager()->add(passable->getErrorFactory()->variableDeclared(token, name));
                        return null;
                    }
                    else if (!scope->getVariableManager()->addVariable(name, var))
                    {
                        passable->getErrorManager()->add(passable->getErrorFactory()->variableNotDeclared(token, name));
                    }
                }
                else
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->invalidExpression(RUNTIME_ERROR, token, internalName));
                }
            }
            return null;
        }

        std::string AddVarNode::toString()
        {
            std::string output;
            if (value != nullptr)
            {
                output.append("let ").append(name).append("=").append(value->toString());
            }
            return output;
        }
    }
}
