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

#include "scope.h"

Scope::Scope(std::shared_ptr<Passable> passable)
{
    variables = std::move(std::make_shared<Variables>(passable, false));
}

Scope::Scope(std::shared_ptr<Variables> variables)
{
    variables = std::move(variables);
}

std::shared_ptr<Variables> Scope::getVariables()
{
    return variables;
}

void Scope::setVariables(std::shared_ptr<Variables> variables)
{
    this->variables = variables;
}

std::shared_ptr<Variable> Scope::getReturnValue()
{
    return returnValue;
}

void Scope::setReturnValue(std::shared_ptr<Variable> value)
{
    this->returnValue = value;
}
