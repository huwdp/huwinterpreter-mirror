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

Functions::Functions(std::shared_ptr<Passable> passable)
{
    this->passable = passable;
}

void Functions::init()
{
    functions["command"] = std::move(std::make_shared<Command>(passable));
    functions["dateFormat"] = std::move(std::make_shared<DateFormat>(passable));

    functions["fileRead"] = std::move(std::make_shared<FileRead>(passable));
    functions["fileWrite"] = std::move(std::make_shared<FileWrite>(passable));
    functions["fileExists"] = std::move(std::make_shared<FileExists>(passable));

    functions["month"] = std::move(std::make_shared<Month>(passable));
    functions["monthName"] = std::move(std::make_shared<MonthName>(passable));
    functions["not"] = std::move(std::make_shared<Not>(passable));
    functions["now"] = std::move(std::make_shared<Now>(passable));
    functions["print"] = std::move(std::make_shared<Print>(passable));
    functions["scan"] = std::move(std::make_shared<Scan>(passable));
    functions["weekday"] = std::move(std::make_shared<Weekday>(passable));
    functions["weekdayName"] = std::move(std::make_shared<WeekdayName>(passable));
    functions["year"] = std::move(std::make_shared<Year>(passable));


    functions["abs"] = std::move(std::make_shared<Abs>(passable));
    functions["acos"] = std::move(std::make_shared<Acos>(passable));
    functions["asin"] = std::move(std::make_shared<Asin>(passable));
    functions["atan"] = std::move(std::make_shared<Atan>(passable));
    functions["atan2"] = std::move(std::make_shared<Atan2>(passable));
    functions["ceil"] = std::move(std::make_shared<Ceil>(passable));
    functions["cos"] = std::move(std::make_shared<Cos>(passable));
    functions["exp"] = std::move(std::make_shared<Exp>(passable));
    functions["sin"] = std::move(std::make_shared<Sin>(passable));
    functions["sqrt"] = std::move(std::make_shared<Sqrt>(passable));
    functions["tan"] = std::move(std::make_shared<Tan>(passable));
    functions["pow"] = std::move(std::make_shared<Pow>(passable));
    functions["min"] = std::move(std::make_shared<Min>(passable));
    functions["max"] = std::move(std::make_shared<Max>(passable));


    functions["inStr"] = std::move(std::make_shared<InStr>(passable));
    functions["inStrRev"] = std::move(std::make_shared<InStrRev>(passable));
    functions["toLower"] = std::move(std::make_shared<ToLower>(passable));
    functions["left"] = std::move(std::make_shared<Left>(passable));
    functions["len"] = std::move(std::make_shared<Len>(passable));
    functions["lTrim"] = std::move(std::make_shared<LTrim>(passable));
    functions["mid"] = std::move(std::make_shared<Mid>(passable));
    functions["right"] = std::move(std::make_shared<Right>(passable));
    functions["rTrim"] = std::move(std::make_shared<RTrim>(passable));
    functions["space"] = std::move(std::make_shared<Space>(passable));
    functions["strCmp"] = std::move(std::make_shared<StrComp>(passable));
    functions["strRev"] = std::move(std::make_shared<StrReverse>(passable));
    functions["trim"] = std::move(std::make_shared<Trim>(passable));
    functions["toUpper"] = std::move(std::make_shared<ToUpper>(passable));
    functions["random"] = std::move(std::make_shared<Random>(passable));


    functions["asc"] = std::move(std::make_shared<Asc>(passable));
    functions["cha"] = std::move(std::make_shared<Cha>(passable));
    functions["str"] = std::move(std::make_shared<Str>(passable));

    functions["array"] = std::move(std::make_shared<Array>(passable));
    functions["arrayGet"] = std::move(std::make_shared<ArrayGet>(passable));
    functions["arraySet"] = std::move(std::make_shared<ArraySet>(passable));
    functions["arrayUnset"] = std::move(std::make_shared<ArrayUnset>(passable));

    functions["count"] = std::move(std::make_shared<Count>(passable));

    functions["isIntType"] = std::move(std::make_shared<IsIntType>(passable));
    functions["isDoubleType"] = std::move(std::make_shared<IsDoubleType>(passable));
    functions["isStringType"] = std::move(std::make_shared<IsStringType>(passable));
    functions["isArrayType"] = std::move(std::make_shared<IsArrayType>(passable));
    functions["isNumberType"] = std::move(std::make_shared<IsNumberType>(passable));

    functions["isInt"] = std::move(std::make_shared<IsInt>(passable));
    functions["isDouble"] = std::move(std::make_shared<IsDouble>(passable));
    functions["isNumber"] = std::move(std::make_shared<IsNumber>(passable));

    functions["toInt"] = std::move(std::make_shared<ToInt>(passable));
    functions["toDouble"] = std::move(std::make_shared<ToDouble>(passable));

    functions["regexSearch"] = std::move(std::make_shared<RegexSearch>(passable));
    functions["regexReplace"] = std::move(std::make_shared<RegexReplace>(passable));
    functions["regexMatch"] = std::move(std::make_shared<RegexMatch>(passable));
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

        std::shared_ptr<EmptyFunction> empty = std::make_shared<EmptyFunction>(passable);
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
