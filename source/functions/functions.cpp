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

#include "functions.h"

Functions::Functions(std::shared_ptr<Passible> passible)
{
    this->passible = passible;
}

void Functions::init()
{
    functions["command"] = std::move(std::make_shared<Command>(passible));
    functions["dateFormat"] = std::move(std::make_shared<DateFormat>(passible));
    functions["fileRead"] = std::move(std::make_shared<FileRead>(passible));
    functions["fileWrite"] = std::move(std::make_shared<FileWrite>(passible));
    functions["month"] = std::move(std::make_shared<Month>(passible));
    functions["monthName"] = std::move(std::make_shared<MonthName>(passible));
    functions["not"] = std::move(std::make_shared<Not>(passible));
    functions["now"] = std::move(std::make_shared<Now>(passible));
    functions["print"] = std::move(std::make_shared<Print>(passible));
    functions["scan"] = std::move(std::make_shared<Scan>(passible));
    functions["weekday"] = std::move(std::make_shared<Weekday>(passible));
    functions["weekdayName"] = std::move(std::make_shared<WeekdayName>(passible));
    functions["year"] = std::move(std::make_shared<Year>(passible));


    functions["abs"] = std::move(std::make_shared<Abs>(passible));
    functions["acos"] = std::move(std::make_shared<Acos>(passible));
    functions["asin"] = std::move(std::make_shared<Asin>(passible));
    functions["atan"] = std::move(std::make_shared<Atan>(passible));
    functions["atan2"] = std::move(std::make_shared<Atan2>(passible));
    functions["ceil"] = std::move(std::make_shared<Ceil>(passible));
    functions["cos"] = std::move(std::make_shared<Cos>(passible));
    functions["exp"] = std::move(std::make_shared<Exp>(passible));
    functions["sin"] = std::move(std::make_shared<Sin>(passible));
    functions["sqrt"] = std::move(std::make_shared<Sqrt>(passible));
    functions["tan"] = std::move(std::make_shared<Tan>(passible));
    functions["pow"] = std::move(std::make_shared<Pow>(passible));
    functions["min"] = std::move(std::make_shared<Min>(passible));
    functions["max"] = std::move(std::make_shared<Max>(passible));


    functions["inStr"] = std::move(std::make_shared<InStr>(passible));
    functions["inStrRev"] = std::move(std::make_shared<InStrRev>(passible));
    functions["toLower"] = std::move(std::make_shared<ToLower>(passible));
    functions["left"] = std::move(std::make_shared<Left>(passible));
    functions["len"] = std::move(std::make_shared<Len>(passible));
    functions["lTrim"] = std::move(std::make_shared<LTrim>(passible));
    functions["mid"] = std::move(std::make_shared<Mid>(passible));
    functions["right"] = std::move(std::make_shared<Right>(passible));
    functions["rTrim"] = std::move(std::make_shared<RTrim>(passible));
    functions["space"] = std::move(std::make_shared<Space>(passible));
    functions["strCmp"] = std::move(std::make_shared<StrComp>(passible));
    functions["strRev"] = std::move(std::make_shared<StrReverse>(passible));
    functions["trim"] = std::move(std::make_shared<Trim>(passible));
    functions["toUpper"] = std::move(std::make_shared<ToUpper>(passible));
    functions["random"] = std::move(std::make_shared<Random>(passible));


    functions["asc"] = std::move(std::make_shared<Asc>(passible));
    functions["cha"] = std::move(std::make_shared<Cha>(passible));
    functions["str"] = std::move(std::make_shared<Str>(passible));

    functions["array"] = std::move(std::make_shared<Array>(passible));
    functions["arrayGet"] = std::move(std::make_shared<ArrayGet>(passible));
    functions["arraySet"] = std::move(std::make_shared<ArraySet>(passible));
    functions["arrayUnset"] = std::move(std::make_shared<ArrayUnset>(passible));

    functions["count"] = std::move(std::make_shared<Count>(passible));

    functions["isIntType"] = std::move(std::make_shared<IsIntType>(passible));
    functions["isDoubleType"] = std::move(std::make_shared<IsDoubleType>(passible));
    functions["isStringType"] = std::move(std::make_shared<IsStringType>(passible));
    functions["isArrayType"] = std::move(std::make_shared<IsArrayType>(passible));
    functions["isNumberType"] = std::move(std::make_shared<IsNumberType>(passible));

    functions["isInt"] = std::move(std::make_shared<IsInt>(passible));
    functions["isDouble"] = std::move(std::make_shared<IsDouble>(passible));
    functions["isNumber"] = std::move(std::make_shared<IsNumber>(passible));

    functions["toInt"] = std::move(std::make_shared<ToInt>(passible));
    functions["toDouble"] = std::move(std::make_shared<ToDouble>(passible));
}

std::shared_ptr<Function> Functions::get(std::string name)
{
    std::unordered_map<std::string,std::shared_ptr<Function>>::const_iterator got = functions.find(name);
    if (got == functions.end())
    {
        std::shared_ptr<Function> null;
        return null;
    }
    else
    {
        return (got->second);
    }
}

bool Functions::addFunction(std::shared_ptr<Function> function)
{
    std::shared_ptr<Function> e = get(function->getName());
    if (e == nullptr)
    {
        std::string name = function->getName();
        functions[name] = function;
        return true;
    }
    return false;
}

bool Functions::addFunction(std::string name)
{
    std::shared_ptr<Function> e = get(name);
    if (e == nullptr)
    {
        //std::shared_ptr<Function> newFunction = std::make_shared<Function>();
        //newFunction->setName(name);

        std::shared_ptr<EmptyFunction> empty = std::make_shared<EmptyFunction>(passible);
        functions[name] = empty;
        return true;
    }
    return false;
}

bool Functions::addFunction(std::string name, std::shared_ptr<Function> function)
{
    std::shared_ptr<Function> e = get(function->getName());
    if (e == nullptr)
    {
        function->setName(name);
        functions[name] = function;
        return true;
    }
    return false;
}

bool Functions::setFunction(std::string name, std::shared_ptr<Function> function)
{
    std::shared_ptr<Function> e = get(function->getName());
    if (e != nullptr)
    {
        function->setName(name);
        functions[name] = function;
        return true;
    }
    return false;
}

bool Functions::exists(std::string name)
{
    std::unordered_map<std::string,std::shared_ptr<Function>>::const_iterator got = functions.find(name);
    if (got == functions.end())
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Functions::exists(std::shared_ptr<Function> function)
{
    std::shared_ptr<Function> e = get(function->getName());
    if (e != nullptr)
    {
        return true;
    }
    return false;
}

bool Functions::removeFunction(std::shared_ptr<Function> function)
{
    std::shared_ptr<Function> e = get(function->getName());
    if (e != nullptr)
    {
        this->functions.erase(function->getName());
        return true;
    }
    return false;
}

bool Functions::removeFunction(std::string name)
{
    std::shared_ptr<Function> e = get(name);
    if (e != nullptr)
    {
        this->functions.erase(name);
        return true;
    }
    return false;
}

std::string Functions::toString()
{
    std::string output;
    for (std::unordered_map<std::string, std::shared_ptr<Function>>::iterator it = functions.begin(); it != functions.end(); ++it)
    {
        std::vector<std::shared_ptr<Node>> emptyVector;
        output.append((*it).second->toString(emptyVector));
    }
    return output;
}
