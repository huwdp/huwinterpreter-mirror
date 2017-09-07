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
    this->compilation = true;
    this->tokens = tokens;
    this->functions = std::move(std::make_shared<Functions>());
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
    std::string errorMsg;
    std::stringstream ss;
    ss << "Parse error: syntax error, unexpected \"";
    ss << currentToken->getContent();
    ss << "\"";
    ss >> errorMsg;
    errorMessage(errorMsg, currentToken);
    return false;
}

bool Parser::expect(TokenType tokenType)
{
    if (accept(tokenType))
    {
        return true;
    }
    compilation = false;
    std::string errorMsg = "Syntax error, unexpected \"";
    errorMsg.append(currentToken->getContent());
    errorMsg.append("\"");
    errorMessage(errorMsg, currentToken);
    return false;
}

void Parser::errorMessage(std::string errorMsg, std::shared_ptr<Token> currentToken)
{
    Errors::add(std::make_shared<Error>(PARSER_ERROR, errorMsg, currentToken));
}

std::shared_ptr<Node> Parser::value()
{
    acceptIndentation();
    if (!tokens.empty() && compilation)
    {
        if (TypeDetector::isNumeric(currentToken->getContent()))
        {
            std::string number = currentToken->getContent();
            std::shared_ptr<Node> node = nodeFactory->CreateNumberNode(currentToken, number);
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
                return nodeFactory->CreateGetFuncNode(currentToken, word, functions, arguments);
            }
            else
            {
                if (currentToken->getType() == TEXT)
                {
                    nextToken();
                    return nodeFactory->CreateTextNode(currentToken, word);
                }

                std::shared_ptr<Node> var = nodeFactory->CreateGetVarNode(currentToken, word);
                nextToken();
                return var;
            }
            Errors::add(std::make_shared<Error>(PARSER_ERROR, "Unidentified word", currentToken));
        }
        else
        {
            Errors::add(std::make_shared<Error>(PARSER_ERROR, "factor: syntax error", currentToken));
            nextToken();
        }
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
            return value;
        }
        else if (currentToken->getType() == ADDITION)
        {
            nextToken();
            return factor();
        }
        else if (currentToken->getType() == SUBTRACTION)
        {
            nextToken();
            return nodeFactory->CreateUnaryMinusNode(currentToken, factor());
        }
        else if (currentToken->getType() == NOT)
        {
            nextToken();
            return nodeFactory->CreateUnaryNotNode(currentToken, factor());
        }

        // Eventually implement other unary stuff here

        value = this->value();
        return value;
    }
    return null;
}

