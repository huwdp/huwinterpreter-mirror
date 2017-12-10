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

#include "numbervariable.h"

namespace HuwInterpreter {
    namespace Variables {
        NumberVariable::NumberVariable(std::shared_ptr<Passable> passable, bool value)
            : Variable(passable)
        {
            this->variable = std::move(std::make_shared<IntegerVariable>(passable, (long long)(int)value));
        }

        NumberVariable::NumberVariable(std::shared_ptr<Passable> passable, std::shared_ptr<Variable> variable)
            : Variable(passable)
        {
            this->variable = variable;
        }

        NumberVariable::NumberVariable(std::shared_ptr<Passable> passable, std::string name, double value)
            : Variable(passable, name)
        {
            this->variable = std::move(toInternalValue(value));
        }

        NumberVariable::NumberVariable(std::shared_ptr<Passable> passable, double value)
            : Variable(passable, "")
        {
            this->variable = std::move(toInternalValue(value));
        }

        NumberVariable::NumberVariable(std::shared_ptr<Passable> passable, long long value)
            : Variable(passable, "")
        {
            this->variable = std::move(toInternalValue(value));
        }

        NumberVariable::NumberVariable(std::shared_ptr<Passable> passable, std::string name, long long value)
            : Variable(passable, name)
        {
            this->variable = std::move(toInternalValue(value));
        }

        NumberVariable::NumberVariable(std::shared_ptr<Passable> passable, std::string name, std::string value)
            : Variable(passable, name)
        {
            std::shared_ptr<VariableTypeFactory> v = std::make_shared<VariableTypeFactory>(passable);
            std::shared_ptr<Variable> var = v->newVariable(Helpers::TypeDetector::getType(value));
            var->setValue(value);
            variable = std::move(var);
        }





        NumberVariable::NumberVariable(std::shared_ptr<Passable> passable, bool value, std::shared_ptr<Tokens::Token> token)
            : Variable(passable, token)
        {
            this->variable = std::move(std::make_shared<IntegerVariable>(passable, (long long)(int)value));
        }

        NumberVariable::NumberVariable(std::shared_ptr<Passable> passable, std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
            : Variable(passable, token)
        {
            this->variable = variable;
        }

        NumberVariable::NumberVariable(std::shared_ptr<Passable> passable, std::string name, double value, std::shared_ptr<Tokens::Token> token)
            : Variable(passable, name, token)
        {
            this->variable = std::move(toInternalValue(value));
        }

        NumberVariable::NumberVariable(std::shared_ptr<Passable> passable, double value, std::shared_ptr<Tokens::Token> token)
            : Variable(passable, "", token)
        {
            this->variable = std::move(toInternalValue(value));
        }

        NumberVariable::NumberVariable(std::shared_ptr<Passable> passable, long long value, std::shared_ptr<Tokens::Token> token)
            : Variable(passable, "", token)
        {
            this->variable = std::move(toInternalValue(value));
        }

        NumberVariable::NumberVariable(std::shared_ptr<Passable> passable, std::string name, long long value, std::shared_ptr<Tokens::Token> token)
            : Variable(passable, name, token)
        {
            this->variable = std::move(toInternalValue(value));
        }

        NumberVariable::NumberVariable(std::shared_ptr<Passable> passable, std::string name, std::string value, std::shared_ptr<Tokens::Token> token)
            : Variable(passable, name, token)
        {
            std::shared_ptr<VariableTypeFactory> v = std::make_shared<VariableTypeFactory>(passable);
            std::shared_ptr<Variable> var = v->newVariable(Helpers::TypeDetector::getType(value));
            var->setValue(value);
            variable = std::move(var);
        }




        void NumberVariable::setValue(double value)
        {
            this->variable->setValue(value);
        }

        void NumberVariable::setValue(std::string value)
        {
            variable->setValue(value);
        }

        void NumberVariable::setValue(long long value)
        {
            variable->setValue(value);
        }

        long long NumberVariable::toInt()
        {
            return variable->toInt();
        }

        double NumberVariable::toDouble()
        {
            return variable->toDouble();
        }

        std::string NumberVariable::toString()
        {
            return variable->toString();
        }

        bool NumberVariable::toBool()
        {
            return variable->toBool();
        }

        Types::VarType NumberVariable::getType()
        {
            return variable->getType();
        }

        double NumberVariable::getValue()
        {
            return variable->toDouble();
        }

        bool NumberVariable::isNumber()
        {
            return true;
        }

        bool NumberVariable::isConst()
        {
            return false;
        }

        std::shared_ptr<Variable> NumberVariable::pow(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return null;
            }
            return std::move(toValue(std::move(this->variable->pow(variable, token))));
        }

        std::shared_ptr<Variable> NumberVariable::mul(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return null;
            }
            return std::move(toValue(std::move(this->variable->mul(variable, token))));
        }

