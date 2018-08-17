#include "timeformatfunction.h"

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

#include "timeformatfunction.h"

namespace HuwInterpreter {
    namespace Functions {
        TimeFormatFunction::TimeFormatFunction(std::shared_ptr<Passable> passable)
            : Function(passable)
        {
            setName("timeFormat");
        }

        std::shared_ptr<Variable> TimeFormatFunction::execute(std::shared_ptr<Tokens::Token> token, std::shared_ptr<Scope> globalScope,
                                           std::shared_ptr<Scope> scope,
                                           std::vector<std::shared_ptr<Nodes::Node>> arguments)
        {
            if (arguments.size()== 0)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->requiresAtLeastXArguments(token, getName(), 1));
                return nullVariable;
            }
            if (arguments.size() > 2)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->requiresAtLeastXArguments(token, getName(), 1));
                return nullVariable;
            }

            std::shared_ptr<Nodes::Node> arg1 = arguments.at(0);

            if (arg1 == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->invalidArgument(token, RUNTIME_ERROR, arg1->getName()));
                return nullVariable;
            }

            std::shared_ptr<Variable> argVar1 = arg1->execute(globalScope, scope);
            long int value = argVar1->toInt();
            if (arguments.size() == 2)
            {
                std::shared_ptr<Nodes::Node> arg2 = arguments.at(1);

                if (arg2 == nullptr)
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->invalidArgument(token, RUNTIME_ERROR, arg1->getName()));
                    return nullVariable;
                }

                std::shared_ptr<Variable> argVar2 = arg2->execute(globalScope, scope);

                if (argVar2 == nullptr)
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->invalidArgument(token, RUNTIME_ERROR, arg2->getName()));
                    return nullVariable;
                }
                std::ostringstream output;
                output << std::put_time(std::localtime(&value),argVar2->toString().c_str());
                return std::make_shared<StringVariable>(passable,output.str());
            }
            std::ostringstream output;
            output << std::put_time(std::localtime(&value),"%c %Z");    // UTC
            return std::make_shared<StringVariable>(passable,output.str());
        }
    }
}
