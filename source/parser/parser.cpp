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

Parser::Parser(std::vector<std::shared_ptr<Token>> tokens,
               std::shared_ptr<NodeFactory> nodeFactory)
{
    this->nodeFactory = nodeFactory;
    this->passable = std::make_shared<Passable>();
    this->passable->errors = std::make_shared<Errors>();
    this->passable->errorFactory = std::make_shared<ErrorFactory>();
    this->compilation = true;
    this->tokens = tokens;
    this->functions = std::move(std::make_shared<Functions>(passable));
    functions->init();
    customFunctions = std::move(std::make_shared<Functions>(passable));
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
        it++;
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

std::shared_ptr<Token> Parser::peakToken()
{
    std::shared_ptr<Token> output;
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

bool Parser::accept(TokenType tokenType)
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

bool Parser::expect(TokenType tokenType)
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
    if (!expect(SEMICOLON))
    {
      return false;
    }
    acceptIndentation();
    acceptSemicolon();
    return true;
}

void Parser::errorMessage(std::string errorMsg, std::shared_ptr<Token> currentToken)
{
    passable->errors->add(passable->errorFactory->syntaxError(currentToken, errorMsg));
}

std::shared_ptr<Node> Parser::value()
{
    acceptIndentation();
    if (!tokens.empty() && compilation)
    {
        if (TypeDetector::isNumeric(currentToken->getContent()))
        {
            std::shared_ptr<Node> node = nodeFactory->CreateNumberNode(passable, currentToken, currentToken->getContent());
            nextToken();
            acceptIndentation();
            return node;
        }
        else if (TypeDetector::isWord(currentToken->getContent()))
        {
            std::string word = currentToken->getContent();
            acceptIndentation();
            std::shared_ptr<Token> peak = peakToken();
            if (peak != nullptr && peakToken()->getType() == LEFTPARENTHESIS)
            {
                nextToken();
                if (!expect(LEFTPARENTHESIS))
                {
                    return null;
                }
                std::vector<std::shared_ptr<Node>> arguments;
                if (currentToken->getType() != RIGHTPARENTHESIS) // Check for end of function parenthesis
                {
                    do
                    {
                        acceptIndentation();
                        arguments.push_back(boolean());
                    }
                    while (accept(COMMA) && !accept(RIGHTPARENTHESIS) && !tokens.empty());
                }

                if (!expect(RIGHTPARENTHESIS))
                {
                    arguments.clear();
                    return null;
                }
                acceptIndentation();
                return nodeFactory->CreateGetFuncNode(passable, currentToken, word, functions, arguments);
            }
            else if (currentToken->getType() == TEXT)
            {
                nextToken();
                return nodeFactory->CreateTextNode(passable, currentToken, word);
            }

            std::shared_ptr<Node> var = nodeFactory->CreateGetVarNode(passable, currentToken, word);
            nextToken();
            return var;
        }
        errorMessage("", currentToken);
        nextToken();
    }
    return null;
}

std::shared_ptr<Node> Parser::factor()
{
    acceptIndentation();
    if (!tokens.empty() && compilation)
    {
        std::shared_ptr<Node> value;
        if (currentToken->getType() == LEFTPARENTHESIS)
        {
            nextToken();
            value = boolean();
            if (!expect(RIGHTPARENTHESIS))
            {
                return null;
            }
            return nodeFactory->CreateBracketNode(passable, currentToken, value);
        }
        else if (currentToken->getType() == ADDITION)
        {
            nextToken();
            return factor();
        }
        else if (currentToken->getType() == SUBTRACTION)
        {
            nextToken();
            return nodeFactory->CreateUnaryMinusNode(passable, currentToken, factor());
        }
        else if (currentToken->getType() == NOT)
        {
            nextToken();
            return nodeFactory->CreateUnaryNotNode(passable, currentToken, factor());
        }
        else if (currentToken->getType() == BITWISECOMPLEMENT)
        {
            nextToken();
            return nodeFactory->CreateBitwiseComplementNode(passable, currentToken, factor());
        }
        return this->value();
    }
    return null;
}

std::shared_ptr<Node> Parser::term()
{
    acceptIndentation();
    if (!tokens.empty() && compilation)
    {
        std::shared_ptr<Node> node = factor();
        acceptIndentation();
        TokenType type = currentToken->getType();
        while (!tokens.empty() && (currentToken->getType() == MULTIPLICATION ||
               currentToken->getType() == DIVISION ||
               currentToken->getType() == MOD))
        {
            nextToken();
            acceptIndentation();
            if (type == MULTIPLICATION)
            {
                node = nodeFactory->CreateMulNode(passable, currentToken, node, factor());
            }
            else if (type == DIVISION)
            {
                node = nodeFactory->CreateDivNode(passable, currentToken, node, factor());
            }
            else if (type == MOD)
            {
                node = nodeFactory->CreateModNode(passable, currentToken, node, factor());
            }
            type = currentToken->getType();
        }
        return node;
    }
    return null;
}

std::shared_ptr<Node> Parser::expression()
{
    acceptIndentation();
    if (!tokens.empty() && compilation)
    {
        std::shared_ptr<Node> node = term();
        acceptIndentation();
        TokenType type = currentToken->getType();
        while (!tokens.empty() && (type == ADDITION ||
                                   type == SUBTRACTION ||
                                   type == LEFTSHIFT ||
                                   type == RIGHTSHIFT))
        {
            nextToken();
            acceptIndentation();
            if (type == ADDITION)
            {
                node = nodeFactory->CreateAddNode(passable, currentToken, node, term());
            }
            else if (type == SUBTRACTION)
            {
                node = nodeFactory->CreateSubNode(passable, currentToken, node, term());
            }
            else if (type == LEFTSHIFT)
            {
                node = nodeFactory->CreateLeftShiftNode(passable, currentToken, node, term());
            }
            else if (type == RIGHTSHIFT)
            {
                node = nodeFactory->CreateRightShiftNode(passable, currentToken, node, term());
            }
            type = currentToken->getType();
        }
        return node;
    }
    return null;
}

std::shared_ptr<Node> Parser::condition()
{
    acceptIndentation();
    if (!tokens.empty() && compilation)
    {
        std::shared_ptr<Node> node = expression();
        if (node != nullptr)
        {
            TokenType type = currentToken->getType();
            while (!tokens.empty() &&
                   (type == IFEQUALS ||
                   type == IFNOTEQUALS ||
                   type == IFLESSTHAN ||
                   type == IFLESSTHANOREQUAL ||
                   type == IFGREATER ||
                   type == IFGREATERTHANOREQUAL))
            {
                if (type == IFEQUALS)
                {
                    nextToken();
                    std::shared_ptr<Node> next = expression();
                    node = nodeFactory->CreateIfEqualNode(passable, currentToken, node, next);
                }
                else if (type == IFNOTEQUALS)
                {
                    nextToken();
                    std::shared_ptr<Node> next = expression();
                    node = nodeFactory->CreateIfNotEqualNode(passable, currentToken, node, next);
                }
                else if (type == IFLESSTHAN)
                {
                    nextToken();
                    std::shared_ptr<Node> next = expression();
                    node = nodeFactory->CreateIfUnderNode(passable, currentToken, node, next);
                }
                else if (type == IFLESSTHANOREQUAL)
                {
                    nextToken();
                    std::shared_ptr<Node> next = expression();
                    node = nodeFactory->CreateIfUnderOrEqualNode(passable, currentToken, node, next);
                }
                else if (type == IFGREATER)
                {
                    nextToken();
                    std::shared_ptr<Node> next = expression();
                    node = nodeFactory->CreateIfOverNode(passable, currentToken, node, next);
                }
                else if (type == IFGREATERTHANOREQUAL)
                {
                    nextToken();
                    std::shared_ptr<Node> next = expression();
                    node = nodeFactory->CreateIfOverOrEqualNode(passable, currentToken, node, next);
                }
                type = currentToken->getType();
            }
            return node;
        }
    }
    return null;
}

std::shared_ptr<Node> Parser::boolean()
{
    acceptIndentation();
    if (!tokens.empty() && compilation)
    {
        std::shared_ptr<Node> node = condition();
        TokenType type = currentToken->getType();
        while (!tokens.empty() &&
               (type == AND ||
               type == OR ||
               type == BITWISEAND ||
               type == BITWISEOR ||
               type == BITWISEXOR))
        {
            if (type == AND)
            {
                nextToken();
                std::shared_ptr<Node> next = condition();
                node = nodeFactory->CreateIfAndNode(passable, currentToken, node, next);
            }
            else if (type == OR)
            {
                nextToken();
                std::shared_ptr<Node> next = condition();
                node = nodeFactory->CreateIfOrNode(passable, currentToken, node, next);
            }
            else if (type == BITWISEAND)
            {
                nextToken();
                std::shared_ptr<Node> next = condition();
                node = nodeFactory->CreateBitwiseAndNode(passable, currentToken, node, next);
            }
            else if (type == BITWISEOR)
            {
                nextToken();
                std::shared_ptr<Node> next = condition();
                node = nodeFactory->CreateBitwiseOrNode(passable, currentToken, node, next);
            }
            else if (type == BITWISEXOR)
            {
                nextToken();
                std::shared_ptr<Node> next = condition();
                node = nodeFactory->CreateBitwiseXORNode(passable, currentToken, node, next);
            }
            type = currentToken->getType();
        }
        return node;
    }
    return null;
}

std::shared_ptr<Node> Parser::assingment()
{
    acceptIndentation();
    if (currentToken->getType() == WORD)
    {
        acceptIndentation();
        std::string word = currentToken->getContent();
        if (!TypeDetector::isWord(word))
        {
            compilation = false;
            return null;
        }
        nextToken();
        acceptIndentation();
        TokenType tokenType = currentToken->getType();
        acceptIndentation();
        if (accept(INCREMENT))
        {
            std::shared_ptr<Node> node = nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateIncrementNode(passable, currentToken, nodeFactory->CreateGetVarNode(passable, currentToken, word)));
            if (!expectSemicolon())
            {
                return null;
            }
            return nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateRunNode(passable, currentToken, (node), block()));
        }
        if (accept(DECREMENT))
        {
            std::shared_ptr<Node> node = nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateDecrementNode(passable, currentToken, nodeFactory->CreateGetVarNode(passable, currentToken, word)));
            if (!expectSemicolon())
            {
                return null;
            }
            return nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateRunNode(passable, currentToken, node, block()));
        }
        acceptIndentation();
        if (accept(SEMICOLON))
        {
            acceptIndentation();
            acceptSemicolon();
            return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateSetVarNode(passable, currentToken, word, nullptr)), block());
        }

        if (tokenType != EQUALS &&
                tokenType != ADDITIONEQUAL &&
                tokenType != SUBTRACTIONEQUAL &&
                tokenType != MULTIPLICATIONEQUAL &&
                tokenType != DIVISIONEQUAL)
        {
            // Unexpected token... report error here
            compilation = false;
            return null;
        }
        nextToken();
        acceptIndentation();
        std::shared_ptr<Node> expressionNode = boolean();
        if (expressionNode == nullptr)
        {
            compilation = false;
            return null;
        }
        acceptIndentation();
        if (!expect(SEMICOLON))
        {
            return null;
        }
        acceptIndentation();
        acceptSemicolon();
        std::shared_ptr<Node> blockNode = block();

        if (tokenType == EQUALS)
        {
            return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateSetVarNode(passable, currentToken, word, expressionNode)), blockNode);
        }
        else if (tokenType == ADDITIONEQUAL)
        {
            std::shared_ptr<Node> getNode = nodeFactory->CreateGetVarNode(passable, currentToken, word);
            std::shared_ptr<Node> addNode = nodeFactory->CreateAddNode(passable, currentToken, getNode, expressionNode);
            return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateSetVarNode(passable, currentToken, word, addNode)), blockNode);
        }
        else if (tokenType == SUBTRACTIONEQUAL)
        {
            std::shared_ptr<Node> getNode = nodeFactory->CreateGetVarNode(passable, currentToken, word);
            std::shared_ptr<Node> subNode = nodeFactory->CreateSubNode(passable, currentToken, getNode, expressionNode);
            return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateSetVarNode(passable, currentToken, word, subNode)), blockNode);
        }
        else if (tokenType == MULTIPLICATIONEQUAL)
        {
            std::shared_ptr<Node> getNode = nodeFactory->CreateGetVarNode(passable, currentToken, word);
            std::shared_ptr<Node> mulNode = nodeFactory->CreateMulNode(passable, currentToken, getNode, expressionNode);
            return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateSetVarNode(passable, currentToken, word, mulNode)), blockNode);
        }
        else if (tokenType == DIVISIONEQUAL)
        {
            std::shared_ptr<Node> getNode = nodeFactory->CreateGetVarNode(passable, currentToken, word);
            std::shared_ptr<Node> divNode = nodeFactory->CreateDivNode(passable, currentToken, getNode, expressionNode);
            return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateSetVarNode(passable, currentToken, word, divNode)), blockNode);
        }
    }
    return null;
}

