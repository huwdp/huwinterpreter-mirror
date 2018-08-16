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

#include "refvariable.h"

namespace HuwInterpreter {
    namespace Variables {
        RefVariable::RefVariable(std::shared_ptr<Passable> passable, std::shared_ptr<Variable> variable)
            : Variable(passable, variable->getName())
        {
            this->variable = std::move(variable);
        }

        RefVariable::RefVariable(std::shared_ptr<Passable> passable, std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
            : Variable(passable, variable->getName(), token)
        {
            this->variable = std::move(variable);
        }

        void RefVariable::setValue(double value)
        {
            variable->setValue(value);
        }

        void RefVariable::setValue(std::string value)
        {
            variable->setValue(value);
        }

        void RefVariable::setValue(long long value)
        {
            variable->setValue(value);
        }

        long long RefVariable::toInt()
        {
            return variable->toInt();
        }

        double RefVariable::toDouble()
        {
            return variable->toDouble();
        }

        std::string RefVariable::toString()
        {
            return variable->toString();
        }

        bool RefVariable::toBool()
        {
            return variable->toBool();
        }

        Types::VarType RefVariable::getType()
        {
            return variable->getType();
        }

        bool RefVariable::isNumber()
        {
            return variable->isNumber();
        }

        bool RefVariable::isConst()
        {
            return true;
        }

        bool RefVariable::isArray()
        {
            return false;
        }

        bool RefVariable::isRef()
        {
            return true;
        }

        void RefVariable::setValue(std::shared_ptr<Variable> variable)
        {
            this->variable = variable;
        }

        std::shared_ptr<Variable> RefVariable::pow(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            return this->variable->pow(variable, token);
        }

        std::shared_ptr<Variable> RefVariable::mul(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            return this->variable->mul(variable, token);
        }

        std::shared_ptr<Variable> RefVariable::div(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            return this->variable->div(variable, token);
        }

        std::shared_ptr<Variable> RefVariable::mod(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            return this->variable->mod(variable, token);
        }

        std::shared_ptr<Variable> RefVariable::add(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            return this->variable->add(variable, token);
        }

        std::shared_ptr<Variable> RefVariable::sub(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            return this->variable->sub(variable, token);
        }

        std::shared_ptr<Variable> RefVariable::ifUnder(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifUnder", name, getType()));
                return nullVariable;
            }
            return this->variable->sub(variable, token);
        }

        std::shared_ptr<Variable> RefVariable::ifUnderOrEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (this->variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifUnderOrEqual", name, getType()));
                return nullVariable;
            }
            return this->variable->ifUnderOrEqual(variable, token);
        }

        std::shared_ptr<Variable> RefVariable::ifOver(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifOver", name, getType()));
                return nullVariable;
            }
            return this->variable->ifOver(variable, token);
        }

        std::shared_ptr<Variable> RefVariable::ifOverOrEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifOverOrEqual", name, getType()));
                return nullVariable;
            }
            return this->ifOverOrEqual(variable, token);
        }

        std::shared_ptr<Variable> RefVariable::ifEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifEqual", name, getType()));
                return nullVariable;
            }
            return this->variable->ifEqual(variable, token);
        }

        std::shared_ptr<Variable> RefVariable::ifNotEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            return this->variable->ifNotEqual(variable, token);
        }

        std::shared_ptr<Variable> RefVariable::increment(std::shared_ptr<Tokens::Token> token)
        {
            return this->variable->increment(token);
        }

        std::shared_ptr<Variable> RefVariable::count(std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            return this->variable->count(token);
        }

        std::shared_ptr<Variable> RefVariable::decrement(std::shared_ptr<Tokens::Token> token)
        {
            return this->variable->decrement(token);
        }

        void RefVariable::set(std::string index, std::shared_ptr<Variable> value, std::shared_ptr<Tokens::Token> token)
        {
            this->variable->set(index, value, token);
        }

        std::shared_ptr<Variable> RefVariable::get(std::string value, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            return this->variable->get(value, token);
        }

        void RefVariable::unset(std::string index, std::shared_ptr<Tokens::Token> token)
        {
            return this->variable->unset(index, token);
        }

        std::shared_ptr<Variable> RefVariable::copy(std::shared_ptr<Tokens::Token> token)
        {
            return std::make_shared<RefVariable>(passable, variable);
        }

        std::shared_ptr<Variable> RefVariable::bitwiseAnd(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            return this->variable->bitwiseAnd(variable, token);
        }

        std::shared_ptr<Variable> RefVariable::bitwiseOr(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            return this->variable->bitwiseOr(variable, token);
        }

        std::shared_ptr<Variable> RefVariable::bitwiseXOR(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            return this->variable->bitwiseXOR(variable, token);
        }

        std::shared_ptr<Variable> RefVariable::bitwiseComplement(std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            return variable->bitwiseComplement(token);
        }

        std::shared_ptr<Variable> RefVariable::leftShift(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            return this->variable->leftShift(variable, token);
        }

        std::shared_ptr<Variable> RefVariable::rightShift(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            return this->variable->rightShift(variable, token);
        }
    }
}
