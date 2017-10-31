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
#include "errors/debug.h"
#include "errors/errors.h"
#include "variables/variables.h"
#include "variables/variable.h"
#include "variables/doublevariable.h"
#include "variables/stringvariable.h"
#include "tokens/token.h"
#include "variables/scope.h"
#include "common/passable.h"

enum NodeType {ADDCONSTNODETYPE,
               ADDNODETYPE,
               ADDVARNODETYPE,
               BITWISEANDNODETYPE,
               BITWISEORNODETYPE,
               BRACKETNODETYPE,
               DECREMENTNODETYPE,
               DIVNODETYPE,
               EQUALNODETYPE,
               GETFUNCNODETYPE,
               GETVARNODETYPE,
               IFANDNODETYPE,
               IFEQUALNODETYPE,
               IFNODETYPE,
               IFNOTEQUALNODETYPE,
               IFORNODETYPE,
               IFOVERNODETYPE,
               IFOVEROREQUALNODETYPE,
               IFUNDERNODETYPE,
               IFUNDERORRQUALNODETYPE,
               INCREMENTNODETYPE,
               MODNODETYPE,
               MULNODETYPE,
               NUMBERNODETYPE,
               RUNNODETYPE,
               SEMICOLONNODETYPE,
               SETRETURNNODETYPE,
               SETVARNODETYPE,
               SUBNODETYPE,
               TEXTNODETYPE,
               UNARYMINUSNODETYPE,
               UNARYNOTNODETYPE,
               WHILENODETYPE };

class Scope;

class Node
{
protected:
    std::string internalName;
    std::shared_ptr<Variable> null;
    std::shared_ptr<Token> token;
    std::shared_ptr<Passable> passable;
public:
    Node(std::string internalName, std::shared_ptr<Passable> passable, std::shared_ptr<Token> token)
    {
        this->internalName = internalName;
        this->passable = passable;
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

    virtual std::shared_ptr<Variable> execute(std::shared_ptr<Scope> globalScope, std::shared_ptr<Scope> scope) = 0;
    virtual std::string toString() = 0;
    virtual NodeType getType() = 0;
    virtual ~Node()
    {

    }
};

#endif // NODE_H