std::shared_ptr<Node> Parser::decloration()
{
    acceptIndentation();
    if (accept("let"))
    {
        acceptIndentation();
        if (currentToken->getType() == WORD)
        {
            acceptIndentation();
            std::string word = currentToken->getContent();
            if (!TypeDetector::isWord(word))
            {
                compilation = false;
                return null;
            }
            nextToken();
            acceptIndentation();
            TokenType tokenType = currentToken->getType();
            acceptIndentation();
            if (accept(SEMICOLON))
            {
                acceptIndentation();
                acceptSemicolon();
                return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateAddVarNode(passable, currentToken, word, nullptr)), block());
            }
            if (tokenType != EQUALS &&
                    tokenType != ADDITIONEQUAL &&
                    tokenType != SUBTRACTIONEQUAL &&
                    tokenType != MULTIPLICATIONEQUAL &&
                    tokenType != DIVISIONEQUAL)
            {
                // Unexpected token... report error here
                compilation = false;
                return null;
            }
            nextToken();
            acceptIndentation();
            std::shared_ptr<Node> expressionNode = boolean();
            if (expressionNode == nullptr)
            {
                compilation = false;
                return null;
            }
            acceptIndentation();
            if (!expectSemicolon())
            {
                return null;
            }
            std::shared_ptr<Node> blockNode = block();

            if (tokenType == EQUALS)
            {
                return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateAddVarNode(passable, currentToken, word, expressionNode)), blockNode);
            }
            else if (tokenType == ADDITIONEQUAL)
            {
                std::shared_ptr<Node> getNode = nodeFactory->CreateGetVarNode(passable, currentToken, word);
                std::shared_ptr<Node> addNode = nodeFactory->CreateAddNode(passable, currentToken, getNode, expressionNode);
                return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateAddVarNode(passable, currentToken, word, addNode)), blockNode);
            }
            else if (tokenType == SUBTRACTIONEQUAL)
            {
                std::shared_ptr<Node> getNode = nodeFactory->CreateGetVarNode(passable, currentToken, word);
                std::shared_ptr<Node> subNode = nodeFactory->CreateSubNode(passable, currentToken, getNode, expressionNode);
                return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateAddVarNode(passable, currentToken, word, subNode)), blockNode);
            }
            else if (tokenType == MULTIPLICATIONEQUAL)
            {
                std::shared_ptr<Node> getNode = nodeFactory->CreateGetVarNode(passable, currentToken, word);
                std::shared_ptr<Node> mulNode = nodeFactory->CreateMulNode(passable, currentToken, getNode, expressionNode);
                return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateAddVarNode(passable, currentToken, word, mulNode)), blockNode);
            }
            else if (tokenType == DIVISIONEQUAL)
            {
                std::shared_ptr<Node> getNode = nodeFactory->CreateGetVarNode(passable, currentToken, word);
                std::shared_ptr<Node> divNode = nodeFactory->CreateDivNode(passable, currentToken, getNode, expressionNode);
                return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateAddVarNode(passable, currentToken, word, divNode)), blockNode);
            }
        }
        return null;
    }
    else if (accept("const"))
    {
        acceptIndentation();
        if (currentToken->getType() == WORD)
        {
            acceptIndentation();
            std::string word = currentToken->getContent();
            if (!TypeDetector::isWord(word))
            {
                compilation = false;
                return null;
            }
            nextToken();
            acceptIndentation();
            TokenType tokenType = currentToken->getType();
            acceptIndentation();
            if (accept(SEMICOLON))
            {
                acceptIndentation();
                acceptSemicolon();
                return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateAddVarNode(passable, currentToken, word, nullptr)), block());
            }
            if (tokenType != EQUALS &&
                    tokenType != ADDITIONEQUAL &&
                    tokenType != SUBTRACTIONEQUAL &&
                    tokenType != MULTIPLICATIONEQUAL &&
                    tokenType != DIVISIONEQUAL)
            {
                // Unexpected token... report error here
                compilation = false;
                return null;
            }
            nextToken();
            acceptIndentation();
            std::shared_ptr<Node> expressionNode = boolean();
            if (expressionNode == nullptr)
            {
                compilation = false;
                return null;
            }
            acceptIndentation();
            if (!expectSemicolon())
            {
                return null;
            }
            std::shared_ptr<Node> blockNode = block();

            if (tokenType == EQUALS)
            {
                return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateAddConstNode(passable, currentToken, word, expressionNode)), blockNode);
            }
            else if (tokenType == ADDITIONEQUAL)
            {
                std::shared_ptr<Node> getNode = nodeFactory->CreateGetVarNode(passable, currentToken, word);
                std::shared_ptr<Node> addNode = nodeFactory->CreateAddNode(passable, currentToken, getNode, expressionNode);
                return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateAddConstNode(passable, currentToken, word, addNode)), blockNode);
            }
            else if (tokenType == SUBTRACTIONEQUAL)
            {
                std::shared_ptr<Node> getNode = nodeFactory->CreateGetVarNode(passable, currentToken, word);
                std::shared_ptr<Node> subNode = nodeFactory->CreateSubNode(passable, currentToken, getNode, expressionNode);
                return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateAddConstNode(passable, currentToken, word, subNode)), blockNode);
            }
            else if (tokenType == MULTIPLICATIONEQUAL)
            {
                std::shared_ptr<Node> getNode = nodeFactory->CreateGetVarNode(passable, currentToken, word);
                std::shared_ptr<Node> mulNode = nodeFactory->CreateMulNode(passable, currentToken, getNode, expressionNode);
                return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateAddConstNode(passable, currentToken, word, mulNode)), blockNode);
            }
            else if (tokenType == DIVISIONEQUAL)
            {
                std::shared_ptr<Node> getNode = nodeFactory->CreateGetVarNode(passable, currentToken, word);
                std::shared_ptr<Node> divNode = nodeFactory->CreateDivNode(passable, currentToken, getNode, expressionNode);
                return nodeFactory->CreateRunNode(passable, currentToken, nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateAddConstNode(passable, currentToken, word, divNode)), blockNode);
            }
        }
        return null;
    }
    return null;
}

