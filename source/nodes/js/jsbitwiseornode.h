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

#ifndef JSBITWISEORNODE_H
#define JSBITWISEORNODE_H

#include "../bitwiseornode.h"

class JSBitwiseOrNode : public BitwiseOrNode
{
public:
    JSBitwiseOrNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right);
    std::string toString();
};

#endif // JSBITWISEORNODE_H
