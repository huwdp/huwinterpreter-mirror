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

namespace HuwInterpreter {
    namespace Nodes {
        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateAddConstNode(std::shared_ptr<Passable> passable,
                                                                            std::shared_ptr<Tokens::Token> token,
                                                                            std::string name,
                                                                            std::shared_ptr<Nodes::Node> value)
        {
            return std::make_shared<AddConstNode>(passable, token, name,value);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateAddNode(std::shared_ptr<Passable> passable,
                                                                       std::shared_ptr<Tokens::Token> token,
                                                                       std::shared_ptr<Nodes::Node> left,
                                                                       std::shared_ptr<Nodes::Node> right)
        {
            return std::make_shared<AddNode>(passable, token, left, right);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateAddVarNode(std::shared_ptr<Passable> passable,
                                                                          std::shared_ptr<Tokens::Token> token,
                                                                          std::string name,
                                                                          std::shared_ptr<Nodes::Node> value)
        {
            return std::make_shared<AddVarNode>(passable, token, name, value);
        }

        std::shared_ptr<Node> HuwCodeNodeFactory::CreateArrayGetNode(std::shared_ptr<Passable> passable,
                                                         std::shared_ptr<Tokens::Token> token,
                                                         std::shared_ptr<Node> left,
                                                         std::shared_ptr<Node> right)
        {
            return std::make_shared<ArrayGetNode>(passable, token, left, right);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateBitwiseComplementNode(std::shared_ptr<Passable> passable,
                                                                                     std::shared_ptr<Tokens::Token> token,
                                                                                     std::shared_ptr<Nodes::Node> node)
        {
            return std::make_shared<BitwiseComplementNode>(passable, token, node);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateBitwiseAndNode(std::shared_ptr<Passable> passable,
                                                                              std::shared_ptr<Tokens::Token> token,
                                                                              std::shared_ptr<Nodes::Node> left,
                                                                              std::shared_ptr<Nodes::Node> right)
        {
            return std::make_shared<BitwiseAndNode>(passable, token, left, right);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateBitwiseOrNode(std::shared_ptr<Passable> passable,
                                                                             std::shared_ptr<Tokens::Token> token,
                                                                             std::shared_ptr<Nodes::Node> left,
                                                                             std::shared_ptr<Nodes::Node> right)
        {
            return std::make_shared<BitwiseOrNode>(passable, token, left, right);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateBitwiseXORNode(std::shared_ptr<Passable> passable,
                                                                              std::shared_ptr<Tokens::Token> token,
                                                                              std::shared_ptr<Nodes::Node> left,
                                                                              std::shared_ptr<Nodes::Node> right)
        {
            return std::make_shared<BitwiseXORNode>(passable, token, left, right);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateBracketNode(std::shared_ptr<Passable> passable,
                                                                           std::shared_ptr<Tokens::Token> token,
                                                                           std::shared_ptr<Nodes::Node> node)
        {
            return std::make_shared<BracketNode>(passable, token, node);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateDecrementNode(std::shared_ptr<Passable> passable,
                                                                             std::shared_ptr<Tokens::Token> token,
                                                                             std::shared_ptr<Nodes::Node> node)
        {
            return std::make_shared<DecrementNode>(passable, token, node);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateDivNode(std::shared_ptr<Passable> passable,
                                                                       std::shared_ptr<Tokens::Token> token,
                                                                       std::shared_ptr<Nodes::Node> left,
                                                                       std::shared_ptr<Nodes::Node> right)
        {
            return std::make_shared<DivNode>(passable, token, left, right);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateEqualNode(std::shared_ptr<Passable> passable,
                                                                         std::shared_ptr<Tokens::Token> token,
                                                                         std::shared_ptr<Nodes::Node> left,
                                                                         std::shared_ptr<Nodes::Node> right,
                                                                         std::shared_ptr<Nodes::Node> next,
                                                                         std::shared_ptr<Variables::Scope> scope)
        {
            return std::make_shared<EqualNode>(passable, token, left, right, next, scope);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateGetFuncNode(std::shared_ptr<Passable> passable,
                                                                           std::shared_ptr<Tokens::Token> token,
                                                                           std::string name,
                                                                           std::shared_ptr<Functions::FunctionManager> functionManager,
                                                                           std::vector<std::shared_ptr<Nodes::Node>> arguments)
        {
            return std::make_shared<GetFuncNode>(passable, token, name, functionManager, arguments);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateGetVarNode(std::shared_ptr<Passable> passable,
                                                                          std::shared_ptr<Tokens::Token> token,
                                                                          std::string name)
        {
            return std::make_shared<GetVarNode>(passable, token, name);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateIfAndNode(std::shared_ptr<Passable> passable,
                                                                         std::shared_ptr<Tokens::Token> token,
                                                                         std::shared_ptr<Nodes::Node> left,
                                                                         std::shared_ptr<Nodes::Node> right)
        {
            return std::make_shared<IfAndNode>(passable, token, left, right);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateIfEqualNode(std::shared_ptr<Passable> passable,
                                                                           std::shared_ptr<Tokens::Token> token,
                                                                           std::shared_ptr<Nodes::Node> left,
                                                                           std::shared_ptr<Nodes::Node> right)
        {
            return std::make_shared<IfEqualNode>(passable, token, left, right);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateIfNode(std::shared_ptr<Passable> passable,
                                                                      std::shared_ptr<Tokens::Token> token,
                                                                      std::shared_ptr<Nodes::Node> condition,
                                                                      std::shared_ptr<Nodes::Node> body,
                                                                      std::shared_ptr<Nodes::Node> elseNode)
        {
            return std::make_shared<IfNode>(passable, token, condition, body, elseNode);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateIfNotEqualNode(std::shared_ptr<Passable> passable,
                                                                              std::shared_ptr<Tokens::Token> token,
                                                                              std::shared_ptr<Nodes::Node> left,
                                                                              std::shared_ptr<Nodes::Node> right)
        {
            return std::make_shared<IfNotEqualNode>(passable, token, left, right);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateIfOrNode(std::shared_ptr<Passable> passable,
                                                                        std::shared_ptr<Tokens::Token> token,
                                                                        std::shared_ptr<Nodes::Node> left,
                                                                        std::shared_ptr<Nodes::Node> right)
        {
            return std::make_shared<IfOrNode>(passable, token, left, right);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateIfOverNode(std::shared_ptr<Passable> passable,
                                                                          std::shared_ptr<Tokens::Token> token,
                                                                          std::shared_ptr<Nodes::Node> left,
                                                                          std::shared_ptr<Nodes::Node> right)
        {
            return std::make_shared<IfOverNode>(passable, token, left, right);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateIfOverOrEqualNode(std::shared_ptr<Passable> passable,
                                                                                 std::shared_ptr<Tokens::Token> token,
                                                                                 std::shared_ptr<Nodes::Node> left,
                                                                                 std::shared_ptr<Nodes::Node> right)
        {
            return std::make_shared<IfOverOrEqualNode>(passable, token, left, right);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateIfUnderNode(std::shared_ptr<Passable> passable,
                                                                           std::shared_ptr<Tokens::Token> token,
                                                                           std::shared_ptr<Nodes::Node> left,
                                                                           std::shared_ptr<Nodes::Node> right)
        {
            return std::make_shared<IfUnderNode>(passable, token, left, right);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateIfUnderOrEqualNode(std::shared_ptr<Passable> passable,
                                                                                  std::shared_ptr<Tokens::Token> token,
                                                                                  std::shared_ptr<Nodes::Node> left,
                                                                                  std::shared_ptr<Nodes::Node> right)
        {
            return std::make_shared<IfUnderOrEqualNode>(passable, token, left, right);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateIncrementNode(std::shared_ptr<Passable> passable,
                                                                             std::shared_ptr<Tokens::Token> token,
                                                                             std::shared_ptr<Nodes::Node> node)
        {
            return std::make_shared<IncrementNode>(passable, token, node);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateModNode(std::shared_ptr<Passable> passable,
                                                                       std::shared_ptr<Tokens::Token> token,
                                                                       std::shared_ptr<Nodes::Node> left,
                                                                       std::shared_ptr<Nodes::Node> right)
        {
            return std::make_shared<ModNode>(passable, token, left, right);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateMulNode(std::shared_ptr<Passable> passable,
                                                                       std::shared_ptr<Tokens::Token> token,
                                                                       std::shared_ptr<Nodes::Node> left,
                                                                       std::shared_ptr<Nodes::Node> right)
        {
            return std::make_shared<MulNode>(passable, token, left, right);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateNumberNode(std::shared_ptr<Passable> passable,
                                                                          std::shared_ptr<Tokens::Token> token,
                                                                          std::string value)
        {
            return std::make_shared<NumberNode>(passable, token, value);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateRunNode(std::shared_ptr<Passable> passable,
                                                                       std::shared_ptr<Tokens::Token> token,
                                                                       std::shared_ptr<Nodes::Node> left,
                                                                       std::shared_ptr<Nodes::Node> right)
        {
            return std::make_shared<RunNode>(passable, token, left, right);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateSemicolonNode(std::shared_ptr<Passable> passable,
                                                                             std::shared_ptr<Nodes::Node> node)
        {
            return std::make_shared<SemicolonNode>(passable, node);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateSetReturnNode(std::shared_ptr<Passable> passable,
                                                                             std::shared_ptr<Nodes::Node> node)
        {
            return std::make_shared<SetReturnNode>(passable, node);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateSetVarNode(std::shared_ptr<Passable> passable,
                                                                          std::shared_ptr<Tokens::Token> token,
                                                                          std::string name,
                                                                          std::shared_ptr<Nodes::Node> value)
        {
            return std::make_shared<SetVarNode>(passable, token, name, value);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateSubNode(std::shared_ptr<Passable> passable,
                                                                       std::shared_ptr<Tokens::Token> token,
                                                                       std::shared_ptr<Nodes::Node> left,
                                                                       std::shared_ptr<Nodes::Node> right)
        {
            return std::make_shared<SubNode>(passable, token, left, right);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateTextNode(std::shared_ptr<Passable> passable,
                                                                        std::shared_ptr<Tokens::Token> token,
                                                                        std::string value)
        {
            return std::make_shared<TextNode>(passable, token, value);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateUnaryMinusNode(std::shared_ptr<Passable> passable,
                                                                              std::shared_ptr<Tokens::Token> token,
                                                                              std::shared_ptr<Nodes::Node> node)
        {
            return std::make_shared<UnaryMinusNode>(passable, token, node);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateUnaryNotNode(std::shared_ptr<Passable> passable,
                                                                            std::shared_ptr<Tokens::Token> token,
                                                                            std::shared_ptr<Nodes::Node> node)
        {
            return std::make_shared<UnaryNotNode>(passable, token, node);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateWhileNode(std::shared_ptr<Passable> passable,
                                                                         std::shared_ptr<Tokens::Token> token,
                                                                         std::shared_ptr<Nodes::Node> condition,
                                                                         std::shared_ptr<Nodes::Node> body,
                                                                         std::shared_ptr<Nodes::Node> next)
        {
            return std::make_shared<WhileNode>(passable, token, std::move(condition), std::move(body), next);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateLeftShiftNode(std::shared_ptr<Passable> passable,
                                                                             std::shared_ptr<Tokens::Token> token,
                                                                             std::shared_ptr<Nodes::Node> left,
                                                                             std::shared_ptr<Nodes::Node> right)
        {
            return std::make_shared<LeftShiftNode>(passable, token, left, right);
        }

        std::shared_ptr<Nodes::Node> HuwCodeNodeFactory::CreateRightShiftNode(std::shared_ptr<Passable> passable,
                                                                              std::shared_ptr<Tokens::Token> token,
                                                                              std::shared_ptr<Nodes::Node> left,
                                                                              std::shared_ptr<Nodes::Node> right)
        {
            return std::make_shared<RightShiftNode>(passable, token, left, right);
        }
    }
}


