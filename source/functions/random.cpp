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

std::shared_ptr<Variable> Random::run(std::shared_ptr<Token> token,
                                      std::shared_ptr<Scope> scope,
                                      std::vector<std::shared_ptr<Node>> variables)
{
    std::shared_ptr<Variable> answer;
    if (variables.size() == 0)
    {
        std::srand(std::time(0));
        int number = std::rand();
        double value = (double)number;
        answer = std::make_shared<FakeNumber>(value);
    }
    else
    {
        Errors::add(std::make_shared<Error>(FUNCTION_ERROR, "Random requires 0 arguments", token));
    }
    
    return answer;
}
