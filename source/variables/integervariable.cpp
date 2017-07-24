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

#include "integervariable.h"

IntegerVariable::IntegerVariable()
{
    value = 0;
}

IntegerVariable::IntegerVariable(long long value)
    : Variable("")
{
    this->value = value;
}

IntegerVariable::IntegerVariable(std::string name, long long value)
    : Variable(name)
{
    this->value = value;
}

void IntegerVariable::setValue(double value)
{
    this->value = (long long)value;
}

void IntegerVariable::setValue(std::string value)
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

void IntegerVariable::setValue(long long value)
{
    this->value = value;
}

double IntegerVariable::toDouble()
{
    return (double)value;
}

long long IntegerVariable::toInt()
{
    return value;
}

std::string IntegerVariable::toString()
{
    return std::to_string(value);
}

bool IntegerVariable::toBool()
{
    if (value != 0)
    {
        return true;
    }
    return false;
}

VarType IntegerVariable::getType()
{
    return INTEGER;
}

double IntegerVariable::getValue()
{
    return value;
}

std::shared_ptr<Variable> IntegerVariable::pow(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(std::pow(this->toDouble(),variable->toDouble())));
}

std::shared_ptr<Variable> IntegerVariable::mul(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(this->toDouble() * variable->toDouble()));
}

std::shared_ptr<Variable> IntegerVariable::div(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(this->toDouble() / variable->toDouble()));
}

std::shared_ptr<Variable> IntegerVariable::mod(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        
        return null;
    }
    return std::make_shared<NumberVariable>(fmod(this->toDouble(), variable->toDouble()));
}

std::shared_ptr<Variable> IntegerVariable::add(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(this->toDouble() + variable->toDouble()));
}

std::shared_ptr<Variable> IntegerVariable::sub(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(this->toDouble() - variable->toDouble()));
}

std::shared_ptr<Variable> IntegerVariable::ifUnder(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(this->toDouble() < variable->toDouble()));
}

std::shared_ptr<Variable> IntegerVariable::ifUnderOrEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(this->toDouble() <= variable->toDouble()));
}

std::shared_ptr<Variable> IntegerVariable::ifOver(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(this->toDouble() > variable->toDouble()));
}

std::shared_ptr<Variable> IntegerVariable::ifOverOrEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(this->toDouble() >= variable->toDouble()));
}

std::shared_ptr<Variable> IntegerVariable::ifEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(this->toDouble() == variable->toDouble()));
}

std::shared_ptr<Variable> IntegerVariable::ifNotEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(std::make_shared<DoubleVariable>(this->toDouble() != variable->toDouble())));
}

std::shared_ptr<Variable> IntegerVariable::increment()
{
    this->value++;
    return std::move(std::make_shared<NumberVariable>(this->toDouble()));
}

std::shared_ptr<Variable> IntegerVariable::decrement()
{
    this->value--;
    return std::move(std::make_shared<NumberVariable>(this->toDouble()));
}

std::shared_ptr<Variable> IntegerVariable::count()
{
    Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "Cannot call count method on integer"));
    return null;
}

void IntegerVariable::set(std::string index, std::shared_ptr<Variable> value)
{
    Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "Cannot call set method on integer type. Integer is not an array"));
}

std::shared_ptr<Variable> IntegerVariable::get(std::string value)
{
    Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "Cannot call get method on integer type. Integer is not an array"));
    return null;
}

void IntegerVariable::unset(std::string index)
{
    Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "Cannot call unset method on integer type. Integer is not an array"));
}

std::shared_ptr<Variable> IntegerVariable::copy()
{
    return std::move(std::make_shared<IntegerVariable>(value));
}
