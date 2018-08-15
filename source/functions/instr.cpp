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

#include "instr.h"

namespace HuwInterpreter {
    namespace Functions {
        InStr::InStr(std::shared_ptr<Passable> passable)
            : Function(passable)
        {
            setName("inStr");
        }

        std::shared_ptr<Variable> InStr::execute(std::shared_ptr<Tokens::Token> token, std::shared_ptr<Scope> globalScope,
                                             std::shared_ptr<Scope> scope,
                                             std::vector<std::shared_ptr<Nodes::Node>> arguments)
        {
            if (arguments.size() == 2)
            {
                std::shared_ptr<Nodes::Node> node1 = arguments.at(0);
                std::shared_ptr<Nodes::Node> node2 = arguments.at(1);
                if (node1 == nullptr || node2 == nullptr)
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->invalidArgument(token, RUNTIME_ERROR, name));
                    return nullVariable;
                }

                std::shared_ptr<Variable> var1 = node1->execute(globalScope, scope);
                std::shared_ptr<Variable> var2 = node2->execute(globalScope, scope);

                if (var1 == nullptr || var2 == nullptr)
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->invalidArgument(token, RUNTIME_ERROR, name));
                    return nullVariable;
                }

                std::string str = var1->toString();
                std::string str2 = var2->toString();
                std::size_t found = str.find(str2);
                if (found != std::string::npos)
                {
                    return std::make_shared<DoubleVariable>(passable, (long long)found);
                }
                return std::make_shared<DoubleVariable>(passable, -1.0);
            }
            passable->getErrorManager()->add(passable->getErrorFactory()->requiresArguments(token, name, "", 2));
            return nullVariable;
        }
    }
}