std::shared_ptr<Node> Parser::elseStatement()
{
    std::shared_ptr<Node> returnNode = null;
    std::shared_ptr<Node> conditionNode = null;
    std::shared_ptr<Node> statementNode = null;
    std::shared_ptr<Node> elseNode = null;
    acceptIndentation();
    if (accept("else"))
    {
        acceptIndentation();
        if (accept("if"))
        {
            acceptIndentation();
            if (!expect(LEFTPARENTHESIS))
            {
                return null;
            }
            acceptIndentation();
            conditionNode = boolean();
            acceptIndentation();
            if (!expect(RIGHTPARENTHESIS))
            {
                return null;
            }
            acceptIndentation();
            if (!expect(LEFTBRACKET))
            {
                return null;
            }
            acceptIndentation();
            statementNode = block();
            if (!expect(RIGHTBRACKET))
            {
                return null;
            }
            acceptIndentation();

            elseNode = elseStatement();
            acceptIndentation();
        }
        else
        {
            acceptIndentation();
            if (!expect(LEFTBRACKET))
            {
                return null;
            }
            acceptIndentation();
            std::shared_ptr<Node> node = block();
            if (!expect(RIGHTBRACKET))
            {
                return null;
            }
            acceptIndentation();
            return node;
        }
        returnNode = nodeFactory->CreateIfNode(passable, currentToken, conditionNode, statementNode, elseNode);
    }
    return returnNode;
}

