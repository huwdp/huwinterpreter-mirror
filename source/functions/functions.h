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

namespace HuwInterpreter {
    namespace Functions {
        class FunctionManager
        {
        private:
            std::shared_ptr<Passable> passable;
            std::unordered_map<std::string, std::shared_ptr<Functions::Function>> functions;
        public:
            FunctionManager(std::shared_ptr<Passable> passable);
            void init();
            std::shared_ptr<Functions::Function> get(std::string name);
            std::shared_ptr<Functions::Function> set(std::string name, std::string value);
            bool exists(std::shared_ptr<Functions::Function> function);
            bool exists(std::string name);
            bool addFunction(std::shared_ptr<Functions::Function> function);
            bool addFunction(std::string name);
            bool addFunction(std::string name, std::shared_ptr<Functions::Function> function);
            bool setFunction(std::string name, std::shared_ptr<Functions::Function> function);
            bool removeFunction(std::shared_ptr<Functions::Function> function);
            bool removeFunction(std::string name);
            std::string toString();
        };
    }
}

#endif // FUNCTIONS_H
