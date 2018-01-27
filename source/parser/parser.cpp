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

#include "parser.h"

namespace HuwInterpreter {
    Parser::Parser(std::vector<std::shared_ptr<Tokens::Token>> tokens,
                   std::shared_ptr<NodeFactory> nodeFactory)
    {
        this->nodeFactory = nodeFactory;
        this->passable = std::make_shared<Passable>();
        this->compilation = true;
        this->tokens = tokens;
        this->functions = std::move(std::make_shared<Functions::FunctionManager>(passable));
        functions->init();
        customFunctions = std::move(std::make_shared<Functions::FunctionManager>(passable));
        if (!tokens.empty())
        {
            it = this->tokens.begin();
            this->currentToken = (*it);
        }
    }

    bool Parser::getCompilation()
    {
        return compilation;
    }

    void Parser::setCompilation(bool compilation)
    {
        this->compilation = compilation;
    }

    void Parser::acceptIndentation()
    {
        while ((this->currentToken->getContent() == " " || this->currentToken->getContent() == "\t") && !tokens.empty())
        {
            nextToken();
        }
    }

    void Parser::acceptSemicolon()
    {
        if (this->currentToken->getContent() == ";" && !tokens.empty())
        {
            nextToken();
        }
    }

    void Parser::nextToken()
    {
        if (it < tokens.end())
        {
            currentToken = (*it);
            ++it;
        }
    }

    void Parser::prevToken()
    {
        if (it != tokens.begin())
        {
            it--;
            currentToken = (*it);
        }
    }

    std::shared_ptr<Tokens::Token> Parser::peakToken()
    {
        std::shared_ptr<Tokens::Token> output;
        if (it != tokens.end())
        {
            output = (*it);
        }
        return output;
    }

    bool Parser::accept(std::string s)
    {
        if (this->currentToken->getContent() == s)
        {
            nextToken();
            return true;
        }
        return false;
    }

    bool Parser::accept(Types::TokenType tokenType)
    {
        if (this->currentToken->getType() == tokenType)
        {
            nextToken();
            return true;
        }
        return false;
    }

    bool Parser::expect(std::string s)
    {
        if (accept(s))
        {
            return true;
        }
        compilation = false;
        errorMessage(syntaxError(currentToken->getContent()), currentToken);
        return false;
    }

    bool Parser::expect(Types::TokenType tokenType)
    {
        if (accept(tokenType))
        {
            return true;
        }
        compilation = false;
        errorMessage(syntaxError(currentToken->getContent()), currentToken);
        return false;
    }

    std::string Parser::syntaxError(std::string content)
    {
        std::string errorMsg;
        errorMsg.append("Parse error: syntax error, unexpected \"")
                .append(content)
                .append("\"");
        errorMessage(errorMsg, currentToken);
        return errorMsg;
    }

    bool Parser::expectSemicolon()
    {
        if (!expect(Types::SEMICOLON))
        {
          return false;
        }
        acceptIndentation();
        acceptSemicolon();
        return true;
    }

    void Parser::errorMessage(std::string errorMsg, std::shared_ptr<Tokens::Token> currentToken)
    {
        passable->getErrorManager()->add(passable->getErrorFactory()->syntaxError(currentToken, errorMsg));
    }

    std::shared_ptr<Nodes::Node> Parser::parseSquareBrackets(std::shared_ptr<Nodes::Node> node)
    {
        acceptIndentation();
        if (!tokens.empty() && compilation)
        {
            if (accept(Types::LEFTSQUAREBRACKET))
            {
                acceptIndentation();
                std::shared_ptr<Nodes::Node> index = parseBoolean();    // This is the index
                acceptIndentation();
                if (!expect(RIGHTSQUAREBRACKET))
                {
                    return nullNode;
                }
                return parseSquareBrackets(nodeFactory->CreateArrayGetNode(passable, currentToken, node, index));
            }
        }
        return node;
    }