        std::shared_ptr<Variable> NumberVariable::div(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return null;
            }
            return std::move(toValue(std::move(this->variable->div(variable, token))));
        }

        std::shared_ptr<Variable> NumberVariable::mod(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return null;
            }
            return std::move(toValue(std::move(this->variable->mod(variable, token))));
        }

        std::shared_ptr<Variable> NumberVariable::add(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return null;
            }
            return std::move(toValue(std::move(this->variable->add(variable, token))));
        }

        std::shared_ptr<Variable> NumberVariable::sub(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return null;
            }
            return std::move(toValue(std::move(this->variable->sub(variable, token))));
        }

        std::shared_ptr<Variable> NumberVariable::ifUnder(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifUnder", name, getType()));
                return null;
            }
            return std::move(toValue(this->variable->ifUnder(variable, token)));
        }

        std::shared_ptr<Variable> NumberVariable::ifUnderOrEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifUnderOrEqual", name, getType()));
                return null;
            }
            return std::move(toValue(std::move(this->variable->ifUnderOrEqual(variable, token))));
        }

        std::shared_ptr<Variable> NumberVariable::ifOver(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifOver", name, getType()));
                return null;
            }
            return std::move(toValue(std::move(this->variable->ifOver(variable, token))));
        }

        std::shared_ptr<Variable> NumberVariable::ifOverOrEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifOverOrEqual", name, getType()));
                return null;
            }
            return std::move(toValue(std::move(this->variable->ifOverOrEqual(variable, token))));
        }

        std::shared_ptr<Variable> NumberVariable::ifEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifEqual", name, getType()));
                return null;
            }
            return std::move(toValue(std::move(this->variable->ifEqual(variable, token))));
        }

        std::shared_ptr<Variable> NumberVariable::ifNotEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifNotEqual", name, getType()));
                return null;
            }
            return toValue(std::move(this->variable->ifNotEqual(variable, token)));
        }

        std::shared_ptr<Variable> NumberVariable::toInternalValue(double value)
        {
            if (precision.isSafeInteger(value))
            {
                return std::move(std::make_shared<DoubleVariable>(passable, value));
            }
            else
            {
                if (precision.getType(value) == Types::DOUBLE)
                {
                    return std::move(std::make_shared<DoubleVariable>(passable, value));
                }
                return std::move(std::make_shared<IntegerVariable>(passable, value));
            }
        }

        std::shared_ptr<Variable> NumberVariable::toInternalValue(long long value)
        {
            if (precision.isSafeInteger(value))
            {
                return std::move(std::make_shared<DoubleVariable>(passable, value));
            }
            return std::move(std::make_shared<DoubleVariable>(passable, value));
        }

        std::shared_ptr<Variable> NumberVariable::toValue(std::shared_ptr<Variable> variable)
        {
            double value = variable->toDouble();
            if (precision.isSafeInteger(value))
            {
                return std::move(variable);
            }
            else if (precision.getType(value) == Types::INTEGER)
            {
                long long intValue = (long long)value;
                return std::make_shared<NumberVariable>(passable, std::move(std::make_shared<IntegerVariable>(passable, intValue)));
            }
            return std::move(variable);
        }

        std::shared_ptr<Variable> NumberVariable::increment(std::shared_ptr<Tokens::Token> token)
        {
            variable->increment(token);
            return variable;
        }

        std::shared_ptr<Variable> NumberVariable::decrement(std::shared_ptr<Tokens::Token> token)
        {
            variable->decrement(token);
            return variable;
        }

        std::shared_ptr<Variable> NumberVariable::count(std::shared_ptr<Tokens::Token> token)
        {
            return variable->count(token);
        }

        void NumberVariable::set(std::string index, std::shared_ptr<Variable> value, std::shared_ptr<Tokens::Token> token)
        {
            variable->set(index, value, token);
        }

        std::shared_ptr<Variable> NumberVariable::get(std::string index, std::shared_ptr<Tokens::Token> token)
        {
            return variable->get(index, token);
        }

        void NumberVariable::unset(std::string index, std::shared_ptr<Tokens::Token> token)
        {
            variable->unset(index, token);
        }

        std::shared_ptr<Variable> NumberVariable::copy(std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return null;
            }
            return variable->copy(token);
        }

        std::shared_ptr<Variable> NumberVariable::bitwiseAnd(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return null;
            }
            return this->variable->bitwiseAnd(variable, token);
        }

        std::shared_ptr<Variable> NumberVariable::bitwiseOr(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return null;
            }
            return this->variable->bitwiseOr(variable, token);
        }

        std::shared_ptr<Variable> NumberVariable::bitwiseXOR(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return null;
            }
            return this->variable->bitwiseXOR(variable, token);
        }

        std::shared_ptr<Variable> NumberVariable::bitwiseComplement(std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return null;
            }
            return this->variable->bitwiseComplement(token);
        }

        std::shared_ptr<Variable> NumberVariable::leftShift(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == null)
            {
                return null;
            }
            return this->variable->leftShift(variable, token);
        }

        std::shared_ptr<Variable> NumberVariable::rightShift(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == null)
            {
                return null;
            }
            return this->variable->rightShift(variable, token);
        }
    }
}

