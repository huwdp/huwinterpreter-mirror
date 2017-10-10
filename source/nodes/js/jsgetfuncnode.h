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

#ifndef JSGETFUNCNODE_H
#define JSGETFUNCNODE_H

#include "../getfuncnode.h"
#include "functions/function.h"
#include "functions/functions.h"

class JSGetFuncNode : public GetFuncNode
{
public:
    JSGetFuncNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token, std::string name, std::shared_ptr<Functions> functions, std::vector<std::shared_ptr<Node>> arguments);
    std::string toString();
};

#endif // JSGETFUNCNODE_H
