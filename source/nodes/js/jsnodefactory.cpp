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

#include "jsnodefactory.h"

JSNodeFactory::JSNodeFactory()
{

}

std::shared_ptr<Node> JSNodeFactory::CreateAddConstNode(std::shared_ptr<Token> token,
                                                      std::string name,
                                                      std::shared_ptr<Node> value)
{
    return std::make_shared<JSAddConstNode>(token,name,value);
}

std::shared_ptr<Node> JSNodeFactory::CreateAddNode(std::shared_ptr<Token> token,
                                                 std::shared_ptr<Node> left,
                                                 std::shared_ptr<Node> right)
{
    return std::make_shared<JSAddNode>(token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateAddVarNode(std::shared_ptr<Token> token,
                                                    std::string name,
                                                    std::shared_ptr<Node> value)
{
    return std::make_shared<JSAddVarNode>(token, name, value);
}

std::shared_ptr<Node> JSNodeFactory::CreateBitwiseAndNode(std::shared_ptr<Token> token,
                                                        std::shared_ptr<Node> left,
                                                        std::shared_ptr<Node> right)
{
    return std::make_shared<JSBitwiseAndNode>(token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateBitwiseOrNode(std::shared_ptr<Token> token,
                                                       std::shared_ptr<Node> left,
                                                       std::shared_ptr<Node> right)
{
    return std::make_shared<JSBitwiseOrNode>(token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateBracketNode(std::shared_ptr<Token> token,
                                                     std::shared_ptr<Node> node)
{
    return std::make_shared<JSBracketNode>(token, node);
}

std::shared_ptr<Node> JSNodeFactory::CreateDecrementNode(std::shared_ptr<Token> token,
                                                       std::shared_ptr<Node> node)
{
    return std::make_shared<JSDecrementNode>(token, node);
}

std::shared_ptr<Node> JSNodeFactory::CreateDivNode(std::shared_ptr<Token> token,
                                                 std::shared_ptr<Node> left,
                                                 std::shared_ptr<Node> right)
{
    return std::make_shared<JSDivNode>(token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateEqualNode(std::shared_ptr<Token> token,
                                                   std::shared_ptr<Node> left,
                                                   std::shared_ptr<Node> right,
                                                   std::shared_ptr<Node> next,
                                                   std::shared_ptr<Scope> scope)
{
    return std::make_shared<JSEqualNode>(token, left, right, next, scope);
}

std::shared_ptr<Node> JSNodeFactory::CreateGetFuncNode(std::shared_ptr<Token> token,
                                                     std::string name,
                                                     std::shared_ptr<Functions> functions,
                                                     std::vector<std::shared_ptr<Node>> arguments)
{
    return std::make_shared<JSGetFuncNode>(token, name, functions, arguments);
}

std::shared_ptr<Node> JSNodeFactory::CreateGetVarNode(std::shared_ptr<Token> token,
                                                    std::string name)
{
    return std::make_shared<JSGetVarNode>(token, name);
}

std::shared_ptr<Node> JSNodeFactory::CreateIfAndNode(std::shared_ptr<Token> token,
                                                   std::shared_ptr<Node> left,
                                                   std::shared_ptr<Node> right)
{
    return std::make_shared<JSIfAndNode>(token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateIfEqualNode(std::shared_ptr<Token> token,
                                                     std::shared_ptr<Node> left,
                                                     std::shared_ptr<Node> right)
{
    return std::make_shared<JSIfEqualNode>(token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateIfNode(std::shared_ptr<Token> token,
                                                std::shared_ptr<Node> condition,
                                                std::shared_ptr<Node> body,
                                                std::shared_ptr<Node> elseNode)
{
    return std::make_shared<JSIfNode>(token, condition, body, elseNode);
}

std::shared_ptr<Node> JSNodeFactory::CreateIfNotEqualNode(std::shared_ptr<Token> token,
                                                        std::shared_ptr<Node> left,
                                                        std::shared_ptr<Node> right)
{
    return std::make_shared<JSIfNotEqualNode>(token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateIfOrNode(std::shared_ptr<Token> token,
                                                  std::shared_ptr<Node> left,
                                                  std::shared_ptr<Node> right)
{
    return std::make_shared<JSIfOrNode>(token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateIfOverNode(std::shared_ptr<Token> token,
                                                    std::shared_ptr<Node> left,
                                                    std::shared_ptr<Node> right)
{
    return std::make_shared<JSIfOverNode>(token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateIfOverOrEqualNode(std::shared_ptr<Token> token,
                                                           std::shared_ptr<Node> left,
                                                           std::shared_ptr<Node> right)
{
    return std::make_shared<JSIfOverOrEqualNode>(token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateIfUnderNode(std::shared_ptr<Token> token,
                                                     std::shared_ptr<Node> left,
                                                     std::shared_ptr<Node> right)
{
    return std::make_shared<JSIfUnderNode>(token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateIfUnderOrEqualNode(std::shared_ptr<Token> token,
                                                            std::shared_ptr<Node> left,
                                                            std::shared_ptr<Node> right)
{
    return std::make_shared<JSIfUnderOrEqualNode>(token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateIncrementNode(std::shared_ptr<Token> token,
                                                       std::shared_ptr<Node> node)
{
    return std::make_shared<JSIncrementNode>(token, node);
}

std::shared_ptr<Node> JSNodeFactory::CreateModNode(std::shared_ptr<Token> token,
                                                 std::shared_ptr<Node> left,
                                                 std::shared_ptr<Node> right)
{
    return std::make_shared<JSModNode>(token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateMulNode(std::shared_ptr<Token> token,
                                                 std::shared_ptr<Node> left,
                                                 std::shared_ptr<Node> right)
{
    return std::make_shared<JSMulNode>(token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateNumberNode(std::shared_ptr<Token> token,
                                                    std::string value)
{
    return std::make_shared<JSNumberNode>(token, value);
}

std::shared_ptr<Node> JSNodeFactory::CreateRunNode(std::shared_ptr<Token> token,
                                                 std::shared_ptr<Node> left,
                                                 std::shared_ptr<Node> right)
{
    return std::make_shared<JSRunNode>(token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateSetReturnNode(std::shared_ptr<Node> node)
{
    return std::make_shared<JSSetReturnNode>(node);
}

std::shared_ptr<Node> JSNodeFactory::CreateSemicolonNode(std::shared_ptr<Node> node)
{
    return std::make_shared<SemicolonNode>(node);
}

std::shared_ptr<Node> JSNodeFactory::CreateSetVarNode(std::shared_ptr<Token> token,
                                                    std::string name,
                                                    std::shared_ptr<Node> value)
{
    return std::make_shared<JSSetVarNode>(token, name, value);
}

std::shared_ptr<Node> JSNodeFactory::CreateSubNode(std::shared_ptr<Token> token,
                                                 std::shared_ptr<Node> left,
                                                 std::shared_ptr<Node> right)
{
    return std::make_shared<JSSubNode>(token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateTextNode(std::shared_ptr<Token> token,
                                                  std::string value)
{
    return std::make_shared<JSTextNode>(token, value);
}

std::shared_ptr<Node> JSNodeFactory::CreateUnaryMinusNode(std::shared_ptr<Token> token,
                                                        std::shared_ptr<Node> node)
{
    return std::make_shared<JSUnaryMinusNode>(token, node);
}

std::shared_ptr<Node> JSNodeFactory::CreateUnaryNotNode(std::shared_ptr<Token> token,
                                                      std::shared_ptr<Node> node)
{
    return std::make_shared<JSUnaryNotNode>(token, node);
}

std::shared_ptr<Node> JSNodeFactory::CreateWhileNode(std::shared_ptr<Token> token,
                                                   std::shared_ptr<Node> condition,
                                                   std::shared_ptr<Node> body,
                                                   std::shared_ptr<Node> next)
{
    return std::make_shared<JSWhileNode>(token, std::move(condition), std::move(body), next);
}
