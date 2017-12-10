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

#include "getfuncnode.h"

namespace HuwInterpreter {
    namespace Nodes {
        GetFuncNode::GetFuncNode(std::shared_ptr<Passable> passable, std::shared_ptr<Tokens::Token> token, std::string name, std::shared_ptr<Functions::FunctionManager> functionManager, std::vector<std::shared_ptr<Nodes::Node>> arguments)
            : Node("GetFuncNode", passable, token)
        {
            this->name = name;
            this->functionManager = functionManager;
            this->arguments = arguments;
            ErrorReporting::Debug::print("GetFuncNode");
        }

        NodeType GetFuncNode::getType()
        {
            return GETFUNCNODETYPE;
        }

        std::shared_ptr<Variables::Variable> GetFuncNode::execute(std::shared_ptr<Variables::Scope> globalScope, std::shared_ptr<Variables::Scope> scope)
        {
            ErrorReporting::Debug::print("GetFuncNode");
            if (passable->getErrorManager()->count() > 0)
            {
                return null;
            }
            if (scope->getReturnValue() != nullptr)
            {
                return scope->getReturnValue();
            }
            std::shared_ptr<Functions::Function> func = functionManager->get(name);
            if (func != nullptr)
            {
                return func->execute(token, globalScope, scope, arguments);
                if (passable->getErrorManager()->count() > 0)
                {
                    return null;
                }
                return scope->getReturnValue();
            }
            passable->getErrorManager()->add(passable->getErrorFactory()->functionNotDeclared(token, name));
            return null;
        }

        std::string GetFuncNode::toString()
        {
            std::string output;
            output.append(name).append("(");
            for (std::vector<std::shared_ptr<Nodes::Node>>::iterator it = arguments.begin(); it != arguments.end(); ++it)
            {
                if ((*it) != nullptr)
                {
                    output.append((*it)->toString());
                    if (it != arguments.end())
                    {
                        ++it;
                        if (it != arguments.end())
                        {
                            output.append(",");
                        }
                        --it;
                    }
                }
            }
            return output.append(")");
        }
    }
}
