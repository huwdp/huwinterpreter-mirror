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

#include "variables.h"

Variables::Variables(bool isEmpty)
{
    addDefaultVariables(isEmpty);
}

Variables::~Variables()
{
    variables.clear();
}

void Variables::addDefaultVariables(bool isEmpty)
{
    if (!isEmpty)
    {
        addVariable(std::move(std::make_shared<ConstantVariable>(std::make_shared<NumberVariable>("PI", 3.14159265358979))));
        addVariable(std::move(std::make_shared<ConstantVariable>(std::make_shared<NumberVariable>("e", 2.718281828459045))));
        addVariable(std::move(std::make_shared<ConstantVariable>(std::make_shared<NumberVariable>("y", 0.577215664901532))));
        addVariable(std::move(std::make_shared<ConstantVariable>(std::make_shared<NumberVariable>("Φ", 1.618033988749894))));
        addVariable(std::move(std::make_shared<ConstantVariable>(std::make_shared<NumberVariable>("φ", 0.618033988749894))));
        addVariable(std::move(std::make_shared<ConstantVariable>(std::make_shared<NumberVariable>("δs", 2.41421356237309))));
        addVariable(std::move(std::make_shared<ConstantVariable>(std::make_shared<NumberVariable>("ρ", 1.324717957244746))));
    }
}

std::shared_ptr<Variable> Variables::get(std::string name)
{
    std::unordered_map<std::string,std::shared_ptr<Variable>>::const_iterator got = variables.find(name);
    if (got == variables.end())
    {
        return null;
    }
    else
    {
        return std::move(got->second);
    }
}

std::shared_ptr<Variable> Variables::exists(std::string name)
{
    std::unordered_map<std::string,std::shared_ptr<Variable>>::const_iterator got = variables.find(name);
    if (got == variables.end())
    {
        return null;
    }
    else
    {
        return got->second;
    }
}

std::shared_ptr<Variable> Variables::exists(std::shared_ptr<Variable> variable)
{
    if (variable == nullptr)
    {
        return null;
    }
    std::shared_ptr<Variable> e = exists(variable->getName());
    if (e != nullptr)
    {
        return e;
    }
    return null;
}

bool Variables::addVariable(std::shared_ptr<Variable> variable)
{
    if (variable != nullptr)
    {
        std::shared_ptr<Variable> e = exists(variable->getName());
        if (e == nullptr)
        {
            std::string name = variable->getName();
            variables[name] = std::move(variable);
            return true;
        }
    }
    return false;
}

bool Variables::addVariable(std::string name, std::shared_ptr<Variable> variable)
{
    if (variable != nullptr)
    {
        std::shared_ptr<Variable> e = exists(name);
        if (e == nullptr)
        {
            variable->setName(name);
            variables[name] = std::move(variable);
            return true;
        }
    }
    return false;
}

bool Variables::removeVariable(std::shared_ptr<Variable> variable)
{
    if (variable != nullptr)
    {
        std::shared_ptr<Variable> e = exists(variable->getName());
        if (e != nullptr)
        {
            this->variables.erase(variable->getName());
            return true;
        }
    }
    return false;
}

bool Variables::removeVariable(std::string name)
{
    std::shared_ptr<Variable> e = exists(name);
    if (e != nullptr)
    {
        this->variables.erase(name);
        return true;
    }
    return false;
}

bool Variables::setVariable(std::string name, std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> e = exists(name);
    if (e == nullptr)
    {
        return false;
    }
    this->variables[name] = std::move(variable);
    return true;
}
