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

#include "stringvariable.h"

StringVariable::StringVariable(std::shared_ptr<Passable> passable)
    : Variable(passable)
{
    variableTypeFactory = std::make_shared<VariableTypeFactory>(passable);
}

StringVariable::StringVariable(std::shared_ptr<Passable> passable, std::string value)
    : Variable(passable, "")
{
    this->value = value;
    variableTypeFactory = std::make_shared<VariableTypeFactory>(passable);
}

StringVariable::StringVariable(std::shared_ptr<Passable> passable, char value)
    : Variable(passable, "")
{
    this->value = std::to_string(value);
    variableTypeFactory = std::make_shared<VariableTypeFactory>(passable);
}

StringVariable::StringVariable(std::shared_ptr<Passable> passable, std::string name, std::string value)
    : Variable(passable, name)
{
    this->value = value;
    variableTypeFactory = std::make_shared<VariableTypeFactory>(passable);
}

StringVariable::StringVariable(std::shared_ptr<Passable> passable, std::string name, char value)
    : Variable(passable, name)
{
    this->value = std::to_string(value);
    variableTypeFactory = std::make_shared<VariableTypeFactory>(passable);
}

void StringVariable::setValue(double value)
{
    this->value = std::to_string(value);
}

void StringVariable::setValue(std::string value)
{
    this->value = value;
}

void StringVariable::setValue(long long value)
{
    this->value = value;
}

double StringVariable::toDouble()
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

std::string StringVariable::toString()
{
    return value;
}

long long StringVariable::toInt()
{
    int value = 0.0;
    try
    {
        value = stol(this->value);
    }
    catch (const std::exception& ex)
    {

    }
    return value;
}

bool StringVariable::toBool()
{
    if (value != "0")
    {
        return true;
    }
    return false;
}

VarType StringVariable::getType()
{
    return STRING;
}

std::string StringVariable::getValue()
{
    return value;
}

bool StringVariable::isNumber()
{
    return false;
}

std::shared_ptr<Variable> StringVariable::pow(std::shared_ptr<Variable> variable)
{
    Debug::print("Cannot call power method on string");
    return null;
}

std::shared_ptr<Variable> StringVariable::mul(std::shared_ptr<Variable> variable)
{
    Debug::print("Cannot call multiple method on string");
    return null;
}

std::shared_ptr<Variable> StringVariable::div(std::shared_ptr<Variable> variable)
{
    Debug::print("Cannot call divide method on string");
    return null;
}

std::shared_ptr<Variable> StringVariable::mod(std::shared_ptr<Variable> variable)
{
    Debug::print("Cannot call mod method on string");
    return null;
}

std::shared_ptr<Variable> StringVariable::add(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::make_shared<StringVariable>(passable, this->toString() + variable->toString());
}

std::shared_ptr<Variable> StringVariable::sub(std::shared_ptr<Variable> variable)
{
    Debug::print("Cannot call subtract method on string");
    return null;
}

std::shared_ptr<Variable> StringVariable::ifUnder(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    if (TypeDetector::isNumeric(toString()))
    {
        std::shared_ptr<Variable> var = variableTypeFactory->newVariable(TypeDetector::getType(value));
        var->setValue(toString());
        return var->ifUnder(variable);
    }
    std::shared_ptr<IntegerVariable> temp = std::make_shared<IntegerVariable>(passable);
    if (this->toString().compare(variable->toString()) < 0)
    {
        temp->setValue(double(1));
    }
    else
    {
        temp->setValue(double(0));
    }
    return temp;
}

std::shared_ptr<Variable> StringVariable::ifUnderOrEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    if (TypeDetector::isNumeric(toString()))
    {
        std::shared_ptr<Variable> var = variableTypeFactory->newVariable(TypeDetector::getType(value));
        var->setValue(toString());
        return var->ifUnderOrEqual(variable);
    }
    std::shared_ptr<IntegerVariable> temp = std::make_shared<IntegerVariable>(passable);
    if (this->toString().compare(variable->toString()) <= 0)
    {
        temp->setValue(double(1));
    }
    else
    {
        temp->setValue(double(0));
    }
    return temp;
}

std::shared_ptr<Variable> StringVariable::ifOver(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    if (TypeDetector::isNumeric(toString()))
    {
        std::shared_ptr<Variable> var = variableTypeFactory->newVariable(TypeDetector::getType(value));
        var->setValue(toString());
        return var->ifOver(variable);
    }
    std::shared_ptr<IntegerVariable> temp = std::make_shared<IntegerVariable>(passable);
    if (this->toString().compare(variable->toString()) > 0)
    {
        temp->setValue(double(1));
    }
    else
    {
        temp->setValue(double(0));
    }
    return temp;
}

