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

#include "fakearray.h"

FakeArray2::FakeArray2()
{

}

FakeArray2::FakeArray2(std::string name, double value)
    : Variable(name)
{

}

FakeArray2::FakeArray2(std::string name, long long value)
    : Variable(name)
{

}

void FakeArray2::setValue(double value)
{

}

void FakeArray2::setValue(std::string value)
{

}

void FakeArray2::setValue(long long value)
{

}

double FakeArray2::toDouble()
{
    return 0.0;
}

long long FakeArray2::toInt()
{
    return 0;
}

std::string FakeArray2::toString()
{
    return "";
}

bool FakeArray2::toBool()
{
    return false;
}

VarType FakeArray2::getType()
{
    return ARRAY;
}

double FakeArray2::getValue()
{
    return 0.0;
}

std::shared_ptr<Variable> FakeArray2::pow(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    return null;
}

std::shared_ptr<Variable> FakeArray2::mul(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    return null;
}

std::shared_ptr<Variable> FakeArray2::div(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    return null;
}

std::shared_ptr<Variable> FakeArray2::mod(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    return null;
}

std::shared_ptr<Variable> FakeArray2::add(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    return null;
}

std::shared_ptr<Variable> FakeArray2::sub(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    return null;
}

std::shared_ptr<Variable> FakeArray2::ifUnder(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    return null;
}

std::shared_ptr<Variable> FakeArray2::ifUnderOrEqual(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    return null;
}

std::shared_ptr<Variable> FakeArray2::ifOver(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    return null;
}

std::shared_ptr<Variable> FakeArray2::ifOverOrEqual(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    return null;
}

std::shared_ptr<Variable> FakeArray2::ifEqual(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    return null;
}

std::shared_ptr<Variable> FakeArray2::ifNotEqual(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    return null;
}

std::shared_ptr<Variable> FakeArray2::addEqual(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    return null;
}

std::shared_ptr<Variable> FakeArray2::subEqual(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    return null;
}

std::shared_ptr<Variable> FakeArray2::mulEqual(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    return null;
}

std::shared_ptr<Variable> FakeArray2::divEqual(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    return null;
}

std::shared_ptr<Variable> FakeArray2::equal(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    return null;
}
