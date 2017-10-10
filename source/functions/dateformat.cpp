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

#include "dateformat.h"

DateFormat::DateFormat(std::shared_ptr<Passable> passable)
    : Function(passable)
{
    name = "dateFormat";
}

std::shared_ptr<Variable> DateFormat::run(std::shared_ptr<Token> token,
                                          std::shared_ptr<Scope> scope,
                                          std::vector<std::shared_ptr<Node>> variables)
{
    std::shared_ptr<Variable> returnNode;
    if (variables.size() == 2)
    {
        std::shared_ptr<Node> node1 = variables.at(0);
        std::shared_ptr<Node> node2 = variables.at(1);
        if (node1 == nullptr || node2 == nullptr)
        {
            return null;
        }

        std::shared_ptr<Variable> var1 = node1->execute(scope);
        std::shared_ptr<Variable> var2 = node2->execute(scope);

        try
        {
            double d = var1->toDouble();
            long value = (long)d;   // TODO

            std::string format = var2->toString();
            std::time_t t = (int)value;
            std::tm tm = *std::localtime(&t);

            std::stringstream ss;
            ss << std::put_time(&tm, format.c_str());
            if (ss.fail())
            {
                passable->errors->add(std::make_shared<Error>(FUNCTION_ERROR, "Could not parse time in DateFormat\n", token));
            }
            else
            {
                returnNode = std::make_shared<StringVariable>(passable, "", ss.str());
            }
        }
        catch (const std::invalid_argument ex)
        {
            passable->errors->add(std::make_shared<Error>(FUNCTION_ERROR, "Invalid argument in DateFormat", token));
        }
        catch (const std::out_of_range ex)
        {
            passable->errors->add(std::make_shared<Error>(FUNCTION_ERROR, "Out of range in DateFormat", token));
        }
        catch (const std::exception& ex)
        {
            passable->errors->add(std::make_shared<Error>(FUNCTION_ERROR, ex.what(), token));
        }
    }
    else
    {
        passable->errors->add(std::make_shared<Error>(FUNCTION_ERROR, "Too many arguments in DateFormat", token));
    }

    return returnNode;
}
