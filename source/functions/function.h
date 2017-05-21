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

#ifndef FUNCTION_H
#define FUNCTION_H
#include <string>
#include <vector>
#include <memory>

#include "variables/variable.h"
#include "nodes/node.h"
#include "errors/errors.h"
#include "errors/error.h"
#include "io/fileline.h"

class Function
{
protected:
    std::string name;
    std::shared_ptr<Variable> null;
public:
    std::string getName();
    void setName(std::string name);
    virtual std::shared_ptr<Variable> run(std::shared_ptr<Token> token,
                                          std::shared_ptr<Scope> scope,
                                          std::vector<std::shared_ptr<Node>> variables) = 0;
};

#endif // FUNCTION_H
