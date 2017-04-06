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

#include "fakeint.h"

FakeInt::FakeInt()
{
    value = 0;
}

FakeInt::FakeInt(long long value)
    : Variable("")
{
    this->value = value;
}

FakeInt::FakeInt(std::string name, long long value)
    : Variable(name)
{
    this->value = value;
}

void FakeInt::setValue(double value)
{
    this->value = (long long)value;
}

void FakeInt::setValue(std::string value)
{
    try
    {
        this->value = std::stoll(value);
    }
    catch (const std::exception& e)
    {
        Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "Could not convert string to integer"));
    }
}

void FakeInt::setValue(long long value)
{
    this->value = value;
}

double FakeInt::toDouble()
{
    return (double)value;
}

long long FakeInt::toInt()
{
    return value;
}

std::string FakeInt::toString()
{
    return std::to_string(value);
}

bool FakeInt::toBool()
{
    if (value != 0)
    {
        return true;
    }
    return false;
}

VarType FakeInt::getType()
{
    return INTEGER;
}

double FakeInt::getValue()
{
    return value;
}

std::shared_ptr<Variable> FakeInt::pow(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        std::shared_ptr<Variable> null;
        return null;
    }
    std::shared_ptr<Variable> temp(new FakeNumber(std::pow(this->toDouble(),variable->toDouble())));
    return temp;
}

std::shared_ptr<Variable> FakeInt::mul(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        std::shared_ptr<Variable> null;
        return null;
    }
    std::shared_ptr<Variable> temp(new FakeNumber(std::make_shared<FakeDouble>()));
    temp->setValue((this->toDouble() * variable->toDouble()));
    return temp;
}

std::shared_ptr<Variable> FakeInt::div(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        std::shared_ptr<Variable> null;
        return null;
    }
    std::shared_ptr<Variable> temp(new FakeNumber(std::make_shared<FakeDouble>()));
    temp->setValue(this->toDouble() / variable->toDouble());
    return temp;
}

std::shared_ptr<Variable> FakeInt::mod(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        std::shared_ptr<Variable> null;
        return null;
    }
    auto a = std::shared_ptr<FakeNumber>(new FakeNumber( fmod(this->toDouble(), variable->toDouble())));
    return (a);
}

std::shared_ptr<Variable> FakeInt::add(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        std::shared_ptr<Variable> null;
        return null;
    }
    std::shared_ptr<Variable> temp(new FakeNumber(std::make_shared<FakeDouble>()));
    temp->setValue(this->toDouble() + variable->toDouble());
    return temp;
}

std::shared_ptr<Variable> FakeInt::sub(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        std::shared_ptr<Variable> null;
        return null;
    }
    std::shared_ptr<Variable> temp(new FakeNumber(std::make_shared<FakeDouble>()));
    temp->setValue(this->toDouble() - variable->toDouble());
    return temp;
}

std::shared_ptr<Variable> FakeInt::ifUnder(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        std::shared_ptr<Variable> null;
        return null;
    }
    std::shared_ptr<Variable> temp(new FakeNumber(std::make_shared<FakeDouble>()));
    if (this->toDouble() < variable->toDouble())
    {
        temp->setValue(double(1));
    }
    else
        temp->setValue(double(0));
    return temp;
}

std::shared_ptr<Variable> FakeInt::ifUnderOrEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        std::shared_ptr<Variable> null;
        return null;
    }
    std::shared_ptr<Variable> temp(new FakeNumber(std::make_shared<FakeDouble>()));
    if (this->toDouble() <= variable->toDouble())
    {
        temp->setValue(double(1));
    }
    else
        temp->setValue(double(0));
    return temp;
}

std::shared_ptr<Variable> FakeInt::ifOver(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        std::shared_ptr<Variable> null;
        return null;
    }
    std::shared_ptr<Variable> temp(new FakeNumber(std::make_shared<FakeDouble>()));
    if (this->toDouble() > variable->toDouble())
    {
        temp->setValue(double(1));
    }
    else
        temp->setValue(double(0));
    return temp;
}

std::shared_ptr<Variable> FakeInt::ifOverOrEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        std::shared_ptr<Variable> null;
        return null;
    }
    std::shared_ptr<Variable> temp(new FakeNumber(std::make_shared<FakeDouble>()));
    if (this->toDouble() >= variable->toDouble())
    {
        temp->setValue(double(1));
    }
    else
        temp->setValue(double(0));
    return temp;
}

std::shared_ptr<Variable> FakeInt::ifEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        std::shared_ptr<Variable> null;
        return null;
    }
    std::shared_ptr<Variable> temp(new FakeNumber(std::make_shared<FakeDouble>()));
    if (this->toDouble() == variable->toDouble())
    {
        temp->setValue(double(1));
    }
    else
        temp->setValue(double(0));
    return temp;
}

std::shared_ptr<Variable> FakeInt::ifNotEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        std::shared_ptr<Variable> null;
        return null;
    }
    std::shared_ptr<Variable> temp(new FakeNumber(std::make_shared<FakeDouble>()));
    if (this->toDouble() != variable->toDouble())
    {
        temp->setValue(double(1));
    }
    else
        temp->setValue(double(0));
    return temp;
}

std::shared_ptr<Variable> FakeInt::addEqual(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    return null;
}

std::shared_ptr<Variable> FakeInt::subEqual(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    return null;
}

std::shared_ptr<Variable> FakeInt::mulEqual(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    return null;
}

std::shared_ptr<Variable> FakeInt::divEqual(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    return null;
}

std::shared_ptr<Variable> FakeInt::equal(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    return null;
}
