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

Functions::Functions()
{
    functions["command"] = std::move(std::make_shared<Command>());
    functions["dateFormat"] = std::move(std::make_shared<DateFormat>());
    functions["fileRead"] = std::move(std::make_shared<FileRead>());
    functions["fileWrite"] = std::move(std::make_shared<FileWrite>());
    functions["month"] = std::move(std::make_shared<Month>());
    functions["monthName"] = std::move(std::make_shared<MonthName>());
    functions["not"] = std::move(std::make_shared<Not>());
    functions["now"] = std::move(std::make_shared<Now>());
    functions["print"] = std::move(std::make_shared<Print>());
    functions["scan"] = std::move(std::make_shared<Scan>());
    functions["weekday"] = std::move(std::make_shared<Weekday>());
    functions["weekdayName"] = std::move(std::make_shared<WeekdayName>());
    functions["year"] = std::move(std::make_shared<Year>());


    functions["abs"] = std::move(std::make_shared<Abs>());
    functions["acos"] = std::move(std::make_shared<Acos>());
    functions["asin"] = std::move(std::make_shared<Asin>());
    functions["atan"] = std::move(std::make_shared<Atan>());
    functions["atan2"] = std::move(std::make_shared<Atan2>());
    functions["ceil"] = std::move(std::make_shared<Ceil>());
    functions["cos"] = std::move(std::make_shared<Cos>());
    functions["exp"] = std::move(std::make_shared<Exp>());
    functions["sin"] = std::move(std::make_shared<Sin>());
    functions["sqrt"] = std::move(std::make_shared<Sqrt>());
    functions["tan"] = std::move(std::make_shared<Tan>());
    functions["pow"] = std::move(std::make_shared<Pow>());
    functions["min"] = std::move(std::make_shared<Min>());
    functions["max"] = std::move(std::make_shared<Max>());


    functions["inStr"] = std::move(std::make_shared<InStr>());
    functions["inStrRev"] = std::move(std::make_shared<InStrRev>());
    functions["toLower"] = std::move(std::make_shared<ToLower>());
    functions["left"] = std::move(std::make_shared<Left>());
    functions["len"] = std::move(std::make_shared<Len>());
    functions["lTrim"] = std::move(std::make_shared<LTrim>());
    functions["mid"] = std::move(std::make_shared<Mid>());
    functions["right"] = std::move(std::make_shared<Right>());
    functions["rTrim"] = std::move(std::make_shared<RTrim>());
    functions["space"] = std::move(std::make_shared<Space>());
    functions["strCmp"] = std::move(std::make_shared<StrComp>());
    functions["strRev"] = std::move(std::make_shared<StrReverse>());
    functions["trim"] = std::move(std::make_shared<Trim>());
    functions["toUpper"] = std::move(std::make_shared<ToUpper>());
    functions["random"] = std::move(std::make_shared<Random>());


    functions["asc"] = std::move(std::make_shared<Asc>());
    functions["cha"] = std::move(std::make_shared<Cha>());
    functions["str"] = std::move(std::make_shared<Str>());

    functions["array"] = std::move(std::make_shared<Array>());
    functions["arrayGet"] = std::move(std::make_shared<ArrayGet>());
    functions["arraySet"] = std::move(std::make_shared<ArraySet>());
    functions["arrayUnset"] = std::move(std::make_shared<ArrayUnset>());

    functions["count"] = std::move(std::make_shared<Count>());

    functions["isIntType"] = std::move(std::make_shared<IsIntType>());
    functions["isDoubleType"] = std::move(std::make_shared<IsDoubleType>());
    functions["isStringType"] = std::move(std::make_shared<IsStringType>());
    functions["isArrayType"] = std::move(std::make_shared<IsArrayType>());
    functions["isNumberType"] = std::move(std::make_shared<IsNumberType>());

    functions["isInt"] = std::move(std::make_shared<IsInt>());
    functions["isDouble"] = std::move(std::make_shared<IsDouble>());
    functions["isNumber"] = std::move(std::make_shared<IsNumber>());

    functions["toInt"] = std::move(std::make_shared<ToInt>());
    functions["toDouble"] = std::move(std::make_shared<ToDouble>());
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

        std::shared_ptr<EmptyFunction> empty = std::make_shared<EmptyFunction>();
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