std::shared_ptr<Node> Parser::statement()
{
    acceptIndentation();
    if (!tokens.empty() && compilation)
    {
        acceptIndentation();
        if (accept("if"))
        {
            acceptIndentation();
            if (!expect(LEFTPARENTHESIS))
            {
                return null;
            }
            acceptIndentation();
            std::shared_ptr<Node> conditionNode = boolean();
            acceptIndentation();
            if (!expect(RIGHTPARENTHESIS))
            {
                return null;
            }
            acceptIndentation();
            if (!expect(LEFTBRACKET))
            {
                return null;
            }
            acceptIndentation();
            std::shared_ptr<Node> statementNode = block();
            if (!expect(RIGHTBRACKET))
            {
                return null;
            }
            acceptIndentation();

            std::shared_ptr<Node> elseNode = elseStatement();

            acceptIndentation();
            std::shared_ptr<Node> next = block();
            std::shared_ptr<Node> returnNode = nodeFactory->CreateIfNode(passable, currentToken, conditionNode, statementNode, elseNode);
            return nodeFactory->CreateRunNode(passable, this->currentToken, returnNode, next);
        }
        else if (accept("while"))
        {
            acceptIndentation();
            expect(LEFTPARENTHESIS);
            std::shared_ptr<Node> conditionNode = boolean();
            acceptIndentation();
            expect(RIGHTPARENTHESIS);
            acceptIndentation();
            expect(LEFTBRACKET);
            acceptIndentation();
            std::shared_ptr<Node> statementNode = block();
            acceptIndentation();
            expect(RIGHTBRACKET);
            acceptIndentation();
            std::shared_ptr<Node> next = block();
            return nodeFactory->CreateWhileNode(passable, currentToken, conditionNode, statementNode, next);
        }
        return assingment();
    }
    return null;
}

