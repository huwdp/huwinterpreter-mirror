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



    functions["command"] = std::move(command);
    functions["dateFormat"] = std::move(dateFormat);
    functions["fileRead"] = std::move(fileRead);
    functions["fileWrite"] = std::move(fileWrite);
    functions["month"] = std::move(month);
    functions["monthName"] = std::move(monthName);
    functions["not"] = std::move(notF);
    functions["now"] = std::move(now);
    functions["print"] = std::move(print);
    functions["scan"] = std::move(scan);
    functions["weekday"] = std::move(weekday);
    functions["weekdayName"] = std::move(weekdayName);
    functions["year"] = std::move(year);


    functions["abs"] = std::move(abs);
    functions["acos"] = std::move(acos);
    functions["asin"] = std::move(asin);
    functions["atan"] = std::move(atan);
    functions["atan2"] = std::move(atan2);
    functions["ceil"] = std::move(ceil);
    functions["cos"] = std::move(cos);
    functions["exp"] = std::move(exp);
    functions["sin"] = std::move(sin);
    functions["sqrt"] = std::move(sqrt);
    functions["tan"] = std::move(tan);
    functions["pow"] = std::move(pow);
    functions["min"] = std::move(min);
    functions["max"] = std::move(max);


    functions["inStr"] = std::move(inStr);
    functions["inStrRev"] = std::move(inStrRev);
    functions["toLower"] = std::move(toLower);
    functions["left"] = std::move(left);
    functions["len"] = std::move(len);
    functions["lTrim"] = std::move(lTrim);
    functions["mid"] = std::move(mid);
    functions["right"] = std::move(right);
    functions["rTrim"] = std::move(rTrim);
    functions["space"] = std::move(space);
    functions["strCmp"] = std::move(strComp);
    functions["strRev"] = std::move(strReverse);
    functions["trim"] = std::move(trim);
    functions["toUpper"] = std::move(toUpper);
    functions["random"] = std::move(random);


    functions["asc"] = std::move(asc);
    functions["cha"] = std::move(cha);
    functions["str"] = std::move(str);



}

std::shared_ptr<Function> Functions::get(std::string name)
{
    if (functions[name].get() != nullptr)
    {
        return (functions[name]);
    }
    std::shared_ptr<Function> null;
    return null;
}

bool Functions::addFunction(std::shared_ptr<Function> function)
{
    std::shared_ptr<Function> e = exists(function->getName());
    if (e.get() == nullptr)
    {
        std::string name = function->getName();
        functions[name] = (function);
        return true;
    }
    return false;
}

std::shared_ptr<Function> Functions::exists(std::string name)
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

std::shared_ptr<Function> Functions::exists(std::shared_ptr<Function> function)
{
    std::shared_ptr<Function> e = exists(function->getName());
    if (e.get() != nullptr)
    {
        return (e);
    }
    std::shared_ptr<Function> null;
    return null;
}

bool Functions::removeFunction(std::shared_ptr<Function> function)
{
    std::shared_ptr<Function> e = exists(function.get()->getName());
    if (e.get() != nullptr)
    {
        this->functions.erase(function->getName());
        return true;
    }
    return false;
}

bool Functions::removeFunction(std::string name)
{
    std::shared_ptr<Function> e = exists(name);
    if (e.get() != nullptr)
    {
        this->functions.erase(name);
        return true;
    }
    return false;

}
