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

#include "passable.h"

Passable::Passable()
{
    this->errors = std::make_shared<Errors>();
    this->errorFactory = std::make_shared<ErrorFactory>();
}

std::shared_ptr<Errors> Passable::getErrors()
{
    return errors;
}

void Passable::setErrors(std::shared_ptr<Errors> errors)
{
    this->errors = std::move(errors);
}

std::shared_ptr<ErrorFactory> Passable::getErrorFactory()
{
    return errorFactory;
}

void Passable::setErrorFactory(std::shared_ptr<ErrorFactory> errorFactory)
{
    this->errorFactory = std::move(errorFactory);
}
