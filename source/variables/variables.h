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

#ifndef VARIABLES_H
#define VARIABLES_H
#include <vector>
#include <string>
#include <iostream>
#include <string>
#include <unordered_map>
#include "variable.h"
#include "doublevariable.h"
#include "stringvariable.h"
#include "constantvariable.h"
#include "types/typedetector.h"

namespace HuwInterpreter {
    namespace Variables {
        class VariableManager
        {
        private:
            std::shared_ptr<Passable> passable;
            std::unordered_map<std::string, std::shared_ptr<Variable>> variables;
        public:
            std::shared_ptr<Variable> nullVariable;
            VariableManager(std::shared_ptr<Passable> passable, bool isEmpty);
            ~VariableManager();
            void addDefaultVariables(bool isEmpty);
            std::shared_ptr<Variable> get(std::string name);
            bool set(std::string name, std::shared_ptr<Variable> variable);
            std::shared_ptr<Variable> exists(std::shared_ptr<Variable> variable);
            std::shared_ptr<Variable> exists(std::string name);
            bool addVariable(std::shared_ptr<Variable> variable);
            bool addVariable(std::string name, std::shared_ptr<Variable> variable);
            bool removeVariable(std::shared_ptr<Variable> variable);
            bool removeVariable(std::string name);
            void setParent(std::shared_ptr<VariableManager> parent);
            bool setVariable(std::string name, std::shared_ptr<Variable> variable);
        };
    }
}

#endif // VARIABLES_H
