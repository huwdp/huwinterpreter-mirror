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

#include "clockfunction.h"

namespace HuwInterpreter {
    namespace Functions {
        ClockFunction::ClockFunction(std::shared_ptr<Passable> passable)
            : Function(passable)
        {
            setName("clock");
        }

        std::shared_ptr<Variable> ClockFunction::execute(std::shared_ptr<Tokens::Token> token, std::shared_ptr<Scope> globalScope,
                                               std::shared_ptr<Scope> scope,
                                               std::vector<std::shared_ptr<Nodes::Node>> arguments)
        {
            if (arguments.size() != 0)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->requiresArguments(token, name, getName(), 0));
                return nullVariable;
            }
            return std::make_shared<DoubleVariable>(passable, (long long)std::clock());
        }
    }
}
