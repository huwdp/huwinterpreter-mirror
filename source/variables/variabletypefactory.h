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

#ifndef VARIABLETYPEFACTORY_H
#define VARIABLETYPEFACTORY_H

#include "variable.h"
#include "doublevariable.h"
#include "stringvariable.h"
#include "types/tokentypes.h"
#include "types/typedetector.h"

class VariableTypeFactory
{
private:
    std::shared_ptr<Passable> passable;
public:
    VariableTypeFactory(std::shared_ptr<Passable> passable);
    std::shared_ptr<Variable> newVariable(VarType varType);
};

#endif // VARIABLETYPEFACTORY_H
