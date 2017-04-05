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

#ifndef TEXTNODE_H
#define TEXTNODE_H

#include "node.h"
#include "../variables/variabletypefactory.h"

class TextNode : public Node
{
private:
    std::shared_ptr<Variable> value;
public:
    TextNode(std::shared_ptr<Token> token, std::string value);
    std::shared_ptr<Variable> execute();
};

#endif // TEXTNODE_H