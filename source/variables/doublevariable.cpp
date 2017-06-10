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

#include "doublevariable.h"

DoubleVariable::DoubleVariable()
{

}

DoubleVariable::DoubleVariable(double value)
    : Variable("")
{
    this->value = value;
}

DoubleVariable::DoubleVariable(std::string name, double value)
    : Variable(name)
{
    this->value = value;
}

void DoubleVariable::setValue(double value)
{
    this->value = value;
}

void DoubleVariable::setValue(std::string value)
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

void DoubleVariable::setValue(long long value)
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

long long DoubleVariable::toInt()
{
    return (long long)value;
}

double DoubleVariable::toDouble()
{
    return value;
}

std::string DoubleVariable::toString()
{
    Precision precision;
    if (precision.getType(value) == INTEGER)
    {
        return std::to_string(toInt());
    }
    return std::to_string(value);
}

bool DoubleVariable::toBool()
{
    if (value != double(0))
    {
        return true;
    }
    return false;
}

VarType DoubleVariable::getType()
{
    return DOUBLE;
}

double DoubleVariable::getValue()
{
    return value;
}

std::shared_ptr<Variable> DoubleVariable::pow(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    std::shared_ptr<Variable> temp(new NumberVariable((double)std::pow(this->toDouble(),variable->toDouble())));
    return std::move(temp);
}

std::shared_ptr<Variable> DoubleVariable::mul(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(this->toDouble() * variable->toDouble()));
}

std::shared_ptr<Variable> DoubleVariable::div(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(this->toDouble() / variable->toDouble()));
}

std::shared_ptr<Variable> DoubleVariable::mod(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::make_shared<NumberVariable>(fmod(this->toDouble(), variable->toDouble()));
}

std::shared_ptr<Variable> DoubleVariable::add(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::make_shared<NumberVariable>(this->toDouble() + variable->toDouble());
}

std::shared_ptr<Variable> DoubleVariable::sub(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(this->toDouble() - variable->toDouble()));
}

std::shared_ptr<Variable> DoubleVariable::ifUnder(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(this->toDouble() < variable->toDouble()));
}

std::shared_ptr<Variable> DoubleVariable::ifUnderOrEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(this->toDouble() <= variable->toDouble()));
}

std::shared_ptr<Variable> DoubleVariable::ifOver(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(this->toDouble() > variable->toDouble()));
}

std::shared_ptr<Variable> DoubleVariable::ifOverOrEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(this->toDouble() >= variable->toDouble()));
}

std::shared_ptr<Variable> DoubleVariable::ifEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(this->toDouble() == variable->toDouble()));
}

std::shared_ptr<Variable> DoubleVariable::ifNotEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(this->toDouble() != variable->toDouble()));
}

std::shared_ptr<Variable> DoubleVariable::increment()
{
    this->value++;
    return std::move(std::make_shared<NumberVariable>(this->toDouble()));
}

std::shared_ptr<Variable> DoubleVariable::count()
{
    Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "Cannot call count method on double"));
    return null;
}

std::shared_ptr<Variable> DoubleVariable::decrement()
{
    this->value--;
    return std::move(std::make_shared<NumberVariable>(this->toDouble()));
}

void DoubleVariable::set(std::string index, std::shared_ptr<Variable> value)
{
    Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "Cannot call set method on double type"));
}

std::shared_ptr<Variable> DoubleVariable::get(std::string value)
{
    Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "Cannot call get method on double type. Double is not an array"));
}

void DoubleVariable::unset(std::string index)
{
    Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "Cannot call unset method on double type. Double is not an array"));
}
