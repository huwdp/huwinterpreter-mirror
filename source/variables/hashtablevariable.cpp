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

#include "hashtablevariable.h"

HashTableVariable::HashTableVariable()
{

}

HashTableVariable::HashTableVariable(std::string name, double value)
    : Variable(name)
{

}

HashTableVariable::HashTableVariable(std::string name, long long value)
    : Variable(name)
{

}

void HashTableVariable::setValue(double value)
{

}

void HashTableVariable::setValue(std::string value)
{

}

void HashTableVariable::setValue(long long value)
{

}

double HashTableVariable::toDouble()
{
    return 0.0;
}

long long HashTableVariable::toInt()
{
    return 0;
}

std::string HashTableVariable::toString()
{
    return "";
}

bool HashTableVariable::toBool()
{
    return false;
}

VarType HashTableVariable::getType()
{
    return ARRAY;
}

double HashTableVariable::getValue()
{
    return 0.0;
}

std::shared_ptr<Variable> HashTableVariable::pow(std::shared_ptr<Variable> variable)
{
    Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "Cannot call pow method on an arrap"));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::mul(std::shared_ptr<Variable> variable)
{
    Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "Cannot call mul method on an arrap"));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::div(std::shared_ptr<Variable> variable)
{
    Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "Cannot call div method on an arrap"));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::mod(std::shared_ptr<Variable> variable)
{
    Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "Cannot call mod method on an arrap"));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::add(std::shared_ptr<Variable> variable)
{
    // Todo
    return null;
}

std::shared_ptr<Variable> HashTableVariable::sub(std::shared_ptr<Variable> variable)
{
    Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "Cannot call sub method on an arrap"));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::ifUnder(std::shared_ptr<Variable> variable)
{
    Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "Cannot call ifUnder method on an arrap"));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::ifUnderOrEqual(std::shared_ptr<Variable> variable)
{
    Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "Cannot call ifUnderOrEqual method on an arrap"));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::ifOver(std::shared_ptr<Variable> variable)
{
    Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "Cannot call ifOver method on an arrap"));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::ifOverOrEqual(std::shared_ptr<Variable> variable)
{
    Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "Cannot call ifOverOrEqual method on an arrap"));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::ifEqual(std::shared_ptr<Variable> variable)
{
    Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "Cannot call ifEqual method on an arrap"));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::ifNotEqual(std::shared_ptr<Variable> variable)
{
    Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "Cannot call ifNotEqual method on an arrap"));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::addEqual(std::shared_ptr<Variable> variable)
{
    // Todo
    return null;
}

std::shared_ptr<Variable> HashTableVariable::subEqual(std::shared_ptr<Variable> variable)
{
    Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "Cannot substract an array"));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::mulEqual(std::shared_ptr<Variable> variable)
{
    Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "Cannot multiply an array"));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::divEqual(std::shared_ptr<Variable> variable)
{
    Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "Cannot divide an array"));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::equal(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(toString() == variable->toString()));
}

std::shared_ptr<Variable> HashTableVariable::count()
{
    return std::make_shared<NumberVariable>((long long)this->map.size());
}

std::shared_ptr<Variable> HashTableVariable::increment()
{
    Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "Cannot decrement an array"));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::decrement()
{
    Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "Cannot increment an array"));
    return null;
}

void HashTableVariable::set(std::string index, std::shared_ptr<Variable> value)
{
    map[index] = std::move(value);
}

std::shared_ptr<Variable> HashTableVariable::get(std::string index)
{
    return map[index];
}

void HashTableVariable::unset(std::string index)
{
    map.erase(index);
}
