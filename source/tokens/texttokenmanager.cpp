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

#include "texttokenmanager.h"

TextTokenManager::TextTokenManager(std::string input)
{
    long long lineNumber = 0;

    for (std::string::iterator it = input.begin(); it != input.end(); ++it)
    {
        if ((*it) == '\n')
        {
            lineNumber++;
        }
        std::shared_ptr<FileLine> fileLine(new FileLine((*it), lineNumber));
        lines.push_back(std::move(fileLine));
    }

    if (lines.size() > 0)
    {
        it = lines.begin();
    }
    else
    {
        it = lines.end();
    }
}

std::shared_ptr<FileLine> TextTokenManager::getCurrent()
{
    if (it != lines.end())
    {
        return (*it);
    }
    std::shared_ptr<FileLine> null;
    return null;
}

std::shared_ptr<FileLine> TextTokenManager::getNext()
{
    if (it != lines.end())
    {
        it++;
        return (*it);
    }
    std::shared_ptr<FileLine> null;
    return null;
}

std::shared_ptr<FileLine> TextTokenManager::getPrev()
{
    if (it != lines.begin() && it != lines.end())
    {
        it--;
        return (*it);
    }
    std::shared_ptr<FileLine> null;
    return null;
}

void TextTokenManager::next()
{
    if (it != lines.end())
    {
        it++;
    }
}

void TextTokenManager::prev()
{
    if (it != lines.begin() && it != lines.end())
    {
        it--;
    }
}

std::shared_ptr<FileLine> TextTokenManager::peak()
{
    if (it != lines.end())
    {
        it++;
        return (*it);
        it--;
    }
    std::shared_ptr<FileLine> null;
    return null;
}

bool TextTokenManager::isEnd()
{
    if (it != lines.end())
    {
        return false;
    }
    return true;
}

bool TextTokenManager::isEmpty()
{
    if (lines.size() > 0)
    {
      return true;
    }
    return false;
}
