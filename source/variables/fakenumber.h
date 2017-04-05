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

#ifndef FAKENUMBER_H
#define FAKENUMBER_H

#include <iostream>

#include "variable.h"
#include "fakedouble.h"
#include "fakeint.h"
#include "variabletypefactory.h"
#include "precision.h"

class FakeNumber : public Variable
{
private:
    std::shared_ptr<Variable> variable;
public:
    FakeNumber(std::shared_ptr<Variable> variable);
    FakeNumber(std::string name, double value);
    FakeNumber(std::string name, long long value);
    FakeNumber(std::string name, std::string value);
    void setValue(double value);
    void setValue(std::string value);
    void setValue(long long value);
    double toDouble();
    long long toInt();
    std::string toString();
    bool toBool();
    VarType getType();
    double getValue();

    std::shared_ptr<Variable> toValue(std::shared_ptr<Variable> variable);

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
};

#endif // FAKENUMBER_H