    std::shared_ptr<Nodes::Node> Parser::parseValue()
    {
        acceptIndentation();
        if (!tokens.empty() && compilation)
        {
            if (Helpers::TypeDetector::isNumeric(currentToken->getContent()))
            {
                std::shared_ptr<Nodes::Node> node = nodeFactory->CreateNumberNode(passable, currentToken, currentToken->getContent());
                nextToken();
                acceptIndentation();
                return node;
            }
            else if (Helpers::TypeDetector::isWord(currentToken->getContent()))
            {
                std::string word = currentToken->getContent();
                acceptIndentation();
                std::shared_ptr<Tokens::Token> peak = peakToken();
                if (peak != nullptr && peakToken()->getType() == Types::LEFTPARENTHESIS)
                {
                    nextToken();
                    if (!expect(Types::LEFTPARENTHESIS))
                    {
                        return nullNode;
                    }
                    std::vector<std::shared_ptr<Nodes::Node>> arguments;
                    if (currentToken->getType() != Types::RIGHTPARENTHESIS) // Check for end of function parenthesis
                    {
                        do
                        {
                            acceptIndentation();
                            arguments.push_back(parseBoolean());
                        }
                        while (accept(Types::COMMA) && !accept(Types::RIGHTPARENTHESIS) && !tokens.empty());
                    }

                    if (!expect(Types::RIGHTPARENTHESIS))
                    {
                        arguments.clear();
                        return nullNode;
                    }
                    acceptIndentation();
                    return parseSquareBrackets(nodeFactory->CreateGetFuncNode(passable, currentToken, word, functions, arguments));
                }
                else if (peak != nullptr && peakToken()->getType() == Types::LEFTSQUAREBRACKET)
                {

                }
                else if (currentToken->getType() == Types::TEXT)
                {
                    nextToken();
                    return nodeFactory->CreateTextNode(passable, currentToken, word);
                }
                else if (peakToken() != nullptr && peakToken()->getType() == Types::INCREMENT)
                {
                    return nodeFactory->CreateIncrementNode(passable, currentToken, nodeFactory->CreateGetVarNode(passable, currentToken, word));
                }
                else if (peakToken() != nullptr && peakToken()->getType() == Types::DECREMENT)
                {
                    return nodeFactory->CreateDecrementNode(passable, currentToken, nodeFactory->CreateGetVarNode(passable, currentToken, word));
                }
                std::shared_ptr<Nodes::Node> var = nodeFactory->CreateGetVarNode(passable, currentToken, word);
                nextToken();
                return parseSquareBrackets(var);
            }
            errorMessage("", currentToken);
            nextToken();
        }
        return nullNode;
    }

    std::shared_ptr<Nodes::Node> Parser::parseFactor()
    {
        acceptIndentation();
        if (!tokens.empty() && compilation)
        {
            std::shared_ptr<Nodes::Node> value;
            if (currentToken->getType() == Types::LEFTPARENTHESIS)
            {
                nextToken();
                value = parseBoolean();
                if (!expect(Types::RIGHTPARENTHESIS))
                {
                    return nullNode;
                }
                return nodeFactory->CreateBracketNode(passable, currentToken, value);
            }
            else if (currentToken->getType() == Types::ADDITION)
            {
                nextToken();
                return parseFactor();
            }
            else if (currentToken->getType() == Types::SUBTRACTION)
            {
                nextToken();
                return nodeFactory->CreateUnaryMinusNode(passable, currentToken, parseFactor());
            }
            else if (currentToken->getType() == Types::NOT)
            {
                nextToken();
                return nodeFactory->CreateUnaryNotNode(passable, currentToken, parseFactor());
            }
            else if (currentToken->getType() == Types::BITWISECOMPLEMENT)
            {
                nextToken();
                return nodeFactory->CreateBitwiseComplementNode(passable, currentToken, parseFactor());
            }
            return parseValue();
        }
        return nullNode;
    }

    std::shared_ptr<Nodes::Node> Parser::parseTerm()
    {
        acceptIndentation();
        if (!tokens.empty() && compilation)
        {
            std::shared_ptr<Nodes::Node> node = parseFactor();
            acceptIndentation();
            Types::TokenType type = currentToken->getType();
            while (!tokens.empty() && (currentToken->getType() == Types::MULTIPLICATION ||
                   currentToken->getType() == Types::DIVISION ||
                   currentToken->getType() == Types::MOD))
            {
                nextToken();
                acceptIndentation();
                if (type == Types::MULTIPLICATION)
                {
                    node = nodeFactory->CreateMulNode(passable, currentToken, node, parseFactor());
                }
                else if (type == Types::DIVISION)
                {
                    node = nodeFactory->CreateDivNode(passable, currentToken, node, parseFactor());
                }
                else if (type == Types::MOD)
                {
                    node = nodeFactory->CreateModNode(passable, currentToken, node, parseFactor());
                }
                type = currentToken->getType();
            }
            return node;
        }
        return nullNode;
    }

    std::shared_ptr<Nodes::Node> Parser::parseExpression()
    {
        acceptIndentation();
        if (!tokens.empty() && compilation)
        {
            std::shared_ptr<Nodes::Node> node = parseTerm();
            acceptIndentation();
            Types::TokenType type = currentToken->getType();
            while (!tokens.empty() && (type == Types::ADDITION ||
                                       type == Types::SUBTRACTION))
            {
                nextToken();
                acceptIndentation();
                if (type == Types::ADDITION)
                {
                    node = nodeFactory->CreateAddNode(passable, currentToken, node, parseTerm());
                }
                else if (type == Types::SUBTRACTION)
                {
                    node = nodeFactory->CreateSubNode(passable, currentToken, node, parseTerm());
                }
                type = currentToken->getType();
            }
            return node;
        }
        return nullNode;
    }

