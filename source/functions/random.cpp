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

#include "random.h"

namespace HuwInterpreter {
    namespace Functions {
        Random::Random(std::shared_ptr<Passable> passable)
            : Function(passable)
        {
            name = "random";
        }

        std::shared_ptr<Variable> Random::execute(std::shared_ptr<Tokens::Token> token, std::shared_ptr<Scope> globalScope,
                                              std::shared_ptr<Scope> scope,
                                              std::vector<std::shared_ptr<Nodes::Node>> arguments)
        {
            std::shared_ptr<Variable> returnNode;
            if (arguments.size() == 0)
            {
                std::srand(std::time(0));
                int number = std::rand();
                double value = (double)number;
                returnNode = std::make_shared<NumberVariable>(passable, value);
            }
            else
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->requiresArguments(token, name, "", 0));
            }

            return returnNode;
        }
    }
}
