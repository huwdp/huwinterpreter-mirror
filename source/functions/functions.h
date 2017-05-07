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

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>
#include "function.h"
#include "functionlist.h"

#include "print.h"



class Functions
{
private:
    std::unordered_map<std::string, std::shared_ptr<Function>> functions;
public:
    Functions();
    std::shared_ptr<Function> get(std::string name);
    std::shared_ptr<Function> set(std::string name, std::string value);
    bool exists(std::shared_ptr<Function> function);
    bool exists(std::string name);
    bool addFunction(std::shared_ptr<Function> function);
    bool addFunction(std::string name);
    bool addFunction(std::string name, std::shared_ptr<Function> function);
    bool removeFunction(std::shared_ptr<Function> function);
    bool removeFunction(std::string name);
};

#endif // FUNCTIONS_H
