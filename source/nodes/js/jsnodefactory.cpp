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

std::shared_ptr<Node> JSNodeFactory::CreateAddConstNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                      std::string name,
                                                      std::shared_ptr<Node> value)
{
    return std::make_shared<JSAddConstNode>(passable, token,name,value);
}

std::shared_ptr<Node> JSNodeFactory::CreateAddNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                 std::shared_ptr<Node> left,
                                                 std::shared_ptr<Node> right)
{\
    return std::make_shared<JSAddNode>(passable, token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateAddVarNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                    std::string name,
                                                    std::shared_ptr<Node> value)
{
    return std::make_shared<JSAddVarNode>(passable, token, name, value);
}

std::shared_ptr<Node> JSNodeFactory::CreateBitwiseAndNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                        std::shared_ptr<Node> left,
                                                        std::shared_ptr<Node> right)
{
    return std::make_shared<JSBitwiseAndNode>(passable, token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateBitwiseOrNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                       std::shared_ptr<Node> left,
                                                       std::shared_ptr<Node> right)
{
    return std::make_shared<JSBitwiseOrNode>(passable, token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateBracketNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                     std::shared_ptr<Node> node)
{
    return std::make_shared<JSBracketNode>(passable, token, node);
}

std::shared_ptr<Node> JSNodeFactory::CreateDecrementNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                       std::shared_ptr<Node> node)
{
    return std::make_shared<JSDecrementNode>(passable, token, node);
}

std::shared_ptr<Node> JSNodeFactory::CreateDivNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                 std::shared_ptr<Node> left,
                                                 std::shared_ptr<Node> right)
{
    return std::make_shared<JSDivNode>(passable, token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateEqualNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                   std::shared_ptr<Node> left,
                                                   std::shared_ptr<Node> right,
                                                   std::shared_ptr<Node> next,
                                                   std::shared_ptr<Scope> scope)
{
    return std::make_shared<JSEqualNode>(passable, token, left, right, next, scope);
}

std::shared_ptr<Node> JSNodeFactory::CreateGetFuncNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                     std::string name,
                                                     std::shared_ptr<Functions> functions,
                                                     std::vector<std::shared_ptr<Node>> arguments)
{
    return std::make_shared<JSGetFuncNode>(passable, token, name, functions, arguments);
}

std::shared_ptr<Node> JSNodeFactory::CreateGetVarNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                    std::string name)
{
    return std::make_shared<JSGetVarNode>(passable, token, name);
}

std::shared_ptr<Node> JSNodeFactory::CreateIfAndNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                   std::shared_ptr<Node> left,
                                                   std::shared_ptr<Node> right)
{
    return std::make_shared<JSIfAndNode>(passable, token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateIfEqualNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                     std::shared_ptr<Node> left,
                                                     std::shared_ptr<Node> right)
{
    return std::make_shared<JSIfEqualNode>(passable, token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateIfNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                std::shared_ptr<Node> condition,
                                                std::shared_ptr<Node> body,
                                                std::shared_ptr<Node> elseNode)
{
    return std::make_shared<JSIfNode>(passable, token, condition, body, elseNode);
}

std::shared_ptr<Node> JSNodeFactory::CreateIfNotEqualNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                        std::shared_ptr<Node> left,
                                                        std::shared_ptr<Node> right)
{
    return std::make_shared<JSIfNotEqualNode>(passable, token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateIfOrNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                  std::shared_ptr<Node> left,
                                                  std::shared_ptr<Node> right)
{
    return std::make_shared<JSIfOrNode>(passable, token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateIfOverNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                    std::shared_ptr<Node> left,
                                                    std::shared_ptr<Node> right)
{
    return std::make_shared<JSIfOverNode>(passable, token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateIfOverOrEqualNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                           std::shared_ptr<Node> left,
                                                           std::shared_ptr<Node> right)
{
    return std::make_shared<JSIfOverOrEqualNode>(passable, token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateIfUnderNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                     std::shared_ptr<Node> left,
                                                     std::shared_ptr<Node> right)
{
    return std::make_shared<JSIfUnderNode>(passable, token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateIfUnderOrEqualNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                            std::shared_ptr<Node> left,
                                                            std::shared_ptr<Node> right)
{
    return std::make_shared<JSIfUnderOrEqualNode>(passable, token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateIncrementNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                       std::shared_ptr<Node> node)
{
    return std::make_shared<JSIncrementNode>(passable, token, node);
}

std::shared_ptr<Node> JSNodeFactory::CreateModNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                 std::shared_ptr<Node> left,
                                                 std::shared_ptr<Node> right)
{
    return std::make_shared<JSModNode>(passable, token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateMulNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                 std::shared_ptr<Node> left,
                                                 std::shared_ptr<Node> right)
{
    return std::make_shared<JSMulNode>(passable, token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateNumberNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                    std::string value)
{
    return std::make_shared<JSNumberNode>(passable, token, value);
}

std::shared_ptr<Node> JSNodeFactory::CreateRunNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                 std::shared_ptr<Node> left,
                                                 std::shared_ptr<Node> right)
{
    return std::make_shared<JSRunNode>(passable, token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateSetReturnNode(std::shared_ptr<Passable> passable, std::shared_ptr<Node> node)
{
    return std::make_shared<JSSetReturnNode>(passable, node);
}

std::shared_ptr<Node> JSNodeFactory::CreateSemicolonNode(std::shared_ptr<Passable> passable, std::shared_ptr<Node> node)
{
    return std::make_shared<SemicolonNode>(passable, node);
}

std::shared_ptr<Node> JSNodeFactory::CreateSetVarNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                    std::string name,
                                                    std::shared_ptr<Node> value)
{
    return std::make_shared<JSSetVarNode>(passable, token, name, value);
}

std::shared_ptr<Node> JSNodeFactory::CreateSubNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                 std::shared_ptr<Node> left,
                                                 std::shared_ptr<Node> right)
{
    return std::make_shared<JSSubNode>(passable, token, left, right);
}

std::shared_ptr<Node> JSNodeFactory::CreateTextNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                  std::string value)
{
    return std::make_shared<JSTextNode>(passable, token, value);
}

std::shared_ptr<Node> JSNodeFactory::CreateUnaryMinusNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                        std::shared_ptr<Node> node)
{
    return std::make_shared<JSUnaryMinusNode>(passable, token, node);
}

std::shared_ptr<Node> JSNodeFactory::CreateUnaryNotNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                      std::shared_ptr<Node> node)
{
    return std::make_shared<JSUnaryNotNode>(passable, token, node);
}

std::shared_ptr<Node> JSNodeFactory::CreateWhileNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token,
                                                   std::shared_ptr<Node> condition,
                                                   std::shared_ptr<Node> body,
                                                   std::shared_ptr<Node> next)
{
    return std::make_shared<JSWhileNode>(passable, token, std::move(condition), std::move(body), next);
}
