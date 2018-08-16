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

#include "floor.h"

namespace HuwInterpreter {
    namespace Functions {
        Floor::Floor(std::shared_ptr<Passable> passable)
            : Function(passable)
        {
            setName("floor");
        }

        std::shared_ptr<Variable> Floor::execute(std::shared_ptr<Tokens::Token> token, std::shared_ptr<Scope> globalScope,
                                             std::shared_ptr<Scope> scope,
                                             std::vector<std::shared_ptr<Nodes::Node>> arguments)
        {
            if (arguments.size() == 1)
            {
                std::shared_ptr<Nodes::Node> node = arguments.at(0);
                if (node == nullptr)
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->invalidArgument(token, RUNTIME_ERROR, name));
                    return nullVariable;
                }

                std::shared_ptr<Variable> var = node->execute(globalScope, scope);
                if (var == nullptr)
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->invalidArgument(token, RUNTIME_ERROR, name));
                    return nullVariable;
                }
                try
                {
                    double temp = var->toDouble();
                    double output = std::floor(temp);
                    return std::make_shared<DoubleVariable>(passable, output);
                }
                catch (const std::invalid_argument& ex)
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->invalidArgument(token, FUNCTION_ERROR, name, ex.what()));
                }
                catch (const std::out_of_range& ex)
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->outOfRange(token, name, ex.what()));
                }
                catch (const std::exception& ex)
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->otherFunctionError(token, name, ex.what()));
                }
                return nullVariable;
            }
            passable->getErrorManager()->add(passable->getErrorFactory()->requiresArguments(token, name, "", 1));
            return nullVariable;
        }
    }
}
