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

#include "numbervariable.h"

NumberVariable::NumberVariable(std::shared_ptr<Passable> passable, bool value)
    : Variable(passable)
{
    this->variable = std::move(std::make_shared<IntegerVariable>(passable, (long long)(int)value));
}

NumberVariable::NumberVariable(std::shared_ptr<Passable> passable, std::shared_ptr<Variable> variable)
    : Variable(passable)
{
    this->variable = variable;
}

NumberVariable::NumberVariable(std::shared_ptr<Passable> passable, std::string name, double value)
    : Variable(passable, name)
{
    this->variable = std::move(toInternalValue(value));
}

NumberVariable::NumberVariable(std::shared_ptr<Passable> passable, double value)
    : Variable(passable, "")
{
    this->variable = std::move(toInternalValue(value));
}

NumberVariable::NumberVariable(std::shared_ptr<Passable> passable, long long value)
    : Variable(passable, "")
{
    this->variable = std::move(toInternalValue(value));
}

NumberVariable::NumberVariable(std::shared_ptr<Passable> passable, std::string name, long long value)
    : Variable(passable, name)
{
    this->variable = std::move(toInternalValue(value));
}

NumberVariable::NumberVariable(std::shared_ptr<Passable> passable, std::string name, std::string value)
    : Variable(passable, name)
{
    std::shared_ptr<VariableTypeFactory> v = std::make_shared<VariableTypeFactory>(passable);
    std::shared_ptr<Variable> var = v->newVariable(TypeDetector::getType(value));
    var->setValue(value);
    variable = std::move(var);
}

void NumberVariable::setValue(double value)
{
    this->variable->setValue(value);
}

void NumberVariable::setValue(std::string value)
{
    variable->setValue(value);
}

void NumberVariable::setValue(long long value)
{
    variable->setValue(value);
}

long long NumberVariable::toInt()
{
    return variable->toInt();
}

double NumberVariable::toDouble()
{
    return variable->toDouble();
}

std::string NumberVariable::toString()
{
    return variable->toString();
}

bool NumberVariable::toBool()
{
    return variable->toBool();
}

VarType NumberVariable::getType()
{
    return variable->getType();
}

double NumberVariable::getValue()
{
    return variable->toDouble();
}

bool NumberVariable::isNumber()
{
    return true;
}

std::shared_ptr<Variable> NumberVariable::pow(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr || this->variable == nullptr)
    {
        return null;
    }
    return std::move(toValue(std::move(this->variable->pow(variable))));
}

std::shared_ptr<Variable> NumberVariable::mul(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr || this->variable == nullptr)
    {
        return null;
    }
    return std::move(toValue(std::move(this->variable->mul(variable))));
}

std::shared_ptr<Variable> NumberVariable::div(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr || this->variable == nullptr)
    {
        return null;
    }
    return std::move(toValue(std::move(this->variable->div(variable))));
}

std::shared_ptr<Variable> NumberVariable::mod(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr || this->variable == nullptr)
    {
        return null;
    }
    return std::move(toValue(std::move(this->variable->mod(variable))));
}

std::shared_ptr<Variable> NumberVariable::add(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr || this->variable == nullptr)
    {
        return null;
    }
    return std::move(toValue(std::move(this->variable->add(variable))));
}

std::shared_ptr<Variable> NumberVariable::sub(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr || this->variable == nullptr)
    {
        return null;
    }
    return std::move(toValue(std::move(this->variable->sub(variable))));
}

std::shared_ptr<Variable> NumberVariable::ifUnder(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr || this->variable == nullptr)
    {
        return null;
    }
    return std::move(toValue(this->variable->ifUnder(variable)));
}

std::shared_ptr<Variable> NumberVariable::ifUnderOrEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr || this->variable == nullptr)
    {
        return null;
    }
    return std::move(toValue(std::move(this->variable->ifUnderOrEqual(variable))));
}

std::shared_ptr<Variable> NumberVariable::ifOver(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr || this->variable == nullptr)
    {
        return null;
    }
    return std::move(toValue(std::move(this->variable->ifOver(variable))));
}

std::shared_ptr<Variable> NumberVariable::ifOverOrEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr || this->variable == nullptr)
    {
        return null;
    }
    return std::move(toValue(std::move(this->variable->ifOverOrEqual(variable))));
}

std::shared_ptr<Variable> NumberVariable::ifEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr || this->variable == nullptr)
    {
        return null;
    }
    return std::move(toValue(std::move(this->variable->ifEqual(variable))));
}

std::shared_ptr<Variable> NumberVariable::ifNotEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr || this->variable == nullptr)
    {
        return null;
    }
    return toValue(std::move(this->variable->ifNotEqual(variable)));
}

std::shared_ptr<Variable> NumberVariable::toInternalValue(double value)
{
    if (precision.isSafeInteger(value))
    {
        return std::move(std::make_shared<DoubleVariable>(passable, value));
    }
    else
    {
        if (precision.getType(value) == DOUBLE)
        {
            return std::move(std::make_shared<DoubleVariable>(passable, value));
        }
        return std::move(std::make_shared<IntegerVariable>(passable, value));
    }
}

std::shared_ptr<Variable> NumberVariable::toInternalValue(long long value)
{
    if (precision.isSafeInteger(value))
    {
        return std::move(std::make_shared<DoubleVariable>(passable, value));
    }
    return std::move(std::make_shared<DoubleVariable>(passable, value));
}

std::shared_ptr<Variable> NumberVariable::toValue(std::shared_ptr<Variable> variable)
{
    double value = variable->toDouble();
    if (precision.isSafeInteger(value))
    {
        return std::move(variable);
    }
    else if (precision.getType(value) == INTEGER)
    {
        long long intValue = (long long)value;
        return std::make_shared<NumberVariable>(passable, std::move(std::make_shared<IntegerVariable>(passable, intValue)));
    }
    return std::move(variable);
}

std::shared_ptr<Variable> NumberVariable::increment()
{
    variable->increment();
    return variable;
}

std::shared_ptr<Variable> NumberVariable::decrement()
{
    variable->decrement();
    return variable;
}

std::shared_ptr<Variable> NumberVariable::count()
{
    return variable->count();
}

void NumberVariable::set(std::string index, std::shared_ptr<Variable> value)
{
    variable->set(index, value);
}

std::shared_ptr<Variable> NumberVariable::get(std::string index)
{
    return variable->get(index);
}

void NumberVariable::unset(std::string index)
{
    variable->unset(index);
}

std::shared_ptr<Variable> NumberVariable::copy()
{
    if (variable == nullptr)
    {
        return null;
    }
    return variable->copy();
}

std::shared_ptr<Variable> NumberVariable::bitwiseAnd(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr || this->variable == nullptr)
    {
        return null;
    }
    return this->variable->bitwiseAnd(variable);
}

std::shared_ptr<Variable> NumberVariable::bitwiseOr(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr || this->variable == nullptr)
    {
        return null;
    }
    return this->variable->bitwiseOr(variable);
}

std::shared_ptr<Variable> NumberVariable::bitwiseXOR(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr || this->variable == nullptr)
    {
        return null;
    }
    return this->variable->bitwiseXOR(variable);
}

std::shared_ptr<Variable> NumberVariable::bitwiseComplement()
{
    if (variable == nullptr || this->variable == nullptr)
    {
        return null;
    }
    return this->variable->bitwiseComplement();
}