    std::shared_ptr<Nodes::Node> Parser::parseBitwiseLeftRight()
    {
        acceptIndentation();
        if (!tokens.empty() && compilation)
        {
            std::shared_ptr<Nodes::Node> node = parseExpression();
            acceptIndentation();
            Types::TokenType type = currentToken->getType();
            while (!tokens.empty() && (type == Types::LEFTSHIFT ||
                                       type == Types::RIGHTSHIFT))
            {
                nextToken();
                acceptIndentation();
                if (type == Types::LEFTSHIFT)
                {
                    node = nodeFactory->CreateLeftShiftNode(passable, currentToken, node, parseExpression());
                }
                else if (type == Types::RIGHTSHIFT)
                {
                    node = nodeFactory->CreateRightShiftNode(passable, currentToken, node, parseExpression());
                }
                type = currentToken->getType();
            }
            return node;
        }
        return nullNode;
    }

    std::shared_ptr<Nodes::Node> Parser::parseEqualAndEqualNot()
    {
        acceptIndentation();
        if (!tokens.empty() && compilation)
        {
            std::shared_ptr<Nodes::Node> node = parseBitwiseLeftRight();
            if (node != nullptr)
            {
                Types::TokenType type = currentToken->getType();
                while (!tokens.empty() &&
                       (type == Types::IFEQUALS ||
                       type == Types::IFNOTEQUALS))
                {
                    if (type == Types::IFEQUALS)
                    {
                        nextToken();
                        std::shared_ptr<Nodes::Node> next = parseExpression();
                        node = nodeFactory->CreateIfEqualNode(passable, currentToken, node, next);
                    }
                    else if (type == Types::IFNOTEQUALS)
                    {
                        nextToken();
                        std::shared_ptr<Nodes::Node> next = parseExpression();
                        node = nodeFactory->CreateIfNotEqualNode(passable, currentToken, node, next);
                    }
                    type = currentToken->getType();
                }
                return node;
            }
        }
        return nullNode;
    }

    std::shared_ptr<Nodes::Node> Parser::parseLessThanAndLessThanOrEqual()
    {
        acceptIndentation();
        if (!tokens.empty() && compilation)
        {
            std::shared_ptr<Nodes::Node> node = parseEqualAndEqualNot();
            if (node != nullptr)
            {
                Types::TokenType type = currentToken->getType();
                while (!tokens.empty() &&
                       (type == Types::IFLESSTHAN ||
                       type == Types::IFLESSTHANOREQUAL))
                {
                    if (type == Types::IFLESSTHAN)
                    {
                        nextToken();
                        std::shared_ptr<Nodes::Node> next = parseExpression();
                        node = nodeFactory->CreateIfUnderNode(passable, currentToken, node, next);
                    }
                    else if (type == Types::IFLESSTHANOREQUAL)
                    {
                        nextToken();
                        std::shared_ptr<Nodes::Node> next = parseExpression();
                        node = nodeFactory->CreateIfUnderOrEqualNode(passable, currentToken, node, next);
                    }
                    type = currentToken->getType();
                }
                return node;
            }
        }
        return nullNode;
    }

    std::shared_ptr<Nodes::Node> Parser::parseGreaterThanAndGreaterThanOrEqual()
    {
        acceptIndentation();
        if (!tokens.empty() && compilation)
        {
            std::shared_ptr<Nodes::Node> node = parseLessThanAndLessThanOrEqual();
            if (node != nullptr)
            {
                Types::TokenType type = currentToken->getType();
                while (!tokens.empty() &&
                       (type == Types::IFGREATER ||
                       type == Types::IFGREATERTHANOREQUAL))
                {
                    if (type == Types::IFGREATER)
                    {
                        nextToken();
                        std::shared_ptr<Nodes::Node> next = parseExpression();
                        node = nodeFactory->CreateIfOverNode(passable, currentToken, node, next);
                    }
                    else if (type == Types::IFGREATERTHANOREQUAL)
                    {
                        nextToken();
                        std::shared_ptr<Nodes::Node> next = parseExpression();
                        node = nodeFactory->CreateIfOverOrEqualNode(passable, currentToken, node, next);
                    }
                    type = currentToken->getType();
                }
                return node;
            }
        }
        return nullNode;
    }

    std::shared_ptr<Nodes::Node> Parser::parseBitwiseAnd()
    {
        acceptIndentation();
        if (!tokens.empty() && compilation)
        {
            std::shared_ptr<Nodes::Node> node = parseGreaterThanAndGreaterThanOrEqual();
            Types::TokenType type = currentToken->getType();
            while (!tokens.empty() &&
                   (type == Types::BITWISEAND))
            {
                nextToken();
                std::shared_ptr<Nodes::Node> next = parseCondition();
                node = nodeFactory->CreateBitwiseAndNode(passable, currentToken, node, next);
                type = currentToken->getType();
            }
            return node;
        }
        return nullNode;
    }

