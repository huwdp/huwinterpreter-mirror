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

#ifndef STRINGVARIABLE_H
#define STRINGVARIABLE_H

#include "variable.h"
#include "doublevariable.h"
#include "variabletypefactory.h"

class VariableTypeFactory;

class StringVariable : public Variable
{
private:
    std::string value;
    std::shared_ptr<VariableTypeFactory> variableTypeFactory;
public:
    StringVariable(std::shared_ptr<Passable> passable);
    StringVariable(std::shared_ptr<Passable> passable, std::string value);
    StringVariable(std::shared_ptr<Passable> passable, char value);
    StringVariable(std::shared_ptr<Passable> passable, std::string name, std::string value);
    StringVariable(std::shared_ptr<Passable> passable, std::string name, char value);
    void setValue(double value);
    void setValue(std::string value);
    void setValue(long long value);
    double toDouble();
    std::string toString();
    bool toBool();
    long long toInt();
    VarType getType();
    std::string getValue();
    bool isNumber();
    std::shared_ptr<Variable> pow(std::shared_ptr<Variable> variable);
    std::shared_ptr<Variable> mul(std::shared_ptr<Variable> variable);
    std::shared_ptr<Variable> div(std::shared_ptr<Variable> variable);
    std::shared_ptr<Variable> mod(std::shared_ptr<Variable> variable);
    std::shared_ptr<Variable> add(std::shared_ptr<Variable> variable);
    std::shared_ptr<Variable> sub(std::shared_ptr<Variable> variable);
    std::shared_ptr<Variable> ifUnder(std::shared_ptr<Variable> variable);
    std::shared_ptr<Variable> ifUnderOrEqual(std::shared_ptr<Variable> variable);
    std::shared_ptr<Variable> ifOver(std::shared_ptr<Variable> variable);
    std::shared_ptr<Variable> ifOverOrEqual(std::shared_ptr<Variable> variable);
    std::shared_ptr<Variable> ifEqual(std::shared_ptr<Variable> variable);
    std::shared_ptr<Variable> ifNotEqual(std::shared_ptr<Variable> variable);
    std::shared_ptr<Variable> addEqual(std::shared_ptr<Variable> variable);
    std::shared_ptr<Variable> subEqual(std::shared_ptr<Variable> variable);
    std::shared_ptr<Variable> mulEqual(std::shared_ptr<Variable> variable);
    std::shared_ptr<Variable> divEqual(std::shared_ptr<Variable> variable);
    std::shared_ptr<Variable> equal(std::shared_ptr<Variable> variable);
    std::shared_ptr<Variable> increment();
    std::shared_ptr<Variable> decrement();
    std::shared_ptr<Variable> count();
    std::shared_ptr<Variable> get(std::string index);
    void set(std::string index, std::shared_ptr<Variable> value);
    void unset(std::string index);
    std::shared_ptr<Variable> copy();
    std::shared_ptr<Variable> bitwiseAnd(std::shared_ptr<Variable> variable);
    std::shared_ptr<Variable> bitwiseOr(std::shared_ptr<Variable> variable);
    std::shared_ptr<Variable> bitwiseXOR(std::shared_ptr<Variable> variable);
};

#endif // StringVariable

