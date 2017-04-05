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

#include "variabletypefactory.h"

VariableTypeFactory::VariableTypeFactory()
{

}

std::shared_ptr<Variable> VariableTypeFactory::newVariable(VarType varType)
{
    if (varType == STRING)
    {
        std::shared_ptr<Variable> var1(new FakeString("", ""));
        return (var1);
    }
    else if (varType == INTEGER)
    {
        std::shared_ptr<Variable> var2(new FakeNumber("", (long long)0));
        return (var2);
    }
    else if (varType == DOUBLE)
    {
        std::shared_ptr<Variable> var3(new FakeNumber("", 0.0));
        return (var3);
    }
    std::shared_ptr<Variable> null;return null;
}
