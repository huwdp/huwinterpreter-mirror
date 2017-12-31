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

#include "stringvariable.h"

namespace HuwInterpreter {
    namespace Variables {
        StringVariable::StringVariable(std::shared_ptr<Passable> passable)
            : Variable(passable)
        {
            variableTypeFactory = std::make_shared<VariableTypeFactory>(passable);
        }

        StringVariable::StringVariable(std::shared_ptr<Passable> passable, std::string value)
            : Variable(passable, "")
        {
            this->value = value;
            variableTypeFactory = std::make_shared<VariableTypeFactory>(passable);
        }

        StringVariable::StringVariable(std::shared_ptr<Passable> passable, char value)
            : Variable(passable, "")
        {
            this->value = std::to_string(value);
            variableTypeFactory = std::make_shared<VariableTypeFactory>(passable);
        }

        StringVariable::StringVariable(std::shared_ptr<Passable> passable, std::string name, std::string value)
            : Variable(passable, name)
        {
            this->value = value;
            variableTypeFactory = std::make_shared<VariableTypeFactory>(passable);
        }

        StringVariable::StringVariable(std::shared_ptr<Passable> passable, std::string name, char value)
            : Variable(passable, name)
        {
            this->value = std::to_string(value);
            variableTypeFactory = std::make_shared<VariableTypeFactory>(passable);
        }




        StringVariable::StringVariable(std::shared_ptr<Passable> passable, std::shared_ptr<Tokens::Token> token)
            : Variable(passable)
        {
            variableTypeFactory = std::make_shared<VariableTypeFactory>(passable);
        }

        StringVariable::StringVariable(std::shared_ptr<Passable> passable, std::string value, std::shared_ptr<Tokens::Token> token)
            : Variable(passable, "")
        {
            this->value = value;
            variableTypeFactory = std::make_shared<VariableTypeFactory>(passable);
        }

        StringVariable::StringVariable(std::shared_ptr<Passable> passable, char value, std::shared_ptr<Tokens::Token> token)
            : Variable(passable, "")
        {
            this->value = std::to_string(value);
            variableTypeFactory = std::make_shared<VariableTypeFactory>(passable);
        }

        StringVariable::StringVariable(std::shared_ptr<Passable> passable, std::string name, std::string value, std::shared_ptr<Tokens::Token> token)
            : Variable(passable, name)
        {
            this->value = value;
            variableTypeFactory = std::make_shared<VariableTypeFactory>(passable);
        }

        StringVariable::StringVariable(std::shared_ptr<Passable> passable, std::string name, char value, std::shared_ptr<Tokens::Token> token)
            : Variable(passable, name)
        {
            this->value = std::to_string(value);
            variableTypeFactory = std::make_shared<VariableTypeFactory>(passable);
        }




        void StringVariable::setValue(double value)
        {
            this->value = std::to_string(value);
        }

        void StringVariable::setValue(std::string value)
        {
            this->value = value;
        }

        void StringVariable::setValue(long long value)
        {
            this->value = value;
        }

        double StringVariable::toDouble()
        {
            double value = 0.0;
            try
            {
                value = stod(this->value);
            }
            catch (const std::exception& ex)
            {

            }
            return value;
        }

        std::string StringVariable::toString()
        {
            return value;
        }

        long long StringVariable::toInt()
        {
            int value = 0.0;
            try
            {
                value = stol(this->value);
            }
            catch (const std::exception& ex)
            {

            }
            return value;
        }

        bool StringVariable::toBool()
        {
            if (value != "0")
            {
                return true;
            }
            return false;
        }

        Types::VarType StringVariable::getType()
        {
            return Types::STRING;
        }

        std::string StringVariable::getValue()
        {
            return value;
        }

        bool StringVariable::isNumber()
        {
            return false;
        }

        bool StringVariable::isConst()
        {
            return false;
        }

        std::shared_ptr<Variable> StringVariable::pow(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            ErrorReporting::Debug::print("Cannot call power method on string");
            return nullVariable;
        }

