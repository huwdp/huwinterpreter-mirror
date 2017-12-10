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

#include "constantvariable.h"

namespace HuwInterpreter {
    namespace Variables {
        ConstantVariable::ConstantVariable(std::shared_ptr<Passable> passable, std::shared_ptr<Variable> variable)
            : Variable(passable, variable->getName())
        {
            this->variable = std::move(variable);
        }

        ConstantVariable::ConstantVariable(std::shared_ptr<Passable> passable, std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
            : Variable(passable, variable->getName(), token)
        {
            this->variable = std::move(variable);
        }

        void ConstantVariable::setValue(double value)
        {
            if (!isSet)
            {
                variable->setValue(value);
                isSet = true;
            }
        }

        void ConstantVariable::setValue(std::string value)
        {
            if (!isSet)
            {
                variable->setValue(value);
                isSet = true;
            }
        }

        void ConstantVariable::setValue(long long value)
        {
            if (!isSet)
            {
                variable->setValue(value);
                isSet = true;
            }
        }

        long long ConstantVariable::toInt()
        {
            return variable->toInt();
        }

        double ConstantVariable::toDouble()
        {
            return variable->toDouble();
        }

        std::string ConstantVariable::toString()
        {
            return variable->toString();
        }

        bool ConstantVariable::toBool()
        {
            return variable->toBool();
        }

        Types::VarType ConstantVariable::getType()
        {
            return variable->getType();
        }

        bool ConstantVariable::isNumber()
        {
            return variable->isNumber();
        }

        bool ConstantVariable::isConst()
        {
            return true;
        }

        std::shared_ptr<Variable> ConstantVariable::pow(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (this->variable == null)
            {
                return null;
            }
            return this->variable->pow(variable, token);
        }

        std::shared_ptr<Variable> ConstantVariable::mul(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (this->variable == null)
            {
                return null;
            }
            return this->variable->mul(variable, token);
        }

        std::shared_ptr<Variable> ConstantVariable::div(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (this->variable == null)
            {
                return null;
            }
            return this->variable->div(variable, token);
        }

        std::shared_ptr<Variable> ConstantVariable::mod(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (this->variable == null)
            {
                return null;
            }
            return this->variable->mod(variable, token);
        }

        std::shared_ptr<Variable> ConstantVariable::add(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (this->variable == null)
            {
                return null;
            }
            return this->variable->add(variable, token);
        }

        std::shared_ptr<Variable> ConstantVariable::sub(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (this->variable == null)
            {
                return null;
            }
            return this->variable->sub(variable, token);
        }

        std::shared_ptr<Variable> ConstantVariable::ifUnder(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (this->variable == null)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifUnder", name, getType()));
                return null;
            }
            return this->variable->sub(variable, token);
        }

        std::shared_ptr<Variable> ConstantVariable::ifUnderOrEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (this->variable)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifUnderOrEqual", name, getType()));
                return null;
            }
            return this->variable->ifUnderOrEqual(variable, token);
        }

        std::shared_ptr<Variable> ConstantVariable::ifOver(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (this->variable == null)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifOver", name, getType()));
                return null;
            }
            return this->variable->ifOver(variable, token);
        }

        std::shared_ptr<Variable> ConstantVariable::ifOverOrEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (this->variable == null)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifOverOrEqual", name, getType()));
                return null;
            }
            return this->ifOverOrEqual(variable, token);
        }

        std::shared_ptr<Variable> ConstantVariable::ifEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (this->variable == null)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifEqual", name, getType()));
                return null;
            }
            return this->variable->ifEqual(variable, token);
        }

        std::shared_ptr<Variable> ConstantVariable::ifNotEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (this->variable == null)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifNotEqual", name, getType()));
                return null;
            }
            return this->variable->ifNotEqual(variable, token);
        }

        std::shared_ptr<Variable> ConstantVariable::increment(std::shared_ptr<Tokens::Token> token)
        {
            if (!isSet && this->variable == null && variable == nullptr)
            {
                isSet = true;
                return null;
            }
            return this->variable->increment(token);
        }

        std::shared_ptr<Variable> ConstantVariable::count(std::shared_ptr<Tokens::Token> token)
        {
            if (this->variable == null)
            {
                return null;
            }
            return this->variable->count(token);
        }

        std::shared_ptr<Variable> ConstantVariable::decrement(std::shared_ptr<Tokens::Token> token)
        {
            if (!isSet && this->variable == null && variable == nullptr)
            {
                isSet = true;
                return null;
            }
            return this->variable->decrement(token);
        }

        void ConstantVariable::set(std::string index, std::shared_ptr<Variable> value, std::shared_ptr<Tokens::Token> token)
        {
            if (!isSet && this->variable == null && variable == nullptr)
            {
                isSet = true;
                return;
            }
            this->variable->set(index, value, token);
        }

        std::shared_ptr<Variable> ConstantVariable::get(std::string value, std::shared_ptr<Tokens::Token> token)
        {
            if (this->variable == null)
            {
                return null;
            }
            return this->variable->get(value, token);
        }

        void ConstantVariable::unset(std::string index, std::shared_ptr<Tokens::Token> token)
        {
            if (!isSet && this->variable == null && variable == nullptr)
            {
                isSet = true;
                return;
            }
            return this->variable->unset(index, token);
        }

        std::shared_ptr<Variable> ConstantVariable::copy(std::shared_ptr<Tokens::Token> token)
        {
            if (variable != nullptr)
            {
                return null;
            }
            return variable->copy(token);
        }

        std::shared_ptr<Variable> ConstantVariable::bitwiseAnd(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (!isSet && this->variable == null && variable == nullptr)
            {
                return null;
            }
            return this->variable->bitwiseAnd(variable, token);
        }

        std::shared_ptr<Variable> ConstantVariable::bitwiseOr(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (!isSet && this->variable == null && variable == nullptr)
            {
                return null;
            }
            return this->variable->bitwiseOr(variable, token);
        }

        std::shared_ptr<Variable> ConstantVariable::bitwiseXOR(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (!isSet && this->variable == null && variable == nullptr)
            {
                return null;
            }
            return this->variable->bitwiseXOR(variable, token);
        }

        std::shared_ptr<Variable> ConstantVariable::bitwiseComplement(std::shared_ptr<Tokens::Token> token)
        {
            if (variable == null)
            {
                return null;
            }
            return variable->bitwiseComplement(token);
        }

        std::shared_ptr<Variable> ConstantVariable::leftShift(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == null)
            {
                return null;
            }
            return this->variable->leftShift(variable, token);
        }

        std::shared_ptr<Variable> ConstantVariable::rightShift(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == null)
            {
                return null;
            }
            return this->variable->rightShift(variable, token);
        }
    }
}
