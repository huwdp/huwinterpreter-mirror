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

#include "getvarnode.h"

namespace HuwInterpreter {
    namespace Nodes {
        GetVarNode::GetVarNode(std::shared_ptr<Passable> passable, std::shared_ptr<Tokens::Token> token, std::string name)
            : Node("GetVarNode", passable, token)
        {
	    ErrorReporting::Debug::print("GetVarNode");
            this->name = name;
            ErrorReporting::Debug::print("GetVarNode");
        }

        NodeType GetVarNode::getType()
        {
            return GETVARNODETYPE;
        }

        std::shared_ptr<Variables::Variable> GetVarNode::execute(std::shared_ptr<Variables::Scope> globalScope, std::shared_ptr<Variables::Scope> scope)
        {
            ErrorReporting::Debug::print("GetVarNode");
            if (passable->getErrorManager()->count() > 0)
            {
                return nullVariable;
            }
            if (scope->getReturnValue() != nullptr)
            {
                return scope->getReturnValue();
            }

            std::shared_ptr<Variables::Variable> var1 = globalScope->getVariableManager()->get(name);
            if (var1 != nullptr)
            {
                return var1;
            }

            std::shared_ptr<Variables::Variable> var2 = scope->getVariableManager()->get(name);
            if (var2 != nullptr)
            {
                return var2;
            }
            else
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->variableNotDeclared(token, name));
                return nullVariable;
            }
            ErrorReporting::Debug::print("Could not find variable.");
            return nullVariable;
        }

        std::string GetVarNode::toString()
        {
            return name;
        }
    }
}
