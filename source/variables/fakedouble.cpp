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

#include "fakedouble.h"

FakeDouble::FakeDouble()
{

}

FakeDouble::FakeDouble(double value)
    : Variable("")
{
    this->value = value;
}

FakeDouble::FakeDouble(std::string name, double value)
    : Variable(name)
{
    this->value = value;
}

void FakeDouble::setValue(double value)
{
    this->value = value;
}

void FakeDouble::setValue(std::string value)
{
    try
    {
        this->value = stod(value);
    }
    catch (const std::exception& e)
    {
        Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "Could not convert string to integer"));
    }
}

void FakeDouble::setValue(long long value)
{
    try
    {
        this->value = (double)value;
    }
    catch (const std::exception& e)
    {
        Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "Could not convert integer to integer"));
    }
}

long long FakeDouble::toInt()
{
    return (long long)value;
}

double FakeDouble::toDouble()
{
    return value;
}

std::string FakeDouble::toString()
{
    Precision precision;
    if (precision.getType(value) == INTEGER)
    {
        return std::to_string(toInt());
    }
    std::stringstream ss;
    ss << std::fixed << std::setprecision(6) << value;
    return ss.str();
}

bool FakeDouble::toBool()
{
    if (value != double(0))
    {
        return true;
    }
    return false;
}

VarType FakeDouble::getType()
{
    return DOUBLE;
}

double FakeDouble::getValue()
{
    return value;
}

std::shared_ptr<Variable> FakeDouble::pow(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        std::shared_ptr<Variable> null;
        return null;
    }
    std::shared_ptr<Variable> temp(new FakeNumber((double)std::pow(this->toDouble(),variable->toDouble())));
    return temp;
}

std::shared_ptr<Variable> FakeDouble::mul(std::shared_ptr<Variable> variable)
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

std::shared_ptr<Variable> FakeDouble::div(std::shared_ptr<Variable> variable)
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

std::shared_ptr<Variable> FakeDouble::mod(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        std::shared_ptr<Variable> null;
        return null;
    }
    auto a = std::shared_ptr<FakeNumber>(new FakeNumber( fmod(this->toDouble(), variable->toDouble())));
    return (a);
}

std::shared_ptr<Variable> FakeDouble::add(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        std::shared_ptr<Variable> null;
        return null;
    }
    std::shared_ptr<Variable> temp(new FakeNumber(std::make_shared<FakeDouble>()));
    double temp2 = this->toDouble() + variable->toDouble();
    temp->setValue(temp2);
    return temp;
}

std::shared_ptr<Variable> FakeDouble::sub(std::shared_ptr<Variable> variable)
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

std::shared_ptr<Variable> FakeDouble::ifUnder(std::shared_ptr<Variable> variable)
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

std::shared_ptr<Variable> FakeDouble::ifUnderOrEqual(std::shared_ptr<Variable> variable)
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

std::shared_ptr<Variable> FakeDouble::ifOver(std::shared_ptr<Variable> variable)
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

std::shared_ptr<Variable> FakeDouble::ifOverOrEqual(std::shared_ptr<Variable> variable)
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

std::shared_ptr<Variable> FakeDouble::ifEqual(std::shared_ptr<Variable> variable)
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

std::shared_ptr<Variable> FakeDouble::ifNotEqual(std::shared_ptr<Variable> variable)
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

std::shared_ptr<Variable> FakeDouble::addEqual(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    return null;
}

std::shared_ptr<Variable> FakeDouble::subEqual(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    return null;
}

std::shared_ptr<Variable> FakeDouble::mulEqual(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    return null;
}

std::shared_ptr<Variable> FakeDouble::divEqual(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    return null;
}

std::shared_ptr<Variable> FakeDouble::equal(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    return null;
}
