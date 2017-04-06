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

#include "fakestring.h"

FakeString::FakeString()
{

}

FakeString::FakeString(std::string name, std::string value)
    : Variable(name)
{
    this->value = value;
}

void FakeString::setValue(double value)
{
    this->value = std::to_string(value);
}

void FakeString::setValue(std::string value)
{
    this->value = value;
}

void FakeString::setValue(long long value)
{
    this->value = value;
}

double FakeString::toDouble()
{
    double value = 0.0;
    try
    {
        value = stod(this->value);
    }
    catch (const std::exception& ex)
    {

    }
    return value;
}

std::string FakeString::toString()
{
    return value;
}

long long FakeString::toInt()
{
    return 0;
}

bool FakeString::toBool()
{
    if (value != "0")
    {
        return true;
    }
    else
    {
        return false;
    }
}

VarType FakeString::getType()
{
    return STRING;
}

std::string FakeString::getValue()
{
    return value;
}

std::shared_ptr<Variable> FakeString::pow(std::shared_ptr<Variable> variable)
{
    Debug::print("Cannot power strings");
    std::shared_ptr<Variable> null;
    return null;
}

std::shared_ptr<Variable> FakeString::mul(std::shared_ptr<Variable> variable)
{
    Debug::print("Cannot combine multiple strings");
    std::shared_ptr<Variable> null;
    return null;
}

std::shared_ptr<Variable> FakeString::div(std::shared_ptr<Variable> variable)
{
    Debug::print("Cannot divide strings");
    std::shared_ptr<Variable> null;
    return null;
}

std::shared_ptr<Variable> FakeString::mod(std::shared_ptr<Variable> variable)
{
    Debug::print("Cannot mod strings");
    std::shared_ptr<Variable> null;
    return null;
}

std::shared_ptr<Variable> FakeString::add(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        std::shared_ptr<Variable> null;
        return null;
    }
    std::shared_ptr<FakeString> temp(new FakeString());
    temp.get()->setValue(this->toString() + variable->toString());
    return (temp);
}

std::shared_ptr<Variable> FakeString::sub(std::shared_ptr<Variable> variable)
{
    Debug::print("Cannot subtract strings");
    std::shared_ptr<Variable> null;
    return null;
}

std::shared_ptr<Variable> FakeString::ifUnder(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        std::shared_ptr<Variable> null;
        return null;
    }
    if (TypeDetector::isNumeric(toString()))
    {
        std::shared_ptr<Variable> var = VariableTypeFactory::newVariable(TypeDetector::getType(value));
        var->setValue(toString());

        return var->ifUnder(variable);
    }
    std::shared_ptr<FakeNumber> temp(new FakeNumber(std::make_shared<FakeInt>()));
    if (this->toString().compare(variable->toString()) < 0)
    {
        temp.get()->setValue(double(1));
    }
    else
    {
        temp->setValue(double(0));
    }
    return (temp);
}

std::shared_ptr<Variable> FakeString::ifUnderOrEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        std::shared_ptr<Variable> null;
        return null;
    }
    if (TypeDetector::isNumeric(toString()))
    {
        std::shared_ptr<Variable> var = VariableTypeFactory::newVariable(TypeDetector::getType(value));
        var->setValue(toString());
        return var->ifUnderOrEqual(variable);
    }
    std::shared_ptr<FakeNumber> temp(new FakeNumber(std::make_shared<FakeInt>()));
    if (this->toString().compare(variable->toString()) <= 0)
    {
        temp->setValue(double(1));
    }
    else
    {
        temp->setValue(double(0));
    }
    return (temp);
}

std::shared_ptr<Variable> FakeString::ifOver(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        std::shared_ptr<Variable> null;
        return null;
    }
    if (TypeDetector::isNumeric(toString()))
    {
        std::shared_ptr<Variable> var = VariableTypeFactory::newVariable(TypeDetector::getType(value));
        var->setValue(toString());
        return var->ifOver(variable);
    }
    std::shared_ptr<FakeNumber> temp(new FakeNumber(std::make_shared<FakeInt>()));
    if (this->toString().compare(variable->toString()) > 0)
    {
        temp->setValue(double(1));
    }
    else
    {
        temp->setValue(double(0));
    }
    return (temp);
}

std::shared_ptr<Variable> FakeString::ifOverOrEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        std::shared_ptr<Variable> null;
        return null;
    }
    if (TypeDetector::isNumeric(toString()))
    {
        std::shared_ptr<Variable> var = VariableTypeFactory::newVariable(TypeDetector::getType(value));
        var->setValue(toString());
        return var->ifOverOrEqual(variable);
    }
    std::shared_ptr<FakeNumber> temp(new FakeNumber(std::make_shared<FakeInt>()));
    if (this->toString().compare(variable->toString()) >= 0)
    {
        temp->setValue(double(1));
    }
    else
    {
        temp->setValue(double(0));
    }
    return (temp);
}

std::shared_ptr<Variable> FakeString::ifEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        std::shared_ptr<Variable> null;
        return null;
    }
    if (TypeDetector::isNumeric(toString()))
    {
        std::shared_ptr<Variable> var = VariableTypeFactory::newVariable(TypeDetector::getType(value));
        var->setValue(toString());
        return var->ifEqual(variable);
    }
    std::shared_ptr<FakeNumber> temp(new FakeNumber(std::make_shared<FakeInt>()));
    if (this->toString().compare(variable->toString()) == 0)
    {
        temp->setValue(double(1));
    }
    else
    {
        temp->setValue(double(0));
    }
    return (temp);
}

std::shared_ptr<Variable> FakeString::ifNotEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        std::shared_ptr<Variable> null;
        return null;
    }
    if (TypeDetector::isNumeric(toString()))
    {
        std::shared_ptr<Variable> var = VariableTypeFactory::newVariable(TypeDetector::getType(value));
        var->setValue(toString());
        return var->ifNotEqual(variable);
    }
    std::shared_ptr<FakeNumber> temp(new FakeNumber(std::make_shared<FakeInt>()));
    if (this->toString().compare(variable->toString()) != 0)
    {
        temp->setValue(double(1));
    }
    else
    {
        temp->setValue(double(0));
    }
    return (temp);
}

std::shared_ptr<Variable> FakeString::addEqual(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    return null;
}

std::shared_ptr<Variable> FakeString::subEqual(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    return null;
}

std::shared_ptr<Variable> FakeString::mulEqual(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    return null;
}

std::shared_ptr<Variable> FakeString::divEqual(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    return null;
}

std::shared_ptr<Variable> FakeString::equal(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable == nullptr)
    {
        return null;
    }
    return null;
}
