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
    parent = nullptr;
    addDefaltVariables(isEmpty);
}

Variables::Variables(std::shared_ptr<Variables> parent, bool isEmpty)
{
    this->parent = parent;
    addDefaltVariables(isEmpty);
}

Variables::~Variables()
{
    variables.clear();
}

void Variables::addDefaltVariables(bool isEmpty)
{
    if (!isEmpty)
    {
        /*
        addVariable(std::move(std::shared_ptr<FakeNumber>(new FakeNumber("PI", 3.14159265358979))));
        addVariable(std::shared_ptr<FakeNumber>(new FakeNumber("e", 2.718281828459045)));
        addVariable(std::shared_ptr<FakeNumber>(new FakeNumber("y", 0.577215664901532)));
        addVariable(std::shared_ptr<FakeNumber>(new FakeNumber("Φ", 1.618033988749894)));
        addVariable(std::shared_ptr<FakeNumber>(new FakeNumber("φ", 0.618033988749894)));
        addVariable(std::shared_ptr<FakeNumber>(new FakeNumber("δs", 2.41421356237309)));
        addVariable(std::shared_ptr<FakeNumber>(new FakeNumber("ρ", 1.324717957244746)));
        */
    }
}

std::shared_ptr<Variable> Variables::get(std::string name)
{
    std::shared_ptr<Variable> null;
    if (parent != nullptr)
    {
        std::shared_ptr<Variable> variable = parent->get(name);
        if (variable != nullptr)
        {
            return variable;
        }
    }
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

bool Variables::set(std::string name, std::string value)
{
    if (parent != nullptr && parent->exists(name))
    {
        return parent->set(name, value);
    }
    std::unordered_map<std::string,std::shared_ptr<Variable>>::const_iterator got = variables.find(name);
    if (got == variables.end())
    {
        return false;
    }
    else
    {
        got->second->setValue(value);
        return true;
    }
}

std::shared_ptr<Variable> Variables::exists(std::string name)
{
    std::shared_ptr<Variable> null;
    std::shared_ptr<Variable> variable;
    if (parent != nullptr)
    {
        variable = parent->exists(name);
        if (variable != nullptr)
        {
            return variable;
        }
    }
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

std::shared_ptr<Variable> Variables::exists(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> null;
    if (variable.get() == nullptr)
    {
        return null;
    }
    if (parent != nullptr)
    {
        std::shared_ptr<Variable> exist = parent->exists(variable->getName());
        if (exist != nullptr)
        {
            return exist;
        }
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
    std::shared_ptr<Variable> e = exists(variable->getName());
    if (e == nullptr)
    {
        std::string name = variable->getName();
        variables[name] = std::move(variable);
        return true;
    }
    return false;
}

bool Variables::addVariable(std::string name, std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> e = exists(variable->getName());
    if (e == nullptr)
    {
        variable->setName(name);
        variables[name] = std::move(variable);
        return true;
    }
    return false;
}

bool Variables::addVariable(std::string name, std::string value)
{
    std::shared_ptr<Variable> e = exists(name);
    if (e == nullptr)
    {
        bool isNum = TypeDetector::isNumeric(value);
        std::shared_ptr<Variable> var;
        if (isNum)
        {
            std::shared_ptr<FakeNumber> a(new FakeNumber(name, value));
            var = std::move(a);
        }
        else
        {
            std::shared_ptr<FakeString> b(new FakeString(name, value));
            var = std::move(b);
        }
        variables[name] = std::move(var);
        return true;
    }
    return false;
}

bool Variables::removeVariable(std::shared_ptr<Variable> variable)
{
    std::shared_ptr<Variable> e = exists(variable->getName());
    if (e != nullptr)
    {
        this->variables.erase(variable->getName());
        return true;
    }
    return false;
}

bool Variables::removeVariable(std::string name)
{
    // fix here

    std::shared_ptr<Variable> e = exists(name);
    if (e != nullptr)
    {
        this->variables.erase(name);
        return true;
    }
    return false;
}

void Variables::setParent(std::shared_ptr<Variables> parent)
{
    this->parent = parent;
}
