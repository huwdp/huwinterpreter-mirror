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

#ifndef GCOBJECT_H
#define GCOBJECT_H

#include <string>
#include <vector>
#include <algorithm>
#include "variables/variable.h"

class GCObject
{
private:
    std::shared_ptr<Variable> var;
    std::vector<std::string> references;
public:
    GCObject(std::shared_ptr<Variable> var);
    std::shared_ptr<Variable> getVariable();
    void setVariable(std::shared_ptr<Variable> var);
    void add(std::string value);
    void remove(std::string value);
    void release();
    int count();
};

#endif // GCOBJECT_H