        std::shared_ptr<Variable> StringVariable::mul(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            ErrorReporting::Debug::print("Cannot call multiple method on string");
            return nullVariable;
        }

        std::shared_ptr<Variable> StringVariable::div(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            ErrorReporting::Debug::print("Cannot call divide method on string");
            return nullVariable;
        }

        std::shared_ptr<Variable> StringVariable::mod(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            ErrorReporting::Debug::print("Cannot call mod method on string");
            return nullVariable;
        }

        std::shared_ptr<Variable> StringVariable::add(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            return std::make_shared<StringVariable>(passable, this->toString() + variable->toString());
        }

        std::shared_ptr<Variable> StringVariable::sub(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            ErrorReporting::Debug::print("Cannot call subtract method on string");
            return nullVariable;
        }

        std::shared_ptr<Variable> StringVariable::ifUnder(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifUnder", name, getType()));
                return nullVariable;
            }
            if (Helpers::TypeDetector::isNumeric(toString()))
            {
                std::shared_ptr<Variable> var = variableTypeFactory->newVariable(Helpers::TypeDetector::getType(value));
                var->setValue(toString());
                return var->ifUnder(variable, token);
            }
            std::shared_ptr<IntegerVariable> temp = std::make_shared<IntegerVariable>(passable);
            if (this->toString().compare(variable->toString()) < 0)
            {
                temp->setValue(double(1));
            }
            else
            {
                temp->setValue(double(0));
            }
            return temp;
        }

