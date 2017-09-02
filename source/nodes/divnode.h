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

#ifndef DIVNODE_H
#define DIVNODE_H

#include "node.h"

class DivNode : public Node
{
protected:
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
public:
    DivNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right);
    std::shared_ptr<Variable> execute(std::shared_ptr<Scope> scope);
    std::string toString();
};

#endif // DIVNODE_H