    std::shared_ptr<Nodes::Node> Parser::parseBitwiseXOr()
    {
        acceptIndentation();
        if (!tokens.empty() && compilation)
        {
            std::shared_ptr<Nodes::Node> node = parseBitwiseAnd();
            Types::TokenType type = currentToken->getType();
            while (!tokens.empty() &&
                   (type == Types::BITWISEXOR))
            {
                nextToken();
                std::shared_ptr<Nodes::Node> next = parseCondition();
                node = nodeFactory->CreateBitwiseXORNode(passable, currentToken, node, next);
                type = currentToken->getType();
            }
            return node;
        }
        return nullNode;
    }

    std::shared_ptr<Nodes::Node> Parser::parseBitwiseOr()
    {
        acceptIndentation();
        if (!tokens.empty() && compilation)
        {
            std::shared_ptr<Nodes::Node> node = parseBitwiseXOr();
            Types::TokenType type = currentToken->getType();
            while (!tokens.empty() &&
                   (type == Types::BITWISEOR))
            {
                nextToken();
                std::shared_ptr<Nodes::Node> next = parseCondition();
                node = nodeFactory->CreateBitwiseOrNode(passable, currentToken, node, next);
                type = currentToken->getType();
            }
            return node;
        }
        return nullNode;
    }

    std::shared_ptr<Nodes::Node> Parser::parseAnd()
    {
        acceptIndentation();
        if (!tokens.empty() && compilation)
        {
            std::shared_ptr<Nodes::Node> node = parseBitwiseOr();
            Types::TokenType type = currentToken->getType();
            while (!tokens.empty() &&
                   (type == Types::AND))
            {
                nextToken();
                std::shared_ptr<Nodes::Node> next = parseCondition();
                node = nodeFactory->CreateIfAndNode(passable, currentToken, node, next);
                type = currentToken->getType();
            }
            return node;
        }
        return nullNode;
    }

    std::shared_ptr<Nodes::Node> Parser::parseOr()
    {
        acceptIndentation();
        if (!tokens.empty() && compilation)
        {
            std::shared_ptr<Nodes::Node> node = parseAnd();
            Types::TokenType type = currentToken->getType();
            while (!tokens.empty() &&
                   (type == Types::OR))
            {
                nextToken();
                std::shared_ptr<Nodes::Node> next = parseCondition();
                node = nodeFactory->CreateIfOrNode(passable, currentToken, node, next);
                type = currentToken->getType();
            }
            return node;
        }
        return nullNode;
    }

    std::shared_ptr<Nodes::Node> Parser::parseCondition()
    {
        return parseOr();
    }

    std::shared_ptr<Nodes::Node> Parser::parseBoolean()
    {
        return parseCondition();
    }