std::shared_ptr<Variable> StringVariable::ifOverOrEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    if (TypeDetector::isNumeric(toString()))
    {
        std::shared_ptr<Variable> var = variableTypeFactory->newVariable(TypeDetector::getType(value));
        var->setValue(toString());
        return var->ifOverOrEqual(variable);
    }
    std::shared_ptr<IntegerVariable> temp = std::make_shared<IntegerVariable>(passable);
    if (this->toString().compare(variable->toString()) >= 0)
    {
        temp->setValue(double(1));
    }
    else
    {
        temp->setValue(double(0));
    }
    return temp;
}

std::shared_ptr<Variable> StringVariable::ifEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    if (TypeDetector::isNumeric(toString()))
    {
        std::shared_ptr<Variable> var = variableTypeFactory->newVariable(TypeDetector::getType(value));
        var->setValue(toString());
        return var->ifEqual(variable);
    }
    std::shared_ptr<IntegerVariable> temp = std::make_shared<IntegerVariable>(passable);
    if (this->toString().compare(variable->toString()) == 0)
    {
        temp->setValue(double(1));
    }
    else
    {
        temp->setValue(double(0));
    }
    return temp;
}

std::shared_ptr<Variable> StringVariable::ifNotEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    if (TypeDetector::isNumeric(toString()))
    {
        std::shared_ptr<Variable> var = variableTypeFactory->newVariable(TypeDetector::getType(value));
        var->setValue(toString());
        return var->ifNotEqual(variable);
    }
    std::shared_ptr<IntegerVariable> temp = std::make_shared<IntegerVariable>(passable);
    if (this->toString().compare(variable->toString()) != 0)
    {
        temp->setValue(double(1));
    }
    else
    {
        temp->setValue(double(0));
    }
    return temp;
}

std::shared_ptr<Variable> StringVariable::addEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    std::string value = this->value;
    value.append(variable->toString());
    return std::make_shared<StringVariable>(passable, value);
}

std::shared_ptr<Variable> StringVariable::subEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return null;
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "subEqual", ""));
}

std::shared_ptr<Variable> StringVariable::mulEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "mulEqual", ""));
    return null;
}

std::shared_ptr<Variable> StringVariable::divEqual(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "divEqual", ""));
    return null;
}

std::shared_ptr<Variable> StringVariable::equal(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    if (value.compare(variable->toString()) == 0)
    {
        return std::make_shared<NumberVariable>(passable, true);
    }
    return std::make_shared<NumberVariable>(passable, false);
}

std::shared_ptr<Variable> StringVariable::increment()
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "increment", ""));
    return null;
}

std::shared_ptr<Variable> StringVariable::decrement()
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "decrement", ""));
    return null;
}

std::shared_ptr<Variable> StringVariable::count()
{
    return std::make_shared<NumberVariable>(passable, (long long)value.size());
}

void StringVariable::set(std::string index, std::shared_ptr<Variable> value)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "set", "String is not an array"));
}

std::shared_ptr<Variable> StringVariable::get(std::string value)
{
    long index = 0;
    try
    {
        index = stol(value);
    }
    catch (const std::exception& e)
    {
        passable->errors->add(passable->errorFactory->couldNotConvertStringToNumber(name, "get", e.what()));
    }

    if (this->value.length() >= index)
    {
        std::string character;
        character.append(1, (char)this->value.at(index));
        return std::make_shared<StringVariable>(passable, character);
    }
    passable->errors->add(passable->errorFactory->outOfBounds(name));
    return null;
}

void StringVariable::unset(std::string index)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "unset", "String is not an array"));
}

std::shared_ptr<Variable> StringVariable::copy()
{
    return std::make_shared<StringVariable>(passable, value);
}

std::shared_ptr<Variable> StringVariable::bitwiseAnd(std::shared_ptr<Variable> variable)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "bitwiseAnd", "Cannot bitwiseAND string type"));
    return null;
}

std::shared_ptr<Variable> StringVariable::bitwiseOr(std::shared_ptr<Variable> variable)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "bitwiseOr", "Cannot bitwiseOR string type"));
    return null;
}

std::shared_ptr<Variable> StringVariable::bitwiseXOR(std::shared_ptr<Variable> variable)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "bitwiseOr", "Cannot bitwiseXOR string type"));
    return null;
}
