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

#include "typedetector.h"

TypeDetector::TypeDetector()
{

}

bool TypeDetector::isInteger(std::string value)
{
    std::string::iterator it = value.begin();

    if (!std::isdigit((*it)))
    {
        return false;
    }

    while (it != value.end())
    {
        if (!std::isdigit((*it)))
        {
            return false;
        }
        ++it;
    }
    return true;
}

bool TypeDetector::isInteger(char value)
{
    if (std::isdigit(value))
    {
        return true;
    }
    return false;
}

bool TypeDetector::isNumeric(std::string value)
{
    std::string::iterator it = value.begin();
    bool dot = false;

    if (!std::isdigit((*it)) && (*it) != '.' && (*it) != '+' && (*it) != '-')
    {
        return false;
    }

    while (it != value.end())
    {
        if ((*it) == '.' && dot)
        {
            return false;
        }
        if ((*it) == '.')
        {
            dot = true;
        }
        if (!std::isdigit((*it)) && (*it) != '.')
        {
            return false;
        }
        ++it;
    }
    return true;
}

bool TypeDetector::isNumeric(char value)
{
    if (std::isdigit(value))
    {
        return true;
    }
    return false;
}

bool TypeDetector::isWord(std::string value)
{
    if (value == "")
    {
        return true;
    }
    if (!isNumeric(value))
    {
        return true;
    }
    return false;
}

bool TypeDetector::isWord(char value)
{
    if (value == '\0')
    {
        return true;
    }
    std::stringstream ss;
    ss << value;
    std::string str;
    ss >> str;
    if (!isNumeric(str))
    {
        return true;
    }
    return false;
}

VarType TypeDetector::getType(std::string value)
{
    if (isWord(value))
    {
        return VarType::STRING;
    }
    else if (isInteger(value))
    {
        return VarType::INTEGER;
    }
    else if (isNumeric(value))
    {
        return VarType::DOUBLE;
    }
    return VarType::NONE;
}
