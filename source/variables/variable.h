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

#pragma once
#ifndef NVARAIBLE_H
#define NVARAIBLE_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <memory>
#include "types/typedetector.h"
#include "errors/debug.h"
#include "errors/errors.h"
#include "common/passable.h"

class Variable
{
private:
    std::string name;
public:
    std::shared_ptr<Passable> passable;
    std::shared_ptr<Variable> null;
    Variable(std::shared_ptr<Passable> passable);
    Variable(std::shared_ptr<Passable> passable, std::string name);
    std::string getName();
    void setName(std::string name);
    virtual void setValue(double value) = 0;
    virtual void setValue(std::string value) = 0;
    virtual void setValue(long long value) = 0;
    virtual double toDouble() = 0;
    virtual long long toInt() = 0;
    virtual std::string toString() = 0;
    virtual bool toBool() = 0;
    virtual VarType getType() = 0;
    virtual bool isNumber() = 0;
    virtual std::shared_ptr<Variable> pow(std::shared_ptr<Variable> variable) = 0;
    virtual std::shared_ptr<Variable> mul(std::shared_ptr<Variable> variable) = 0;
    virtual std::shared_ptr<Variable> div(std::shared_ptr<Variable> variable) = 0;
    virtual std::shared_ptr<Variable> mod(std::shared_ptr<Variable> variable) = 0;
    virtual std::shared_ptr<Variable> add(std::shared_ptr<Variable> variable) = 0;
    virtual std::shared_ptr<Variable> sub(std::shared_ptr<Variable> variable) = 0;
    virtual std::shared_ptr<Variable> ifUnder(std::shared_ptr<Variable> variable) = 0;
    virtual std::shared_ptr<Variable> ifUnderOrEqual(std::shared_ptr<Variable> variable) = 0;
    virtual std::shared_ptr<Variable> ifOver(std::shared_ptr<Variable> variable) = 0;
    virtual std::shared_ptr<Variable> ifOverOrEqual(std::shared_ptr<Variable> variable) = 0;
    virtual std::shared_ptr<Variable> ifEqual(std::shared_ptr<Variable> variable) = 0;
    virtual std::shared_ptr<Variable> ifNotEqual(std::shared_ptr<Variable> variable) = 0;
    virtual std::shared_ptr<Variable> increment() = 0;
    virtual std::shared_ptr<Variable> decrement() = 0;
    virtual std::shared_ptr<Variable> count() = 0;
    virtual std::shared_ptr<Variable> get(std::string index) = 0;
    virtual void set(std::string index, std::shared_ptr<Variable> value) = 0;
    virtual void unset(std::string index) = 0;
    virtual std::shared_ptr<Variable> copy() = 0;
    virtual std::shared_ptr<Variable> bitwiseAnd(std::shared_ptr<Variable> variable) = 0;
    virtual std::shared_ptr<Variable> bitwiseOr(std::shared_ptr<Variable> variable) = 0;
};

#endif
