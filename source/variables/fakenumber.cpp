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

#include "fakenumber.h"

FakeNumber::FakeNumber(std::shared_ptr<Variable> variable)
{
    this->variable = std::move(toValue(variable));
}

FakeNumber::FakeNumber(std::string name, double value)
    : Variable(name)
{
    std::shared_ptr<Variable> v(new FakeDouble(value));
    this->variable = std::move(toValue(v));
}

FakeNumber::FakeNumber(double value)
    : Variable("")
{
    std::shared_ptr<Variable> v(new FakeDouble(value));
    this->variable = std::move(toValue(v));
}

FakeNumber::FakeNumber(long long value)
    : Variable("")
{
    std::shared_ptr<Variable> v(new FakeInt(value));
    this->variable = std::move(toValue(v));
}

FakeNumber::FakeNumber(std::string name, long long value)
    : Variable("")
{
    std::shared_ptr<Variable> v(new FakeInt("",value));
    this->variable = std::move(v);
}

FakeNumber::FakeNumber(std::string name, std::string value)
    : Variable(name)
{
    VariableTypeFactory v;
    std::shared_ptr<Variable> var = v.newVariable(TypeDetector::getType(value));
    var->setValue(value);
    variable = std::move(var);
}

void FakeNumber::setValue(double value)
{
    this->variable->setValue(value);
}

void FakeNumber::setValue(std::string value)
{
    variable->setValue(value);
}

void FakeNumber::setValue(long long value)
{
    variable->setValue(value);
}

long long FakeNumber::toInt()
{
    return variable->toInt();
}

double FakeNumber::toDouble()
{
    return variable->toDouble();
}

std::string FakeNumber::toString()
{
    return variable->toString();
}

bool FakeNumber::toBool()
{
    return variable->toBool();
}

VarType FakeNumber::getType()
{
    return variable->getType();
}

double FakeNumber::getValue()
{
    return variable->toDouble();
}

std::shared_ptr<Variable> FakeNumber::pow(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    if (this->variable == nullptr)
    {
        return null;
    }
    return toValue(this->variable->pow(variable));
}

std::shared_ptr<Variable> FakeNumber::mul(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    if (this->variable == nullptr)
    {
        return null;
    }
    return toValue(this->variable->mul(variable));
}

std::shared_ptr<Variable> FakeNumber::div(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    if (this->variable == nullptr)
    {
        return null;
    }
    return toValue(this->variable->div(variable));
}

std::shared_ptr<Variable> FakeNumber::mod(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    if (this->variable == nullptr)
    {
        return null;
    }
    return toValue(this->variable->mod(variable));
}

std::shared_ptr<Variable> FakeNumber::add(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    if (this->variable == nullptr)
    {
        return null;
    }
    return toValue(this->variable->add(variable));
}

std::shared_ptr<Variable> FakeNumber::sub(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    if (this->variable == nullptr)
    {
        return null;
    }
    return toValue(this->variable->sub(variable));
}

std::shared_ptr<Variable> FakeNumber::ifUnder(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    if (this->variable == nullptr)
    {
        return null;
    }
    return toValue(this->variable->ifUnder(variable));
}

std::shared_ptr<Variable> FakeNumber::ifUnderOrEqual(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    if (this->variable == nullptr)
    {
        return null;
    }
    return toValue(this->variable->ifUnderOrEqual(variable));
}

std::shared_ptr<Variable> FakeNumber::ifOver(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    if (this->variable == nullptr)
    {
        return null;
    }
    return toValue(this->variable->ifOver(variable));
}

std::shared_ptr<Variable> FakeNumber::ifOverOrEqual(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    if (this->variable == nullptr)
    {
        return null;
    }
    return toValue(this->variable->ifOverOrEqual(variable));
}

std::shared_ptr<Variable> FakeNumber::ifEqual(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    if (this->variable == nullptr)
    {
        return null;
    }
    return toValue(this->variable->ifEqual(variable));
}

std::shared_ptr<Variable> FakeNumber::ifNotEqual(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    if (this->variable == nullptr)
    {
        return null;
    }
    return toValue(this->variable->ifNotEqual(variable));
}

std::shared_ptr<Variable> FakeNumber::addEqual(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    return null;
}

std::shared_ptr<Variable> FakeNumber::subEqual(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    return null;
}

std::shared_ptr<Variable> FakeNumber::mulEqual(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    return null;
}

std::shared_ptr<Variable> FakeNumber::divEqual(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    return null;
}

std::shared_ptr<Variable> FakeNumber::equal(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    return null;
}

std::shared_ptr<Variable> FakeNumber::toValue(std::shared_ptr<Variable> variable)
{
    Precision precision;
    return variable;
    double value = variable->toDouble();
    if (precision.getType(value) == INTEGER && !precision.isSafeInteger(value))
    {
        return variable;
    }
    else if (variable->getType() == INTEGER)
    {
        return variable;
    }
    else if (precision.getType(value) == INTEGER)
    {
        long long intValue = (long long)value;
        auto a = std::make_shared<FakeNumber>(std::make_shared<FakeInt>("",intValue));
        return a;
    }
    return variable;
}

