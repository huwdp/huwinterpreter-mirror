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

#include "command.h"

namespace HuwInterpreter {
    namespace Functions {
        Command::Command(std::shared_ptr<Passable> passable)
            : Function(passable)
        {
            setName("command");
        }

        std::shared_ptr<Variable> Command::execute(std::shared_ptr<Tokens::Token> token, std::shared_ptr<Scope> globalScope,
                                               std::shared_ptr<Scope> scope,
                                               std::vector<std::shared_ptr<Nodes::Node>> arguments)
        {
            if (arguments.size() == 0)
            {
                ErrorReporting::Debug::print("Command function requires at least 1 argument");
                passable->getErrorManager()->add(passable->getErrorFactory()->requiresAtLeastXArguments(token, name, 1));
                return nullVariable;
            }
            for (std::vector<std::shared_ptr<Nodes::Node>>::iterator it = arguments.begin(); it != arguments.end(); ++it)
            {
                if ((*it) != nullptr)
                {
                    std::shared_ptr<Variable> var = (*it)->execute(globalScope, scope);
                    if (var == nullptr)
                    {
                        passable->getErrorManager()->add(passable->getErrorFactory()->invalidArgument(token, RUNTIME_ERROR, name));
                        return nullVariable;
                    }
                    return std::make_shared<DoubleVariable>(passable, system(var->toString().c_str()));
                }
            }
            return nullVariable;
        }
    }
}