    std::shared_ptr<Nodes::Node> Parser::parseAssingment()
    {
        acceptIndentation();
        if (currentToken->getType() == Types::WORD)
        {
            acceptIndentation();
            std::string word = currentToken->getContent();
            if (!Helpers::TypeDetector::isWord(word))
            {
                compilation = false;
                return nullNode;
            }
            nextToken();
            acceptIndentation();
            Types::TokenType tokenType = currentToken->getType();
            acceptIndentation();
            if (accept(Types::INCREMENT))
            {
                std::shared_ptr<Nodes::Node> node = nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateIncrementNode(passable, currentToken, nodeFactory->CreateGetVarNode(passable, currentToken, word)));
                if (!expectSemicolon())
                {
                    return nullNode;
                }
                return nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateRunNode(passable, currentToken, (node), parseBlock()));
            }
            if (accept(Types::DECREMENT))
            {
                std::shared_ptr<Nodes::Node> node = nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateDecrementNode(passable, currentToken, nodeFactory->CreateGetVarNode(passable, currentToken, word)));
                if (!expectSemicolon())
                {
                    return nullNode;
                }
                return nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateRunNode(passable, currentToken, node, parseBlock()));
            }
            acceptIndentation();
            if (accept(Types::SEMICOLON))
            {
                acceptIndentation();
                acceptSemicolon();
                return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateSetVarNode(passable, currentToken, word, nullptr)), parseBlock());
            }

            if (tokenType != Types::EQUALS &&
                    tokenType != Types::ADDITIONEQUAL &&
                    tokenType != Types::SUBTRACTIONEQUAL &&
                    tokenType != Types::MULTIPLICATIONEQUAL &&
                    tokenType != Types::DIVISIONEQUAL)
            {
                // Unexpected token... report error here
                compilation = false;
                return nullNode;
            }
            nextToken();
            acceptIndentation();
            std::shared_ptr<Nodes::Node> expressionNode = parseBoolean();
            if (expressionNode == nullptr)
            {
                compilation = false;
                return nullNode;
            }
            acceptIndentation();
            if (!expect(Types::SEMICOLON))
            {
                return nullNode;
            }
            acceptIndentation();
            acceptSemicolon();
            std::shared_ptr<Nodes::Node> blockNode = parseBlock();

            if (tokenType == Types::EQUALS)
            {
                return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateSetVarNode(passable, currentToken, word, expressionNode)), blockNode);
            }
            else if (tokenType == Types::ADDITIONEQUAL)
            {
                std::shared_ptr<Nodes::Node> getNode = nodeFactory->CreateGetVarNode(passable, currentToken, word);
                std::shared_ptr<Nodes::Node> addNode = nodeFactory->CreateAddNode(passable, currentToken, getNode, expressionNode);
                return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateSetVarNode(passable, currentToken, word, addNode)), blockNode);
            }
            else if (tokenType == Types::SUBTRACTIONEQUAL)
            {
                std::shared_ptr<Nodes::Node> getNode = nodeFactory->CreateGetVarNode(passable, currentToken, word);
                std::shared_ptr<Nodes::Node> subNode = nodeFactory->CreateSubNode(passable, currentToken, getNode, expressionNode);
                return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateSetVarNode(passable, currentToken, word, subNode)), blockNode);
            }
            else if (tokenType == Types::MULTIPLICATIONEQUAL)
            {
                std::shared_ptr<Nodes::Node> getNode = nodeFactory->CreateGetVarNode(passable, currentToken, word);
                std::shared_ptr<Nodes::Node> mulNode = nodeFactory->CreateMulNode(passable, currentToken, getNode, expressionNode);
                return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateSetVarNode(passable, currentToken, word, mulNode)), blockNode);
            }
            else if (tokenType == Types::DIVISIONEQUAL)
            {
                std::shared_ptr<Nodes::Node> getNode = nodeFactory->CreateGetVarNode(passable, currentToken, word);
                std::shared_ptr<Nodes::Node> divNode = nodeFactory->CreateDivNode(passable, currentToken, getNode, expressionNode);
                return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateSetVarNode(passable, currentToken, word, divNode)), blockNode);
            }
        }
        return nullNode;
    }

    std::shared_ptr<Nodes::Node> Parser::parseDecloration()
    {
        acceptIndentation();
        if (accept("let"))
        {
            acceptIndentation();
            if (currentToken->getType() == Types::WORD)
            {
                acceptIndentation();
                std::string word = currentToken->getContent();
                if (!Helpers::TypeDetector::isWord(word))
                {
                    compilation = false;
                    return nullNode;
                }
                nextToken();
                acceptIndentation();
                Types::TokenType tokenType = currentToken->getType();
                acceptIndentation();
                if (accept(Types::SEMICOLON))
                {
                    acceptIndentation();
                    acceptSemicolon();
                    return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateAddVarNode(passable, currentToken, word, nullptr)), parseBlock());
                }
                if (tokenType != Types::EQUALS &&
                        tokenType != Types::ADDITIONEQUAL &&
                        tokenType != Types::SUBTRACTIONEQUAL &&
                        tokenType != Types::MULTIPLICATIONEQUAL &&
                        tokenType != Types::DIVISIONEQUAL)
                {
                    // Unexpected token... report error here
                    compilation = false;
                    return nullNode;
                }
                nextToken();
                acceptIndentation();
                std::shared_ptr<Nodes::Node> expressionNode = parseBoolean();
                if (expressionNode == nullptr)
                {
                    compilation = false;
                    return nullNode;
                }
                acceptIndentation();
                if (!expectSemicolon())
                {
                    return nullNode;
                }
                std::shared_ptr<Nodes::Node> blockNode = parseBlock();

                if (tokenType == Types::EQUALS)
                {
                    return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateAddVarNode(passable, currentToken, word, expressionNode)), blockNode);
                }
                else if (tokenType ==  Types::ADDITIONEQUAL)
                {
                    std::shared_ptr<Nodes::Node> getNode = nodeFactory->CreateGetVarNode(passable, currentToken, word);
                    std::shared_ptr<Nodes::Node> addNode = nodeFactory->CreateAddNode(passable, currentToken, getNode, expressionNode);
                    return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateAddVarNode(passable, currentToken, word, addNode)), blockNode);
                }
                else if (tokenType ==  Types::SUBTRACTIONEQUAL)
                {
                    std::shared_ptr<Nodes::Node> getNode = nodeFactory->CreateGetVarNode(passable, currentToken, word);
                    std::shared_ptr<Nodes::Node> subNode = nodeFactory->CreateSubNode(passable, currentToken, getNode, expressionNode);
                    return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateAddVarNode(passable, currentToken, word, subNode)), blockNode);
                }
                else if (tokenType ==  Types::MULTIPLICATIONEQUAL)
                {
                    std::shared_ptr<Nodes::Node> getNode = nodeFactory->CreateGetVarNode(passable, currentToken, word);
                    std::shared_ptr<Nodes::Node> mulNode = nodeFactory->CreateMulNode(passable, currentToken, getNode, expressionNode);
                    return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateAddVarNode(passable, currentToken, word, mulNode)), blockNode);
                }
                else if (tokenType ==  Types::DIVISIONEQUAL)
                {
                    std::shared_ptr<Nodes::Node> getNode = nodeFactory->CreateGetVarNode(passable, currentToken, word);
                    std::shared_ptr<Nodes::Node> divNode = nodeFactory->CreateDivNode(passable, currentToken, getNode, expressionNode);
                    return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateAddVarNode(passable, currentToken, word, divNode)), blockNode);
                }
            }
            return nullNode;
        }
        else if (accept("const"))
        {
            acceptIndentation();
            if (currentToken->getType() == Types::WORD)
            {
                acceptIndentation();
                std::string word = currentToken->getContent();
                if (!Helpers::TypeDetector::isWord(word))
                {
                    compilation = false;
                    return nullNode;
                }
                nextToken();
                acceptIndentation();
                Types::TokenType tokenType = currentToken->getType();
                acceptIndentation();
                if (accept(Types::SEMICOLON))
                {
                    acceptIndentation();
                    acceptSemicolon();
                    return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateAddVarNode(passable, currentToken, word, nullptr)), parseBlock());
                }
                if (tokenType != Types::EQUALS &&
                        tokenType != Types::ADDITIONEQUAL &&
                        tokenType != Types::SUBTRACTIONEQUAL &&
                        tokenType != Types::MULTIPLICATIONEQUAL &&
                        tokenType != Types::DIVISIONEQUAL)
                {
                    // Unexpected token... report error here
                    compilation = false;
                    return nullNode;
                }
                nextToken();
                acceptIndentation();
                std::shared_ptr<Nodes::Node> expressionNode = parseBoolean();
                if (expressionNode == nullptr)
                {
                    compilation = false;
                    return nullNode;
                }
                acceptIndentation();
                if (!expectSemicolon())
                {
                    return nullNode;
                }
                std::shared_ptr<Nodes::Node> blockNode = parseBlock();

                if (tokenType == Types::EQUALS)
                {
                    return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateAddConstNode(passable, currentToken, word, expressionNode)), blockNode);
                }
                else if (tokenType ==  Types::ADDITIONEQUAL)
                {
                    std::shared_ptr<Nodes::Node> getNode = nodeFactory->CreateGetVarNode(passable, currentToken, word);
                    std::shared_ptr<Nodes::Node> addNode = nodeFactory->CreateAddNode(passable, currentToken, getNode, expressionNode);
                    return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateAddConstNode(passable, currentToken, word, addNode)), blockNode);
                }
                else if (tokenType ==  Types::SUBTRACTIONEQUAL)
                {
                    std::shared_ptr<Nodes::Node> getNode = nodeFactory->CreateGetVarNode(passable, currentToken, word);
                    std::shared_ptr<Nodes::Node> subNode = nodeFactory->CreateSubNode(passable, currentToken, getNode, expressionNode);
                    return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateAddConstNode(passable, currentToken, word, subNode)), blockNode);
                }
                else if (tokenType ==  Types::MULTIPLICATIONEQUAL)
                {
                    std::shared_ptr<Nodes::Node> getNode = nodeFactory->CreateGetVarNode(passable, currentToken, word);
                    std::shared_ptr<Nodes::Node> mulNode = nodeFactory->CreateMulNode(passable, currentToken, getNode, expressionNode);
                    return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateAddConstNode(passable, currentToken, word, mulNode)), blockNode);
                }
                else if (tokenType ==  Types::DIVISIONEQUAL)
                {
                    std::shared_ptr<Nodes::Node> getNode = nodeFactory->CreateGetVarNode(passable, currentToken, word);
                    std::shared_ptr<Nodes::Node> divNode = nodeFactory->CreateDivNode(passable, currentToken, getNode, expressionNode);
                    return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateAddConstNode(passable, currentToken, word, divNode)), blockNode);
                }
            }
            return nullNode;
        }
        return nullNode;
    }

    std::shared_ptr<Nodes::Node> Parser::parseElseStatement()
    {
        std::shared_ptr<Nodes::Node> returnNode;
        std::shared_ptr<Nodes::Node> conditionNode;
        std::shared_ptr<Nodes::Node> statementNode;
        std::shared_ptr<Nodes::Node> elseNode;
        acceptIndentation();
        if (accept("else"))
        {
            acceptIndentation();
            if (accept("if"))
            {
                acceptIndentation();
                if (!expect(Types::LEFTPARENTHESIS))
                {
                    return nullNode;
                }
                acceptIndentation();
                conditionNode = parseBoolean();
                acceptIndentation();
                if (!expect(Types::RIGHTPARENTHESIS))
                {
                    return nullNode;
                }
                acceptIndentation();
                if (!expect(Types::LEFTBRACKET))
                {
                    return nullNode;
                }
                acceptIndentation();
                statementNode = parseBlock();
                if (!expect(Types::RIGHTBRACKET))
                {
                    return nullNode;
                }
                acceptIndentation();

                elseNode = parseElseStatement();
                acceptIndentation();
            }
            else
            {
                acceptIndentation();
                if (!expect(Types::LEFTBRACKET))
                {
                    return nullNode;
                }
                acceptIndentation();
                std::shared_ptr<Nodes::Node> node = parseBlock();
                if (!expect(Types::RIGHTBRACKET))
                {
                    return nullNode;
                }
                acceptIndentation();
                return node;
            }
            returnNode = nodeFactory->CreateIfNode(passable, currentToken, conditionNode, statementNode, elseNode);
        }
        return returnNode;
    }

    std::shared_ptr<Nodes::Node> Parser::parseFunction()
    {
        acceptIndentation();
        if (!tokens.empty() && compilation)
        {
            if (Helpers::TypeDetector::isWord(this->currentToken->getContent()) && peakToken() != nullptr && peakToken()->getType() == Types::LEFTPARENTHESIS)
            {
                std::string word = this->currentToken->getContent();
                if (functions->get(word) == nullptr)
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->functionNotDeclared(currentToken, word));
                    compilation = false;
                    return nullNode;
                }
                acceptIndentation();
                nextToken();
                acceptIndentation();
                if (!expect(Types::LEFTPARENTHESIS))
                {
                    return nullNode;
                }
                std::vector<std::shared_ptr<Nodes::Node>> arguments;
                if (currentToken->getType() != Types::RIGHTPARENTHESIS)
                {
                    do
                    {
                        acceptIndentation();
                        arguments.push_back(parseBoolean());
                        acceptIndentation();
                    }
                    while (accept(Types::COMMA) && !accept(Types::RIGHTPARENTHESIS) && !tokens.empty());
                }
                if (!expect(Types::RIGHTPARENTHESIS))
                {
                    return nullNode;
                }
                if (!expectSemicolon())
                {
                    return nullNode;
                }
                std::shared_ptr<Nodes::Node> blockNode = parseBlock();
                std::shared_ptr<Nodes::Node> functions = nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateGetFuncNode(passable, currentToken, word, this->functions, arguments));
                return nodeFactory->CreateRunNode(passable, currentToken, (functions), blockNode);
            }
        }
        return parseAssingment();
    }

    std::shared_ptr<Nodes::Node> Parser::parseStatement()
    {
        acceptIndentation();
        if (!tokens.empty() && compilation)
        {
            acceptIndentation();
            if (accept("if"))
            {
                acceptIndentation();
                if (!expect(Types::LEFTPARENTHESIS))
                {
                    return nullNode;
                }
                acceptIndentation();
                std::shared_ptr<Nodes::Node> conditionNode = parseBoolean();
                acceptIndentation();
                if (!expect(Types::RIGHTPARENTHESIS))
                {
                    return nullNode;
                }
                acceptIndentation();
                if (!expect(Types::LEFTBRACKET))
                {
                    return nullNode;
                }
                acceptIndentation();
                std::shared_ptr<Nodes::Node> statementNode = parseBlock();
                if (!expect(Types::RIGHTBRACKET))
                {
                    return nullNode;
                }
                acceptIndentation();

                std::shared_ptr<Nodes::Node> elseNode = parseElseStatement();

                acceptIndentation();
                std::shared_ptr<Nodes::Node> next = parseBlock();
                std::shared_ptr<Nodes::Node> returnNode = nodeFactory->CreateIfNode(passable, currentToken, conditionNode, statementNode, elseNode);
                return nodeFactory->CreateRunNode(passable, this->currentToken, returnNode, next);
            }
            else if (accept("while"))
            {
                acceptIndentation();
                expect(Types::LEFTPARENTHESIS);
                std::shared_ptr<Nodes::Node> conditionNode = parseBoolean();
                acceptIndentation();
                expect(Types::RIGHTPARENTHESIS);
                acceptIndentation();
                expect(Types::LEFTBRACKET);
                acceptIndentation();
                std::shared_ptr<Nodes::Node> statementNode = parseBlock();
                acceptIndentation();
                expect(Types::RIGHTBRACKET);
                acceptIndentation();
                std::shared_ptr<Nodes::Node> next = parseBlock();
                return nodeFactory->CreateWhileNode(passable, currentToken, conditionNode, statementNode, next);
            }
            return parseFunction();
        }
        return nullNode;
    }

    std::shared_ptr<Nodes::Node> Parser::parseBlock()
    {
        acceptIndentation();
        if (!tokens.empty() && compilation)
        {
            if (accept("return"))
            {
                acceptIndentation();
                std::shared_ptr<Nodes::Node> returnNode = nodeFactory->CreateSetReturnNode(passable, parseBoolean());
                if (!expectSemicolon())
                {
                    return nullNode;
                }

                std::shared_ptr<Nodes::Node> blockNode = parseBlock();

                return nodeFactory->CreateRunNode(passable,
                                                  currentToken,
                                                  nodeFactory->CreateSemicolonNode(passable, returnNode),
                                                  blockNode
                                                  );
            }

            std::shared_ptr<Nodes::Node> dec = parseDecloration();
            if (dec != nullptr)
            {
                return dec;
            }
            else if (accept("function"))
            {
                acceptIndentation();
                std::string word = currentToken->getContent();
                nextToken();
                if (!Helpers::TypeDetector::isWord(word) || functions->exists(word))
                {
                    compilation = false;
                    return nullNode;
                }

                // Here we add a hint that the function exists
                functions->addFunction(word);
                customFunctions->addFunction(word);
                acceptIndentation();
                if (!expect(Types::LEFTPARENTHESIS))
                {
                    functions->removeFunction(word);
                    customFunctions->removeFunction(word);
                    return nullNode;
                }
                acceptIndentation();

                std::vector<std::string> arguments;
                if (currentToken->getType() != Types::RIGHTPARENTHESIS)
                {
                    do
                    {
                        acceptIndentation();
                        arguments.push_back(currentToken->getContent());
                        nextToken();
                    }
                    while (accept(Types::COMMA) && !accept(Types::RIGHTPARENTHESIS) && !tokens.empty());
                }
                acceptIndentation();

                if (!expect(Types::RIGHTPARENTHESIS))
                {
                    functions->removeFunction(word);
                    customFunctions->removeFunction(word);
                    arguments.clear();
                    return nullNode;
                }
                acceptIndentation();

                if (!expect(Types::LEFTBRACKET))
                {
                    functions->removeFunction(word);
                    customFunctions->removeFunction(word);
                    return false;
                }
                acceptIndentation();

                std::shared_ptr<Nodes::Node> blockNode = parseBlock();

                acceptIndentation();
                if (!expect(Types::RIGHTBRACKET))
                {
                    functions->removeFunction(word);
                    customFunctions->removeFunction(word);
                    return false;
                }
                std::shared_ptr<Functions::Function> newFunction = std::make_shared<Functions::CustomFunction>(passable, currentToken, word, arguments, blockNode);
                functions->setFunction(word, newFunction);
                customFunctions->setFunction(word, newFunction);
                return parseBlock();
            }
            return parseStatement();
        }
        return nullNode;
    }

    std::shared_ptr<Nodes::Node> Parser::parse()
    {
        if (!tokens.empty() && compilation)
        {
            nextToken();
            return parseBlock();
        }
        return nullNode;
    }

    std::string Parser::toString()
    {
        std::string output;
        if (!tokens.empty() && compilation)
        {
            std::shared_ptr<Nodes::Node> node = parse();
            output.append(customFunctions->toString());
            if (node != nullptr)
            {
                output.append(node->toString());
            }
        }
        return output;
    }

    bool Parser::execute()
    {
        std::shared_ptr<Variables::Scope> globalScope = std::make_shared<Variables::Scope>(passable);
        if (!tokens.empty() && compilation)
        {
            std::shared_ptr<Nodes::Node> done = parse();
            if (done != nullptr && compilation)
            {
                std::shared_ptr<Variables::Variable> output = done->execute(globalScope, globalScope);
                if (output != nullptr)
                {
                    std::cout << output->toString() << std::endl;
                }
                if (passable->getErrorManager()->count() > 0)
                {
                    std::vector<std::shared_ptr<Error>> errors = passable->getErrorManager()->get();
                    std::deque<std::shared_ptr<StackTrace>> stackTraces = passable->getStackTraceManager()->get();
                    for (std::vector<std::shared_ptr<Error>>::iterator it = errors.begin(); it != errors.end(); ++it)
                    {
                        std::cout << (*it)->getMessage() << std::endl;
                    }
                    for (std::deque<std::shared_ptr<StackTrace>>::iterator it = stackTraces.begin(); it != stackTraces.end(); ++it)
                    {
                        std::cout << (*it)->toString() << std::endl;
                    }
                }
                return true;
            }
        }
        return false;
    }
}
