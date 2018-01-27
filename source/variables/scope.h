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

#ifndef SCOPE_H
#define SCOPE_H

#include "nodes/node.h"
#include "variables/variables.h"
#include <memory>

namespace HuwInterpreter {
    namespace Variables {
        class Node;
        class VariableManager;
        class Variable;

        class Scope
        {
        private:
            std::string functionName;
            std::shared_ptr<Variable> returnValue;
            std::shared_ptr<VariableManager> variableManager;
        public:
            Scope(std::shared_ptr<Passable> passable);
            Scope(std::shared_ptr<VariableManager> variableManager);
            Scope(std::string functionName, std::shared_ptr<Passable> passable);
            Scope(std::string functionName, std::shared_ptr<VariableManager> variableManager);
            std::shared_ptr<VariableManager> getVariableManager();
            void setVariableManager(std::shared_ptr<VariableManager> variableManager);
            std::shared_ptr<Variable> getReturnValue();
            void setReturnValue(std::shared_ptr<Variable> value);
            std::string getFunctionName();
            void setFunctionName(std::string functionName);
        };
    }
}

#endif // SCOPE_H
