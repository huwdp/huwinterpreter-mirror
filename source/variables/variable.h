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

namespace HuwInterpreter {
    namespace Variables {
        class Variable
        {
        protected:
            long long referenceCount = 0;
            std::string internalName;
            std::string name;
            std::shared_ptr<Tokens::Token> token;
        public:
            std::shared_ptr<Passable> passable;
            std::shared_ptr<Variable> nullVariable;
            Variable(std::shared_ptr<Passable> passable);
            Variable(std::shared_ptr<Passable> passable, std::string name);
            Variable(std::shared_ptr<Passable> passable, std::shared_ptr<Tokens::Token> token);
            Variable(std::shared_ptr<Passable> passable, std::string name, std::shared_ptr<Tokens::Token> token);
            std::string getName();
            void setName(std::string name);
            virtual void setValue(double value) = 0;
            virtual void setValue(std::string value) = 0;
            virtual void setValue(long long value) = 0;
            virtual double toDouble() = 0;
            virtual long long toInt() = 0;
            virtual std::string toString() = 0;
            virtual bool toBool() = 0;
            virtual Types::VarType getType() = 0;
            virtual bool isNumber() = 0;
            virtual bool isConst() = 0;
            virtual std::shared_ptr<Variable> pow(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token) = 0;
            virtual std::shared_ptr<Variable> mul(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token) = 0;
            virtual std::shared_ptr<Variable> div(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token) = 0;
            virtual std::shared_ptr<Variable> mod(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token) = 0;
            virtual std::shared_ptr<Variable> add(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token) = 0;
            virtual std::shared_ptr<Variable> sub(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token) = 0;
            virtual std::shared_ptr<Variable> ifUnder(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token) = 0;
            virtual std::shared_ptr<Variable> ifUnderOrEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token) = 0;
            virtual std::shared_ptr<Variable> ifOver(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token) = 0;
            virtual std::shared_ptr<Variable> ifOverOrEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token) = 0;
            virtual std::shared_ptr<Variable> ifEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token) = 0;
            virtual std::shared_ptr<Variable> ifNotEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token) = 0;
            virtual std::shared_ptr<Variable> increment(std::shared_ptr<Tokens::Token> token) = 0;
            virtual std::shared_ptr<Variable> decrement(std::shared_ptr<Tokens::Token> token) = 0;
            virtual std::shared_ptr<Variable> count(std::shared_ptr<Tokens::Token> token) = 0;
            virtual std::shared_ptr<Variable> get(std::string index, std::shared_ptr<Tokens::Token> token) = 0;
            virtual void set(std::string index, std::shared_ptr<Variable> value, std::shared_ptr<Tokens::Token> token) = 0;
            virtual void unset(std::string index, std::shared_ptr<Tokens::Token> token) = 0;
            virtual std::shared_ptr<Variable> copy(std::shared_ptr<Tokens::Token> token) = 0;
            virtual std::shared_ptr<Variable> bitwiseAnd(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token) = 0;
            virtual std::shared_ptr<Variable> bitwiseOr(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token) = 0;
            virtual std::shared_ptr<Variable> bitwiseXOR(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token) = 0;
            virtual std::shared_ptr<Variable> bitwiseComplement(std::shared_ptr<Tokens::Token> token) = 0;
            virtual std::shared_ptr<Variable> leftShift(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token) = 0;
            virtual std::shared_ptr<Variable> rightShift(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token) = 0;

            long long getReferenceCount();
            void setReferenceCount(long long n);
            void incrementReferenceCount();
            void decrementReferenceCount();
        };
    }
}

#endif
