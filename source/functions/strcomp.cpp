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

#include "strcomp.h"

namespace HuwInterpreter {
    namespace Functions {
        StrComp::StrComp(std::shared_ptr<Passable> passable)
            : Function(passable)
        {
            name = "strCmp";
        }

        std::shared_ptr<Variable> StrComp::execute(std::shared_ptr<Tokens::Token> token, std::shared_ptr<Scope> globalScope,
                                               std::shared_ptr<Scope> scope,
                                               std::vector<std::shared_ptr<Nodes::Node>> arguments)
        {
            std::shared_ptr<Variable> returnNode;
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

                std::string str1 = var1->toString();
                std::string str2 = var2->toString();
                double diff = double(str1.compare(str2));
                returnNode = std::make_shared<NumberVariable>(passable, diff);
            }
            else
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->requiresArguments(token, name, "", 2));
            }

            return returnNode;
        }
    }
}
