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
    std::stringstream ss;
    if (precision.getType(value) == INTEGER)
    {
        ss << toInt();
        return ss.str();
    }
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
        return null;
    }
    std::shared_ptr<Variable> temp(new FakeNumber((double)std::pow(this->toDouble(),variable->toDouble())));
    return std::move(temp);
}

std::shared_ptr<Variable> FakeDouble::mul(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<FakeNumber>(this->toDouble() * variable->toDouble()));
}

std::shared_ptr<Variable> FakeDouble::div(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<FakeNumber>(this->toDouble() / variable->toDouble()));
}

std::shared_ptr<Variable> FakeDouble::mod(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::make_shared<FakeNumber>(fmod(this->toDouble(), variable->toDouble()));
}

std::shared_ptr<Variable> FakeDouble::add(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::make_shared<FakeNumber>(this->toDouble() + variable->toDouble());
}

std::shared_ptr<Variable> FakeDouble::sub(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<FakeNumber>(this->toDouble() - variable->toDouble()));
}

std::shared_ptr<Variable> FakeDouble::ifUnder(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<FakeNumber>(this->toDouble() < variable->toDouble()));
}

std::shared_ptr<Variable> FakeDouble::ifUnderOrEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<FakeNumber>(this->toDouble() <= variable->toDouble()));
}

std::shared_ptr<Variable> FakeDouble::ifOver(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<FakeNumber>(this->toDouble() > variable->toDouble()));
}

std::shared_ptr<Variable> FakeDouble::ifOverOrEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<FakeNumber>(this->toDouble() >= variable->toDouble()));
}

std::shared_ptr<Variable> FakeDouble::ifEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<FakeNumber>(this->toDouble() == variable->toDouble()));
}

std::shared_ptr<Variable> FakeDouble::ifNotEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        
        return null;
    }
    return std::move(std::make_shared<FakeNumber>(this->toDouble() != variable->toDouble()));
}

std::shared_ptr<Variable> FakeDouble::addEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return null;
}

std::shared_ptr<Variable> FakeDouble::subEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return null;
}

std::shared_ptr<Variable> FakeDouble::mulEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return null;
}

std::shared_ptr<Variable> FakeDouble::divEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return null;
}

std::shared_ptr<Variable> FakeDouble::equal(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return null;
}
