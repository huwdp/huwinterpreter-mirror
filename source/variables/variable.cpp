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

#include "variable.h"

Variable::Variable(std::shared_ptr<Passible> passible)
{
    this->passible = passible;
}

Variable::Variable(std::shared_ptr<Passible> passible, std::string name)
{
    this->passible = passible;
    this->name = name;
}

std::string Variable::getName()
{
	return name;
}

void Variable::setName(std::string name)
{
	this->name = name;
}
