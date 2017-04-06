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

#include "gcobject.h"

GCObject::GCObject(std::shared_ptr<Variable> var)
{
    this->var = var;
}

std::shared_ptr<Variable> GCObject::getVariable()
{
    return var;
}

void GCObject::setVariable(std::shared_ptr<Variable> var)
{
    this->var = var;
}

void GCObject::add(std::string value)
{
    references.push_back(value);
}

void GCObject::remove(std::string value)
{
    std::vector<std::string>::iterator it = std::find(references.begin(), references.end(), value);
    if(it != references.end())
    {
        references.erase(it);
    }
}

void GCObject::release()
{
    if (references.empty())
    {

    }
}

int GCObject::count()
{
    return references.size();
}
