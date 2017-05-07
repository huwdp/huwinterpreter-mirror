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

#include "gc.h"


GC::GC()
{

}

void GC::exist(std::shared_ptr<Variable> var)
{
}

std::shared_ptr<GCObject> GC::add(std::shared_ptr<Variable> var)
{
    std::shared_ptr<GCObject> gcObject(new GCObject(var));
    list.push_back(std::move(gcObject));
    return gcObject;
}

void GC::remove(std::shared_ptr<Variable> var)
{
    for (std::vector<std::shared_ptr<GCObject>>::iterator it = list.begin(); it != list.end(); ++it)
    {
        if ((*it)->getVariable() == var)
        {
            (*it)->release();
        }
    }
}

void GC::removeAll()
{
    for (std::vector<std::shared_ptr<GCObject>>::iterator it = list.begin(); it != list.end(); ++it)
    {
        std::shared_ptr<GCObject> gcObject = (*it);
    }
}

void GC::release()
{
    for (std::vector<std::shared_ptr<GCObject>>::iterator it = list.begin(); it != list.end(); ++it)
    {
        std::shared_ptr<GCObject> gcObject = (*it);
    }
}

int GC::count()
{
    return list.size();
}
