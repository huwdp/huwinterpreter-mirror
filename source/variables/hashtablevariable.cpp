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

HashTableVariable::HashTableVariable(std::shared_ptr<Passable> passable)
    : Variable(passable)
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
    std::string output = "[";
    for (std::unordered_map<std::string, std::shared_ptr<Variable>>::iterator it = map.begin(); it != map.end(); ++it)
    {
        output.append("Key:" + (*it).first + " Value:" + (*it).second->toString());
    }
    output.append("]");
    return output;
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

bool HashTableVariable::isNumber()
{
    return false;
}

std::shared_ptr<Variable> HashTableVariable::pow(std::shared_ptr<Variable> variable)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "pow", ""));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::mul(std::shared_ptr<Variable> variable)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "multiply", ""));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::div(std::shared_ptr<Variable> variable)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "divide", ""));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::mod(std::shared_ptr<Variable> variable)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "mod", ""));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::add(std::shared_ptr<Variable> variable)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "add", ""));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::sub(std::shared_ptr<Variable> variable)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "subtract", ""));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::ifUnder(std::shared_ptr<Variable> variable)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "ifUnder", ""));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::ifUnderOrEqual(std::shared_ptr<Variable> variable)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "ifUnderOrEqual", ""));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::ifOver(std::shared_ptr<Variable> variable)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "ifOver", ""));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::ifOverOrEqual(std::shared_ptr<Variable> variable)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "ifOverOrEqual", ""));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::ifEqual(std::shared_ptr<Variable> variable)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "ifEqual", ""));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::ifNotEqual(std::shared_ptr<Variable> variable)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "ifNotEqual", ""));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::addEqual(std::shared_ptr<Variable> variable)
{
    // Todo
    return null;
}

std::shared_ptr<Variable> HashTableVariable::subEqual(std::shared_ptr<Variable> variable)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "subequal", ""));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::mulEqual(std::shared_ptr<Variable> variable)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "mulequal", ""));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::divEqual(std::shared_ptr<Variable> variable)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "divequal", ""));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::equal(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(passable, toString() == variable->toString()));
}

std::shared_ptr<Variable> HashTableVariable::count()
{
    return std::make_shared<NumberVariable>(passable, (long long)this->map.size());
}

std::shared_ptr<Variable> HashTableVariable::increment()
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "decrement", ""));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::decrement()
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "increment", ""));
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

std::shared_ptr<Variable> HashTableVariable::copy()
{
    std::shared_ptr<HashTableVariable> map = std::make_shared<HashTableVariable>(passable);
    for (std::unordered_map<std::string, std::shared_ptr<Variable>>::iterator it = this->map.begin(); it != this->map.end(); ++it)
    {
        map->set((*it).first, (*it).second->copy());
    }
    return map;
}

std::shared_ptr<Variable> HashTableVariable::bitwiseAnd(std::shared_ptr<Variable> variable)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "bitwiseAnd", "Cannot bitwsieAND array type"));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::bitwiseOr(std::shared_ptr<Variable> variable)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "bitwiseOr", "Cannot bitwiseOR array type"));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::bitwiseXOR(std::shared_ptr<Variable> variable)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "bitwiseXOR", "Cannot bitwsieXOR array type"));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::bitwiseComplement()
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "bitwiseXOR", "Cannot bitwiseComplement array type"));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::leftShift(std::shared_ptr<Variable> variable)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "leftShift", "Cannot leftShift array type"));
    return null;
}

std::shared_ptr<Variable> HashTableVariable::rightShift(std::shared_ptr<Variable> variable)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(name, "rightShift", "Cannot rightShift array type"));
    return null;
}
