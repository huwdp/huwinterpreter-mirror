

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

#include "currenttimefunction.h"

namespace HuwInterpreter {
    namespace Functions {
        CurrentTimeFunction::CurrentTimeFunction(std::shared_ptr<Passable> passable)
            : Function(passable)
        {
            setName("currentTime");
        }

        std::shared_ptr<Variable> CurrentTimeFunction::execute(std::shared_ptr<Tokens::Token> token, std::shared_ptr<Scope> globalScope,
                                               std::shared_ptr<Scope> scope,
                                               std::vector<std::shared_ptr<Nodes::Node>> arguments)
        {
            if (arguments.size() > 1)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->requiresAtLeastXArguments(token, name, 0));
                return nullVariable;
            }
            if (arguments.size() == 1)
            {
                std::shared_ptr<Nodes::Node> node = arguments.at(0);
                if (node == nullptr)
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->invalidArgument(token, RUNTIME_ERROR, node->getName()));
                    return nullVariable;
                }
                std::shared_ptr<Variable> var = node->execute(globalScope, scope);
                if (var == nullptr)
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->invalidArgument(token, RUNTIME_ERROR, node->getName()));
                    return nullVariable;
                }
                long int value = (long int)var->toInt();
                time_t t = std::time(&value);
                return std::make_shared<DoubleVariable>(passable, static_cast<double> (t));
            }
            time_t t = std::time(0);
            return std::make_shared<DoubleVariable>(passable, static_cast<double> (t));
        }
    }
}
