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

#ifndef NODE_H
#define NODE_H

#include <string.h>
#include <memory>
#include "../errors/debug.h"
#include "../errors/errors.h"
#include "../variables/variables.h"
#include "../variables/variable.h"
#include "../variables/fakedouble.h"
#include "../variables/fakestring.h"
#include "tokens/token.h"

class Node
{
protected:
    std::shared_ptr<Token> token;
public:
    Node(std::shared_ptr<Token> token)
    {
        this->token = token;
    }

    std::shared_ptr<Token> getToken()
    {
        return token;
    }

    void setToken(std::shared_ptr<Token> token)
    {
        this->token = token;
    }

    virtual std::shared_ptr<Variable> execute() = 0;
    virtual ~Node()
    {

    }
};

#endif // NODE_H
