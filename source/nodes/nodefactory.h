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



#ifndef NODEFACTORY_H
#define NODEFACTORY_H

#include "node.h"
#include  "equalnode.h"

#include  "ifequalnode.h"
#include  "ifnotequalnode.h"
#include  "ifundernode.h"
#include  "ifunderorequalnode.h"
#include  "ifovernode.h"
#include  "ifoverorequalnode.h"
#include "ifnode.h"

#include "whilenode.h"

#include  "ifandnode.h"
#include  "ifornode.h"
#include  "bitwiseandnode.h"
#include  "bitwiseornode.h"

#include  "getvarnode.h"
#include  "setvarnode.h"
#include  "addconstnode.h"
#include  "addvarnode.h"
#include  "getfuncnode.h"
#include  "numbernode.h"
#include  "textnode.h"
#include  "runnode.h"

#include  "addnode.h"
#include  "subnode.h"
#include  "mulnode.h"
#include  "divnode.h"
#include  "modnode.h"
#include  "unaryminusnode.h"
#include  "unarynotnode.h"

#include  "setreturnnode.h"

#include  "bracketnode.h"

#include  "incrementnode.h"
#include  "decrementnode.h"

class NodeFactory
{
public:
    virtual std::shared_ptr<Node> CreateAddConstNode(std::shared_ptr<Token> token, std::string name, std::shared_ptr<Node> value, std::shared_ptr<Node> next) = 0;
    virtual std::shared_ptr<Node> CreateAddNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right) = 0;
    virtual std::shared_ptr<Node> CreateAddVarNode(std::shared_ptr<Token> token, std::string name, std::shared_ptr<Node> value, std::shared_ptr<Node> next) = 0;
    virtual std::shared_ptr<Node> CreateBitwiseAndNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right) = 0;
    virtual std::shared_ptr<Node> CreateBitwiseOrNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right) = 0;
    virtual std::shared_ptr<Node> CreateBracketNode(std::shared_ptr<Token> token, std::shared_ptr<Node> node) = 0;
    virtual std::shared_ptr<Node> CreateDecrementNode(std::shared_ptr<Token> token, std::shared_ptr<Node> node) = 0;
    virtual std::shared_ptr<Node> CreateDivNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right) = 0;
    virtual std::shared_ptr<Node> CreateEqualNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right, std::shared_ptr<Node> next, std::shared_ptr<Scope> scope) = 0;
    virtual std::shared_ptr<Node> CreateGetFuncNode(std::shared_ptr<Token> token, std::string name, std::shared_ptr<Functions> functions, std::vector<std::shared_ptr<Node>> arguments) = 0;
    virtual std::shared_ptr<Node> CreateGetVarNode(std::shared_ptr<Token> token, std::string name) = 0;
    virtual std::shared_ptr<Node> CreateIfAndNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right) = 0;
    virtual std::shared_ptr<Node> CreateIfEqualNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right) = 0;
    virtual std::shared_ptr<Node> CreateIfNode(std::shared_ptr<Token> token, std::shared_ptr<Node> condition, std::shared_ptr<Node> body, std::shared_ptr<Node> elseNode) = 0;
    virtual std::shared_ptr<Node> CreateIfNotEqualNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right) = 0;
    virtual std::shared_ptr<Node> CreateIfOrNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right) = 0;
    virtual std::shared_ptr<Node> CreateIfOverNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right) = 0;
    virtual std::shared_ptr<Node> CreateIfOverOrEqualNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right) = 0;
    virtual std::shared_ptr<Node> CreateIfUnderNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right) = 0;
    virtual std::shared_ptr<Node> CreateIfUnderOrEqualNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right) = 0;
    virtual std::shared_ptr<Node> CreateIncrementNode(std::shared_ptr<Token> token, std::shared_ptr<Node> node) = 0;
    virtual std::shared_ptr<Node> CreateModNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right) = 0;
    virtual std::shared_ptr<Node> CreateMulNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right) = 0;
    virtual std::shared_ptr<Node> CreateNumberNode(std::shared_ptr<Token> token, std::string value) = 0;
    virtual std::shared_ptr<Node> CreateRunNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right) = 0;
    virtual std::shared_ptr<Node> CreateSetReturnNode(std::shared_ptr<Node> node) = 0;
    virtual std::shared_ptr<Node> CreateSetVarNode(std::shared_ptr<Token> token, std::string name, std::shared_ptr<Node> value, std::shared_ptr<Node> next) = 0;
    virtual std::shared_ptr<Node> CreateSubNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right) = 0;
    virtual std::shared_ptr<Node> CreateTextNode(std::shared_ptr<Token> token, std::string value) = 0;
    virtual std::shared_ptr<Node> CreateUnaryMinusNode(std::shared_ptr<Token> token, std::shared_ptr<Node> node) = 0;
    virtual std::shared_ptr<Node> CreateUnaryNotNode(std::shared_ptr<Token> token, std::shared_ptr<Node> node) = 0;
    virtual std::shared_ptr<Node> CreateWhileNode(std::shared_ptr<Token> token, std::shared_ptr<Node> condition, std::shared_ptr<Node> body, std::shared_ptr<Node> next) = 0;
};

#endif // NODEFACTORY_H