std::shared_ptr<Node> Parser::block()
{
    acceptIndentation();
    if (!tokens.empty() && compilation)
    {
        if (accept("return"))
        {
            acceptIndentation();
            std::shared_ptr<Node> returnNode = nodeFactory->CreateSetReturnNode(passable, boolean());
            if (!expectSemicolon())
            {
                return null;
            }
            return nodeFactory->CreateSemicolonNode(passable, returnNode);
        }
        std::shared_ptr<Node> dec = decloration();
        if (dec != nullptr)
        {
            return dec;
        }
        else if (functions->get(this->currentToken->getContent()) != nullptr)
        {
            std::string word = this->currentToken->getContent();
            nextToken();
            if (!expect(LEFTPARENTHESIS))
            {
                return null;
            }
            std::vector<std::shared_ptr<Node>> arguments;
            if (currentToken->getType() != RIGHTPARENTHESIS)
            {
                do
                {
                    acceptIndentation();
                    arguments.push_back(boolean());
                    acceptIndentation();
                }
                while (accept(COMMA) && !accept(RIGHTPARENTHESIS) && !tokens.empty());
            }
            if (!expect(RIGHTPARENTHESIS))
            {
                return null;
            }
            if (!expectSemicolon())
            {
                return null;
            }
            std::shared_ptr<Node> blockNode = block();
            std::shared_ptr<Node> functions = nodeFactory->CreateSemicolonNode(passable, nodeFactory->CreateGetFuncNode(passable, currentToken, word, this->functions, arguments));
            return nodeFactory->CreateRunNode(passable, currentToken, (functions), blockNode);
        }
        else if (accept("function"))
        {
            acceptIndentation();
            std::string word = currentToken->getContent();
            nextToken();
            if (!TypeDetector::isWord(word) || functions->exists(word))
            {
                compilation = false;
                return null;
            }

            // Here we add a hint that the function exists
            functions->addFunction(word);
            customFunctions->addFunction(word);
            acceptIndentation();
            if (!expect(LEFTPARENTHESIS))
            {
                functions->removeFunction(word);
                customFunctions->removeFunction(word);
                return null;
            }
            acceptIndentation();

            std::vector<std::string> arguments;
            if (currentToken->getType() != RIGHTPARENTHESIS)
            {
                do
                {
                    acceptIndentation();
                    arguments.push_back(currentToken->getContent());
                    nextToken();
                }
                while (accept(COMMA) && !accept(RIGHTPARENTHESIS) && !tokens.empty());
            }
            acceptIndentation();

            if (!expect(RIGHTPARENTHESIS))
            {
                functions->removeFunction(word);
                customFunctions->removeFunction(word);
                arguments.clear();
                return null;
            }
            acceptIndentation();

            if (!expect(LEFTBRACKET))
            {
                functions->removeFunction(word);
                customFunctions->removeFunction(word);
                return false;
            }
            acceptIndentation();

            std::shared_ptr<Node> blockNode = block();

            acceptIndentation();
            if (!expect(RIGHTBRACKET))
            {
                functions->removeFunction(word);
                customFunctions->removeFunction(word);
                return false;
            }
            std::shared_ptr<Function> newFunction = std::make_shared<CustomFunction>(passable, currentToken, word, arguments, blockNode);
            functions->setFunction(word, newFunction);
            customFunctions->setFunction(word, newFunction);
            return block();
        }
        return statement();
    }
    return null;
}

std::shared_ptr<Node> Parser::parse()
{
    if (!tokens.empty() && compilation)
    {
        nextToken();
        return block();
    }
    return null;
}

std::string Parser::toString()
{
    std::string output;
    if (!tokens.empty() && compilation)
    {
        std::shared_ptr<Node> node = parse();
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
    std::shared_ptr<Scope> globalScope = std::make_shared<Scope>(passable);
    if (!tokens.empty() && compilation)
    {
        std::shared_ptr<Node> done = parse();
        if (done != nullptr && compilation)
        {
            std::shared_ptr<Variable> output = done->execute(globalScope, globalScope);
            if (output != nullptr)
            {
                std::cout << output->toString() << std::endl;
            }
            passable->errors->print();
            return true;
        }
    }
    passable->errors->print();
    return false;
}
