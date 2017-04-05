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

#include "errors.h"

Errors::Errors()
{

}

Errors::~Errors()
{
    errorList.clear();
}

void Errors::add(std::string message)
{
    errorList.push_back(std::make_shared<Error>(ERROR, message));
}

void Errors::add(std::shared_ptr<Error> error)
{
    errorList.push_back(error);
}

void Errors::removeAll()
{
    errorList.clear();
}

std::vector<std::shared_ptr<Error>> Errors::get()
{
    return errorList;
}

void Errors::set(std::vector<std::shared_ptr<Error>> errors)
{
    errorList = errors;
}

void Errors::print()
{
    for (std::vector<std::shared_ptr<Error>>::iterator it = errorList.begin(); it != errorList.end(); ++it)
    {
        std::string value = (*it)->getMessage();
        std::cout << value << std::endl;
    }
}

std::vector<std::shared_ptr<Error>> Errors::errorList;

