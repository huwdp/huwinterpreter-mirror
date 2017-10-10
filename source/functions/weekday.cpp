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

#include "weekday.h"

Weekday::Weekday(std::shared_ptr<Passable> passable)
    : Function(passable)
{
    this->name = "weekday";
}

std::shared_ptr<Variable> Weekday::run(std::shared_ptr<Token> token,
                                       std::shared_ptr<Scope> scope,
                                       std::vector<std::shared_ptr<Node>> variables)
{
    std::shared_ptr<Variable> returnNode;
    if (variables.size() == 1)
    {
        std::shared_ptr<Node> node = variables.at(0);
        if (node == nullptr)
        {
            return null;
        }

        std::shared_ptr<Variable> var = node->execute(scope);
        try
        {
            double d = var->toDouble();
            int value = (int)d;
            std::time_t t = value;
            std::tm tm = *std::localtime(&t);
            std::stringstream ss;
            ss << std::put_time(&tm, "%w");
            returnNode = std::make_shared<StringVariable>(passable, "", ss.str());
        }
        catch (const std::invalid_argument ex)
        {
            passable->errors->add(std::make_shared<Error>(FUNCTION_ERROR, "Invalid argument in Weekday", token));
        }
        catch (const std::out_of_range ex)
        {
            passable->errors->add(std::make_shared<Error>(FUNCTION_ERROR, "Out of range in Weekday", token));
        }
        catch (const std::exception& ex)
        {
            passable->errors->add(std::make_shared<Error>(FUNCTION_ERROR, ex.what()));
        }
        
    }
    else
    {
        passable->errors->add(std::make_shared<Error>(FUNCTION_ERROR, "Weekday function needs 1 argument", token));
    }
    
    return returnNode;
}