std::shared_ptr<Node> Parser::term()
{
    acceptIndentation();
    if (!tokens.empty() && compilation)
    {
        std::shared_ptr<Node> value = factor();
        acceptIndentation();
        std::shared_ptr<Node> node = value;
        while (!tokens.empty() && (currentToken->getType() == MULTIPLICATION ||
               currentToken->getType() == DIVISION ||
               currentToken->getType() == MOD))
        {
            TokenType type = currentToken->getType();
            nextToken();
            acceptIndentation();
            if (type == MULTIPLICATION)
            {
                node = nodeFactory->CreateMulNode(currentToken, node, factor());
            }
            else if (type == DIVISION)
            {
                node = nodeFactory->CreateDivNode(currentToken, node, factor());
            }
            else if (type == MOD)
            {
                node = nodeFactory->CreateModNode(currentToken, node, factor());
            }
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
        std::shared_ptr<Node> value = term();
        acceptIndentation();
        std::shared_ptr<Node> node = value;
        while (!tokens.empty() && (currentToken->getType() == ADDITION || currentToken->getType() == SUBTRACTION))
        {
            TokenType type = currentToken->getType();
            nextToken();
            acceptIndentation();
            if (type == ADDITION)
            {
                node = nodeFactory->CreateAddNode(currentToken, node, term());
            }
            else
            {
                node = nodeFactory->CreateSubNode(currentToken, node, term());
            }
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
        std::shared_ptr<Node> value = expression();
        if (value != nullptr)
        {
            TokenType type = currentToken->getType();
            std::shared_ptr<Node> node = value;
            while (!tokens.empty() && (currentToken->getType() == IFEQUALS ||
                   currentToken->getType() == IFNOTEQUALS ||
                   currentToken->getType() == IFLESSTHAN ||
                   currentToken->getType() == IFLESSTHANOREQUAL ||
                   currentToken->getType() == IFGREATER ||
                   currentToken->getType() == IFGREATERTHANOREQUAL))
            {
                if (type == IFEQUALS)
                {
                    nextToken();
                    std::shared_ptr<Node> next = expression();
                    node = nodeFactory->CreateIfEqualNode(currentToken, node, next);
                }
                else if (type == IFNOTEQUALS)
                {
                    nextToken();
                    std::shared_ptr<Node> next = expression();
                    node = nodeFactory->CreateIfNotEqualNode(currentToken, node, next);
                }
                else if (type == IFLESSTHAN)
                {
                    nextToken();
                    std::shared_ptr<Node> next = expression();
                    node = nodeFactory->CreateIfUnderNode(currentToken, node, next);
                }
                else if (type == IFLESSTHANOREQUAL)
                {
                    nextToken();
                    std::shared_ptr<Node> next = expression();
                    node = nodeFactory->CreateIfUnderOrEqualNode(currentToken, node, next);
                }
                else if (type == IFGREATER)
                {
                    nextToken();
                    std::shared_ptr<Node> next = expression();
                    node = nodeFactory->CreateIfOverNode(currentToken, node, next);
                }
                else if (type == IFGREATERTHANOREQUAL)
                {
                    nextToken();
                    std::shared_ptr<Node> next = expression();
                    node = nodeFactory->CreateIfOverOrEqualNode(currentToken, node, next);
                }
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
        std::shared_ptr<Node> value = condition();
        TokenType type = currentToken->getType();
        std::shared_ptr<Node> node = value;
        while (currentToken->getType() == AND || currentToken->getType() == OR)
        {
            if (type == AND)
            {
                nextToken();
                std::shared_ptr<Node> next = condition();
                node = nodeFactory->CreateIfAndNode(currentToken, node, next);
            }
            else if (type == OR)
            {
                nextToken();
                std::shared_ptr<Node> next = condition();
                node = nodeFactory->CreateIfOrNode(currentToken, node, next);
            }
            else if (type == BITWISEAND)
            {
                nextToken();
                std::shared_ptr<Node> next = condition();
                node = nodeFactory->CreateBitwiseAndNode(currentToken, node, next);
            }
            else if (type == BITWISEOR)
            {
                nextToken();
                std::shared_ptr<Node> next = condition();
                node = nodeFactory->CreateBitwiseOrNode(currentToken, node, next);
            }
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
            std::shared_ptr<Node> node = nodeFactory->CreateIncrementNode(currentToken, nodeFactory->CreateGetVarNode(currentToken, word));
            if (!expect(SEMICOLON))
            {
                return null;
            }
            return nodeFactory->CreateSemicolonNode(nodeFactory->CreateRunNode(currentToken, (node), block()));
        }
        if (accept(DECREMENT))
        {
            std::shared_ptr<Node> node = nodeFactory->CreateDecrementNode(currentToken, nodeFactory->CreateGetVarNode(currentToken, word));
            if (!expect(SEMICOLON))
            {
                return null;
            }
            return nodeFactory->CreateSemicolonNode(nodeFactory->CreateRunNode(currentToken, node, block()));
        }
        acceptIndentation();
        if (accept(SEMICOLON))
        {
            return nodeFactory->CreateSemicolonNode(nodeFactory->CreateSetVarNode(currentToken, word, nullptr, block()));
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
        std::shared_ptr<Node> blockNode = block();

        if (tokenType == EQUALS)
        {
            return nodeFactory->CreateSemicolonNode(nodeFactory->CreateSetVarNode(currentToken, word, expressionNode, blockNode));
        }
        else if (tokenType == ADDITIONEQUAL)
        {
            std::shared_ptr<Node> getNode = nodeFactory->CreateGetVarNode(currentToken, word);
            std::shared_ptr<Node> addNode = nodeFactory->CreateAddNode(currentToken, getNode, expressionNode);
            return nodeFactory->CreateSemicolonNode(nodeFactory->CreateSetVarNode(currentToken, word, addNode, blockNode));
        }
        else if (tokenType == SUBTRACTIONEQUAL)
        {
            std::shared_ptr<Node> getNode = nodeFactory->CreateGetVarNode(currentToken, word);
            std::shared_ptr<Node> subNode = nodeFactory->CreateSubNode(currentToken, getNode, expressionNode);
            return nodeFactory->CreateSemicolonNode(nodeFactory->CreateSetVarNode(currentToken, word, subNode, blockNode));
        }
        else if (tokenType == MULTIPLICATIONEQUAL)
        {
            std::shared_ptr<Node> getNode = nodeFactory->CreateGetVarNode(currentToken, word);
            std::shared_ptr<Node> mulNode = nodeFactory->CreateMulNode(currentToken, getNode, expressionNode);
            return nodeFactory->CreateSemicolonNode(nodeFactory->CreateSetVarNode(currentToken, word, mulNode, blockNode));
        }
        else if (tokenType == DIVISIONEQUAL)
        {
            std::shared_ptr<Node> getNode = nodeFactory->CreateGetVarNode(currentToken, word);
            std::shared_ptr<Node> divNode = nodeFactory->CreateDivNode(currentToken, getNode, expressionNode);
            return nodeFactory->CreateSemicolonNode(nodeFactory->CreateSetVarNode(currentToken, word, divNode, blockNode));
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
                return nodeFactory->CreateSemicolonNode(nodeFactory->CreateAddVarNode(currentToken, word, nullptr, block()));
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
            std::shared_ptr<Node> blockNode = block();

            if (tokenType == EQUALS)
            {
                return nodeFactory->CreateSemicolonNode(nodeFactory->CreateAddVarNode(currentToken, word, expressionNode, blockNode));
            }
            else if (tokenType == ADDITIONEQUAL)
            {
                std::shared_ptr<Node> getNode = nodeFactory->CreateGetVarNode(currentToken, word);
                std::shared_ptr<Node> addNode = nodeFactory->CreateAddNode(currentToken, getNode, expressionNode);
                return nodeFactory->CreateSemicolonNode(nodeFactory->CreateAddVarNode(currentToken, word, addNode, blockNode));
            }
            else if (tokenType == SUBTRACTIONEQUAL)
            {
                std::shared_ptr<Node> getNode = nodeFactory->CreateGetVarNode(currentToken, word);
                std::shared_ptr<Node> subNode = nodeFactory->CreateSubNode(currentToken, getNode, expressionNode);
                return nodeFactory->CreateSemicolonNode(nodeFactory->CreateAddVarNode(currentToken, word, subNode, blockNode));
            }
            else if (tokenType == MULTIPLICATIONEQUAL)
            {
                std::shared_ptr<Node> getNode = nodeFactory->CreateGetVarNode(currentToken, word);
                std::shared_ptr<Node> mulNode = nodeFactory->CreateMulNode(currentToken, getNode, expressionNode);
                return nodeFactory->CreateSemicolonNode(nodeFactory->CreateAddVarNode(currentToken, word, mulNode, blockNode));
            }
            else if (tokenType == DIVISIONEQUAL)
            {
                std::shared_ptr<Node> getNode = nodeFactory->CreateGetVarNode(currentToken, word);
                std::shared_ptr<Node> divNode = nodeFactory->CreateDivNode(currentToken, getNode, expressionNode);
                return nodeFactory->CreateSemicolonNode(nodeFactory->CreateAddVarNode(currentToken, word, divNode, blockNode));
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
                return nodeFactory->CreateSemicolonNode(nodeFactory->CreateAddVarNode(currentToken, word, nullptr, block()));
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
            std::shared_ptr<Node> blockNode = block();

            if (tokenType == EQUALS)
            {
                return nodeFactory->CreateSemicolonNode(nodeFactory->CreateAddConstNode(currentToken, word, expressionNode, blockNode));
            }
            else if (tokenType == ADDITIONEQUAL)
            {
                std::shared_ptr<Node> getNode = nodeFactory->CreateGetVarNode(currentToken, word);
                std::shared_ptr<Node> addNode = nodeFactory->CreateAddNode(currentToken, getNode, expressionNode);
                return nodeFactory->CreateSemicolonNode(nodeFactory->CreateAddConstNode(currentToken, word, addNode, blockNode));
            }
            else if (tokenType == SUBTRACTIONEQUAL)
            {
                std::shared_ptr<Node> getNode = nodeFactory->CreateGetVarNode(currentToken, word);
                std::shared_ptr<Node> subNode = nodeFactory->CreateSubNode(currentToken, getNode, expressionNode);
                return nodeFactory->CreateSemicolonNode(nodeFactory->CreateAddConstNode(currentToken, word, subNode, blockNode));
            }
            else if (tokenType == MULTIPLICATIONEQUAL)
            {
                std::shared_ptr<Node> getNode = nodeFactory->CreateGetVarNode(currentToken, word);
                std::shared_ptr<Node> mulNode = nodeFactory->CreateMulNode(currentToken, getNode, expressionNode);
                return nodeFactory->CreateSemicolonNode(nodeFactory->CreateAddConstNode(currentToken, word, mulNode, blockNode));
            }
            else if (tokenType == DIVISIONEQUAL)
            {
                std::shared_ptr<Node> getNode = nodeFactory->CreateGetVarNode(currentToken, word);
                std::shared_ptr<Node> divNode = nodeFactory->CreateDivNode(currentToken, getNode, expressionNode);
                return nodeFactory->CreateSemicolonNode(nodeFactory->CreateAddConstNode(currentToken, word, divNode, blockNode));
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
        returnNode = nodeFactory->CreateIfNode(currentToken, conditionNode, statementNode, elseNode);
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
            std::shared_ptr<Node> returnNode = nodeFactory->CreateIfNode(currentToken, conditionNode, statementNode, elseNode);
            return nodeFactory->CreateRunNode(this->currentToken, returnNode, next);
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
            return nodeFactory->CreateWhileNode(currentToken, conditionNode, statementNode, next);
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
            std::shared_ptr<Node> returnNode = nodeFactory->CreateSetReturnNode(boolean());
            if (!expect(SEMICOLON))
            {
                return null;
            }
            return nodeFactory->CreateSemicolonNode(returnNode);
        }
        std::shared_ptr<Node> dec = decloration();
        if (dec != nullptr)
        {
            return dec;
        }
        if (functions->get(this->currentToken->getContent()) != nullptr)
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
            if (!expect(SEMICOLON))
            {
                return null;
            }
            std::shared_ptr<Node> blockNode = block();
            std::shared_ptr<Node> functions = nodeFactory->CreateGetFuncNode(currentToken, word, this->functions, arguments);
            return nodeFactory->CreateSemicolonNode(nodeFactory->CreateRunNode(currentToken, (functions), blockNode));
        }
        else if (accept("function"))
        {
            acceptIndentation();
            std::string word = currentToken->getContent();
            nextToken();

            // Check if word is word
            // Check if word already exists in functions list
            if (!TypeDetector::isWord(word) || functions->exists(word))
            {
                compilation = false;
                return null;
            }

            // Here we add a hint that the function exists
            functions->addFunction(word);
            acceptIndentation();

            if (!expect(LEFTPARENTHESIS))
            {
                functions->removeFunction(word);
                return null;
            }
            acceptIndentation();

            std::vector<std::string> arguments;
            if (currentToken->getType() != RIGHTPARENTHESIS)
            {
                do
                {
                    acceptIndentation();
                    // Check if argument is a set of char characters TODO
                    arguments.push_back(currentToken->getContent());
                    nextToken();
                }
                while (accept(COMMA) && !accept(RIGHTPARENTHESIS) && !tokens.empty());
            }
            acceptIndentation();

            if (!expect(RIGHTPARENTHESIS))
            {
                functions->removeFunction(word);
                arguments.clear();
                return null;
            }
            acceptIndentation();

            if (!expect(LEFTBRACKET))
            {
                functions->removeFunction(word);
                return false;
            }
            acceptIndentation();

            std::shared_ptr<Node> blockNode = block();

            acceptIndentation();
            if (!expect(RIGHTBRACKET))
            {
                functions->removeFunction(word);
                return false;
            }
            functions->addFunction(word, std::make_shared<CustomFunction>(currentToken, arguments, blockNode));
            return block();
        }
        else
        {
            return statement();
        }
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

bool Parser::execute()
{
    std::shared_ptr<Scope> scope = std::make_shared<Scope>();
    if (!tokens.empty() && compilation)
    {
        std::shared_ptr<Node> done = parse();
        if (done != nullptr && compilation)
        {
            std::shared_ptr<Variable> output = done->execute(scope);
            if (output != nullptr)
            {
                std::cout << output->toString() << std::endl;
            }
            return true;
        }
    }
    return false;
}