        std::shared_ptr<Variable> StringVariable::ifUnderOrEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifUnderOrEqual", name, getType()));
                return nullVariable;
            }
            if (Helpers::TypeDetector::isNumeric(toString()))
            {
                std::shared_ptr<Variable> var = variableTypeFactory->newVariable(Helpers::TypeDetector::getType(value));
                var->setValue(toString());
                return var->ifUnderOrEqual(variable, token);
            }
            std::shared_ptr<IntegerVariable> temp = std::make_shared<IntegerVariable>(passable);
            if (this->toString().compare(variable->toString()) <= 0)
            {
                temp->setValue(double(1));
            }
            else
            {
                temp->setValue(double(0));
            }
            return temp;
        }

        std::shared_ptr<Variable> StringVariable::ifOver(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifOver", name, getType()));
                return nullVariable;
            }
            if (Helpers::TypeDetector::isNumeric(toString()))
            {
                std::shared_ptr<Variable> var = variableTypeFactory->newVariable(Helpers::TypeDetector::getType(value));
                var->setValue(toString());
                return var->ifOver(variable, token);
            }
            std::shared_ptr<IntegerVariable> temp = std::make_shared<IntegerVariable>(passable);
            if (this->toString().compare(variable->toString()) > 0)
            {
                temp->setValue(double(1));
            }
            else
            {
                temp->setValue(double(0));
            }
            return temp;
        }

        std::shared_ptr<Variable> StringVariable::ifOverOrEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifOverOrEqual", name, getType()));
                return nullVariable;
            }
            if (Helpers::TypeDetector::isNumeric(toString()))
            {
                std::shared_ptr<Variable> var = variableTypeFactory->newVariable(Helpers::TypeDetector::getType(value));
                var->setValue(toString());
                return var->ifOverOrEqual(variable, token);
            }
            std::shared_ptr<IntegerVariable> temp = std::make_shared<IntegerVariable>(passable);
            if (this->toString().compare(variable->toString()) >= 0)
            {
                temp->setValue(double(1));
            }
            else
            {
                temp->setValue(double(0));
            }
            return temp;
        }

        std::shared_ptr<Variable> StringVariable::ifEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifEqual", name, getType()));
                return nullVariable;
            }
            if (Helpers::TypeDetector::isNumeric(toString()))
            {
                std::shared_ptr<Variable> var = variableTypeFactory->newVariable(Helpers::TypeDetector::getType(value));
                var->setValue(toString());
                return var->ifEqual(variable, token);
            }
            std::shared_ptr<IntegerVariable> temp = std::make_shared<IntegerVariable>(passable);
            if (this->toString().compare(variable->toString()) == 0)
            {
                temp->setValue(double(1));
            }
            else
            {
                temp->setValue(double(0));
            }
            return temp;
        }

        std::shared_ptr<Variable> StringVariable::ifNotEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifNotEqual", name, getType()));
                return nullVariable;
            }
            if (Helpers::TypeDetector::isNumeric(toString()))
            {
                std::shared_ptr<Variable> var = variableTypeFactory->newVariable(Helpers::TypeDetector::getType(value));
                var->setValue(toString());
                return var->ifNotEqual(variable, token);
            }
            std::shared_ptr<IntegerVariable> temp = std::make_shared<IntegerVariable>(passable);
            if (this->toString().compare(variable->toString()) != 0)
            {
                temp->setValue(double(1));
            }
            else
            {
                temp->setValue(double(0));
            }
            return temp;
        }

        std::shared_ptr<Variable> StringVariable::addEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            std::string value = this->value;
            value.append(variable->toString());
            return std::make_shared<StringVariable>(passable, value);
        }

        std::shared_ptr<Variable> StringVariable::subEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            return nullVariable;
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "subEqual", ""));
        }

        std::shared_ptr<Variable> StringVariable::mulEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "mulEqual", ""));
            return nullVariable;
        }

        std::shared_ptr<Variable> StringVariable::divEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "divEqual", ""));
            return nullVariable;
        }

        std::shared_ptr<Variable> StringVariable::equal(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            if (value.compare(variable->toString()) == 0)
            {
                return std::make_shared<NumberVariable>(passable, true);
            }
            return std::make_shared<NumberVariable>(passable, false);
        }

        std::shared_ptr<Variable> StringVariable::increment(std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "increment", ""));
            return nullVariable;
        }

        std::shared_ptr<Variable> StringVariable::decrement(std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "decrement", ""));
            return nullVariable;
        }

        std::shared_ptr<Variable> StringVariable::count(std::shared_ptr<Tokens::Token> token)
        {
            return std::make_shared<NumberVariable>(passable, (long long)value.size());
        }

        void StringVariable::set(std::string index, std::shared_ptr<Variable> value, std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "set", "String is not an array"));
        }

        std::shared_ptr<Variable> StringVariable::get(std::string value, std::shared_ptr<Tokens::Token> token)
        {
            long index = 0;
            try
            {
                index = stol(value);
            }
            catch (const std::exception& e)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->couldNotConvertStringToNumber(token, name, "get", e.what()));
            }

            if (index >= 0 && index < this->value.length())
            {
                std::string character;
                character.append(1, (char)this->value.at(index));
                return std::make_shared<StringVariable>(passable, character);
            }
            passable->getErrorManager()->add(passable->getErrorFactory()->outOfBounds(token, name));
            return nullVariable;
        }

        void StringVariable::unset(std::string index, std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "unset", "String is not an array"));
        }

        std::shared_ptr<Variable> StringVariable::copy(std::shared_ptr<Tokens::Token> token)
        {
            return std::make_shared<StringVariable>(passable, value);
        }

        std::shared_ptr<Variable> StringVariable::bitwiseAnd(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "bitwiseAnd", "Cannot bitwiseAND string type"));
            return nullVariable;
        }

        std::shared_ptr<Variable> StringVariable::bitwiseOr(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "bitwiseOr", "Cannot bitwiseOR string type"));
            return nullVariable;
        }

        std::shared_ptr<Variable> StringVariable::bitwiseXOR(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "bitwiseXOR", "Cannot bitwiseXOR string type"));
            return nullVariable;
        }

        std::shared_ptr<Variable> StringVariable::bitwiseComplement(std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "bitwiseComplement", "Cannot bitwiseComplement string type"));
            return nullVariable;
        }

        std::shared_ptr<Variable> StringVariable::leftShift(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "leftShift", "Cannot leftShift string type"));
            return nullVariable;
        }

        std::shared_ptr<Variable> StringVariable::rightShift(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "rightShift", "Cannot leftShift string type"));
            return nullVariable;
        }
    }
}
