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

#include "setvarnode.h"

namespace HuwInterpreter {
    namespace Nodes {
        SetVarNode::SetVarNode(std::shared_ptr<Passable> passable, std::shared_ptr<Tokens::Token> token, std::string name, std::shared_ptr<Nodes::Node> value)
            : Node("SetVarNode", passable, token)
        {
            ErrorReporting::Debug::print("SetVarNode");
            this->name = name;
            this->value = value;
        }

        NodeType SetVarNode::getType()
        {
            return SETVARNODETYPE;
        }

        std::shared_ptr<Variables::Variable> SetVarNode::execute(std::shared_ptr<Variables::Scope> globalScope, std::shared_ptr<Variables::Scope> scope)
        {
            ErrorReporting::Debug::print("SetVarNode");
            if (passable->getErrorManager()->count() > 0)
            {
                return nullVariable;
            }
            if (scope->getReturnValue() != nullptr)
            {
                return scope->getReturnValue();
            }
            std::shared_ptr<Variables::Variable> v = value->execute(globalScope, scope);

            std::shared_ptr<Variables::Variable> globalVar = globalScope->getVariableManager()->get(name);
            std::shared_ptr<Variables::Variable> localVar = globalScope->getVariableManager()->get(name);

            if (globalScope->getVariableManager()->exists(name))
            {

                if (globalVar != nullptr && globalVar->isConst())
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->cannotChangeConstant(token, name));
                    return nullVariable;
                }

                if (v != nullptr)
                {
                    globalScope->getVariableManager()->setVariable(name, v->copy(token));
                }
                else
                {
                    globalScope->getVariableManager()->setVariable(name, nullVariable);
                }
            }
            else if (scope->getVariableManager()->exists(name))
            {
                if (localVar != nullptr && localVar->isConst())
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->cannotChangeConstant(token, name));
                    return nullVariable;
                }

                std::shared_ptr<Variable> var = scope->getVariableManager()->get(name);

                if (v != nullptr)
                {
                    if (var->isRef())
                    {
                        var->setValue(v->copy(token));
                    }
                    else
                    {
                        scope->getVariableManager()->setVariable(name, v->copy(token));
                    }
                }
                else
                {
                    scope->getVariableManager()->setVariable(name, nullVariable);
                }
            }
            else
            {
                if (globalVar != nullptr && globalVar->isConst())
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->cannotChangeConstant(token, name));
                }
                else if (localVar != nullptr && localVar->isConst())
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->cannotChangeConstant(token, name));
                }
                else
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->variableDeclared(token, name));
                }
            }
            return nullVariable;
        }

        std::string SetVarNode::toString()
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

