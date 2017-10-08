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

#include "huwcodenodefactory.h"

HuwCodeNodeFactory::HuwCodeNodeFactory()
{

}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateAddConstNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                      std::string name,
                                                      std::shared_ptr<Node> value)
{
    return std::make_shared<AddConstNode>(passible, token, name,value);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateAddNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                 std::shared_ptr<Node> left,
                                                 std::shared_ptr<Node> right)
{
    return std::make_shared<AddNode>(passible, token, left, right);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateAddVarNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                    std::string name,
                                                    std::shared_ptr<Node> value)
{
    return std::make_shared<AddVarNode>(passible, token, name, value);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateBitwiseAndNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                        std::shared_ptr<Node> left,
                                                        std::shared_ptr<Node> right)
{
    return std::make_shared<BitwiseAndNode>(passible, token, left, right);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateBitwiseOrNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                       std::shared_ptr<Node> left,
                                                       std::shared_ptr<Node> right)
{
    return std::make_shared<BitwiseOrNode>(passible, token, left, right);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateBracketNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                     std::shared_ptr<Node> node)
{
    return std::make_shared<BracketNode>(passible, token, node);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateDecrementNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                       std::shared_ptr<Node> node)
{
    return std::make_shared<DecrementNode>(passible, token, node);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateDivNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                 std::shared_ptr<Node> left,
                                                 std::shared_ptr<Node> right)
{
    return std::make_shared<DivNode>(passible, token, left, right);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateEqualNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                   std::shared_ptr<Node> left,
                                                   std::shared_ptr<Node> right,
                                                   std::shared_ptr<Node> next,
                                                   std::shared_ptr<Scope> scope)
{
    return std::make_shared<EqualNode>(passible, token, left, right, next, scope);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateGetFuncNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                     std::string name,
                                                     std::shared_ptr<Functions> functions,
                                                     std::vector<std::shared_ptr<Node>> arguments)
{
    return std::make_shared<GetFuncNode>(passible, token, name, functions, arguments);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateGetVarNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                    std::string name)
{
    return std::make_shared<GetVarNode>(passible, token, name);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateIfAndNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                   std::shared_ptr<Node> left,
                                                   std::shared_ptr<Node> right)
{
    return std::make_shared<IfAndNode>(passible, token, left, right);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateIfEqualNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                     std::shared_ptr<Node> left,
                                                     std::shared_ptr<Node> right)
{
    return std::make_shared<IfEqualNode>(passible, token, left, right);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateIfNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                std::shared_ptr<Node> condition,
                                                std::shared_ptr<Node> body,
                                                std::shared_ptr<Node> elseNode)
{
    return std::make_shared<IfNode>(passible, token, condition, body, elseNode);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateIfNotEqualNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                        std::shared_ptr<Node> left,
                                                        std::shared_ptr<Node> right)
{
    return std::make_shared<IfNotEqualNode>(passible, token, left, right);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateIfOrNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                  std::shared_ptr<Node> left,
                                                  std::shared_ptr<Node> right)
{
    return std::make_shared<IfOrNode>(passible, token, left, right);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateIfOverNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                    std::shared_ptr<Node> left,
                                                    std::shared_ptr<Node> right)
{
    return std::make_shared<IfOverNode>(passible, token, left, right);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateIfOverOrEqualNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                           std::shared_ptr<Node> left,
                                                           std::shared_ptr<Node> right)
{
    return std::make_shared<IfOverOrEqualNode>(passible, token, left, right);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateIfUnderNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                     std::shared_ptr<Node> left,
                                                     std::shared_ptr<Node> right)
{
    return std::make_shared<IfUnderNode>(passible, token, left, right);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateIfUnderOrEqualNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                            std::shared_ptr<Node> left,
                                                            std::shared_ptr<Node> right)
{
    return std::make_shared<IfUnderOrEqualNode>(passible, token, left, right);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateIncrementNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                       std::shared_ptr<Node> node)
{
    return std::make_shared<IncrementNode>(passible, token, node);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateModNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                 std::shared_ptr<Node> left,
                                                 std::shared_ptr<Node> right)
{
    return std::make_shared<ModNode>(passible, token, left, right);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateMulNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                 std::shared_ptr<Node> left,
                                                 std::shared_ptr<Node> right)
{
    return std::make_shared<MulNode>(passible, token, left, right);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateNumberNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                    std::string value)
{
    return std::make_shared<NumberNode>(passible, token, value);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateRunNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                 std::shared_ptr<Node> left,
                                                 std::shared_ptr<Node> right)
{
    return std::make_shared<RunNode>(passible, token, left, right);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateSemicolonNode(std::shared_ptr<Passible> passible, std::shared_ptr<Node> node)
{
    return std::make_shared<SemicolonNode>(passible, node);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateSetReturnNode(std::shared_ptr<Passible> passible, std::shared_ptr<Node> node)
{
    return std::make_shared<SetReturnNode>(passible, node);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateSetVarNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                    std::string name,
                                                    std::shared_ptr<Node> value)
{
    return std::make_shared<SetVarNode>(passible, token, name, value);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateSubNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                 std::shared_ptr<Node> left,
                                                 std::shared_ptr<Node> right)
{
    return std::make_shared<SubNode>(passible, token, left, right);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateTextNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                  std::string value)
{
    return std::make_shared<TextNode>(passible, token, value);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateUnaryMinusNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                        std::shared_ptr<Node> node)
{
    return std::make_shared<UnaryMinusNode>(passible, token, node);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateUnaryNotNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                      std::shared_ptr<Node> node)
{
    return std::make_shared<UnaryNotNode>(passible, token, node);
}

std::shared_ptr<Node> HuwCodeNodeFactory::CreateWhileNode(std::shared_ptr<Passible> passible, std::shared_ptr<Token> token,
                                                   std::shared_ptr<Node> condition,
                                                   std::shared_ptr<Node> body,
                                                   std::shared_ptr<Node> next)
{
    return std::make_shared<WhileNode>(passible, token, std::move(condition), std::move(body), next);
}


