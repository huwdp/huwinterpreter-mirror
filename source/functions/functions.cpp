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
    /*
    std::shared_ptr<Command> command(new Command());
    std::shared_ptr<Function> dateFormat(new DateFormat());
    std::shared_ptr<Function> fileRead(new FileRead());
    std::shared_ptr<Function> fileWrite(new FileWrite());
    std::shared_ptr<Function> month(new Month());
    std::shared_ptr<Function> monthName(new MonthName());
    std::shared_ptr<Function> notF(new Not());
    std::shared_ptr<Function> now(new Now());
    std::shared_ptr<Function> print(new Print());
    std::shared_ptr<Function> scan(new Scan());
    std::shared_ptr<Function> weekday(new Weekday());
    std::shared_ptr<Function> weekdayName(new WeekdayName());
    std::shared_ptr<Function> year(new Year());


    std::shared_ptr<Function> abs(new Abs());
    std::shared_ptr<Function> acos(new Acos());
    std::shared_ptr<Function> asin(new Asin());
    std::shared_ptr<Function> atan(new Atan());
    std::shared_ptr<Function> atan2(new Atan2());
    std::shared_ptr<Function> ceil(new Ceil());
    std::shared_ptr<Function> cos(new Cos());
    std::shared_ptr<Function> exp(new Exp());
    std::shared_ptr<Function> sin(new Sin());
    std::shared_ptr<Function> sqrt(new Sqrt());
    std::shared_ptr<Function> tan(new Tan());
    std::shared_ptr<Function> pow(new Pow());
    std::shared_ptr<Function> min(new Min());
    std::shared_ptr<Function> max(new Max());


    std::shared_ptr<Function> inStr(new InStr());
    std::shared_ptr<Function> inStrRev(new InStrRev());
    std::shared_ptr<Function> toLower(new ToLower());
    std::shared_ptr<Function> left(new Left());
    std::shared_ptr<Function> len(new Len());
    std::shared_ptr<Function> lTrim(new LTrim());
    std::shared_ptr<Function> mid(new Mid());
    std::shared_ptr<Function> right(new Right());
    std::shared_ptr<Function> rTrim(new RTrim());
    std::shared_ptr<Function> space(new Space());
    std::shared_ptr<Function> strComp(new StrComp());
    std::shared_ptr<Function> strReverse(new StrReverse());
    std::shared_ptr<Function> trim(new Trim());
    std::shared_ptr<Function> toUpper(new ToUpper());
    std::shared_ptr<Function> random(new Random());


    std::shared_ptr<Function> asc(new Asc());
    std::shared_ptr<Function> cha(new Cha());
    std::shared_ptr<Function> str(new Str());
    */


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
