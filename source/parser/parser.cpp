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

Parser::Parser(std::vector<std::shared_ptr<Token>> tokens)
{
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

bool Parser::acceptIndentation()
{
    while ((this->currentToken->getContent() == " " || this->currentToken->getContent() == "\t") && !tokens.empty())
    {
        nextToken();
    }
    return true;
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
        it++;
        output = (*it);
        it--;
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
        return true;

    compilation = false;

    std::string errorMsg;
    std::stringstream ss;
    ss << "Parse error: syntax error, unexpected \"";
    ss << currentToken->getContent();
    ss << "\"";
    ss >> errorMsg;

    Errors::add(std::make_shared<Error>(PARSER_ERROR, errorMsg, currentToken,__FILE__,__LINE__));
    return false;
}

bool Parser::expect(TokenType tokenType)
{
    if (accept(tokenType))
        return true;

    compilation = false;

    std::string errorMsg = "Syntax error, unexpected \"";
    errorMsg.append(currentToken->getContent());
    errorMsg.append("\"");

    Errors::add(std::make_shared<Error>(PARSER_ERROR, errorMsg, currentToken,__FILE__,__LINE__));
    return false;
}

std::shared_ptr<Node> Parser::value()
{
    acceptIndentation();
    if (!tokens.empty() && compilation)
    {
        if (TypeDetector::isNumeric(currentToken->getContent()))
        {
            std::string number = currentToken->getContent();
            std::shared_ptr<Node> node = std::make_shared<NumberNode>(currentToken, number);
            nextToken();
            acceptIndentation();
            return node;
        }
        else if (TypeDetector::isWord(currentToken->getContent()))
        {
            std::string word = currentToken->getContent();
            if (functions->get(word) != nullptr)
            {
                nextToken();
                if (!expect(TokenType::LEFTARENTHESIS))
                {
                    compilation = false;
                    return null;
                }
                std::vector<std::shared_ptr<Node>> arguments;
                if (currentToken->getType() != TokenType::RIGHTPARENTHESIS) // Check for end of function parenthesis
                {
                    do
                    {
                        acceptIndentation();
                        arguments.push_back(std::make_shared<ReturnNode>(boolean()));
                    }
                    while (accept(TokenType::COMMA) && !accept(TokenType::RIGHTPARENTHESIS) && !tokens.empty());
                }

                if (!expect(TokenType::RIGHTPARENTHESIS))
                {
                    compilation = false;
                    arguments.clear();
                    return null;
                }
                acceptIndentation();
                return std::make_shared<ReturnNode>(
                                                    std::make_shared<GetFuncNode>(currentToken, word, functions, arguments));
            }
            else
            {
                if (currentToken->getType() == TokenType::TEXT)
                {
                    nextToken();
                    return std::make_shared<ReturnNode>(
                                                        std::make_shared<TextNode>(currentToken, word));
                }
                nextToken();
                return std::make_shared<ReturnNode>(std::make_shared<GetVarNode>(currentToken, word));
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
        if (currentToken->getType() == TokenType::LEFTARENTHESIS)
        {
            nextToken();
            value = std::make_shared<ReturnNode>(
                                                 boolean());
            if (!expect(TokenType::RIGHTPARENTHESIS))
            {
                compilation = false;
                return null;
            }
            return value;
        }
        std::shared_ptr<Node> value1 = this->value();
        return value1;
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

        while (!tokens.empty() && (currentToken->getType() == TokenType::MULTIPLICATION ||
               currentToken->getType() == TokenType::DIVISION ||
               currentToken->getType() == TokenType::MOD))
        {
            TokenType type = currentToken->getType();
            nextToken();
            acceptIndentation();
            if (type == TokenType::MULTIPLICATION)
            {
                node = std::make_shared<ReturnNode>(
                                                    std::make_shared<MulNode>(currentToken, node, factor()));
            }
            else if (type == TokenType::DIVISION)
            {
                node = std::make_shared<ReturnNode>(
                                                    std::make_shared<DivNode>(currentToken, node, factor()));
            }
            else if (type == TokenType::MOD)
            {
                node = std::make_shared<ReturnNode>(
                                                    std::make_shared<ModNode>(currentToken, node, factor()));
            }
        }
        return std::make_shared<ReturnNode>(node);
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

        while (!tokens.empty() && (currentToken->getType() == TokenType::ADDITION || currentToken->getType() == TokenType::SUBTRACTION))
        {
            TokenType type = currentToken->getType();
            nextToken();
            acceptIndentation();
            if (type == TokenType::ADDITION)
            {
                node = std::make_shared<ReturnNode>(
                                                    std::make_shared<AddNode>(currentToken, node, term()));
            }
            else
            {
                node = std::make_shared<ReturnNode>(
                                                    std::make_shared<SubNode>(currentToken, node, term()));
            }
        }
        return std::make_shared<ReturnNode>(node);
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

            while (!tokens.empty() && (currentToken->getType() == TokenType::IFEQUALS ||
                   currentToken->getType() == TokenType::IFNOTEQUALS ||
                   currentToken->getType() == TokenType::IFLESSTHAN ||
                   currentToken->getType() == TokenType::IFLESSTHANOREQUAL ||
                   currentToken->getType() == TokenType::IFGREATER ||
                   currentToken->getType() == TokenType::IFGREATERTHANOREQUAL))
            {
                if (type == TokenType::IFEQUALS)
                {
                    nextToken();
                    std::shared_ptr<Node> next = expression();
                    node = std::make_shared<ReturnNode>(
                                                        std::make_shared<IfEqualNode>(currentToken, node, next));
                }
                else if (type == TokenType::IFNOTEQUALS)
                {
                    nextToken();
                    std::shared_ptr<Node> next = expression();
                    node = std::make_shared<ReturnNode>(
                                                        std::make_shared<IfNotEqualNode>(currentToken, node, next));
                }
                else if (type == TokenType::IFLESSTHAN)
                {
                    nextToken();
                    std::shared_ptr<Node> next = expression();
                    node = std::make_shared<ReturnNode>(
                                                        std::make_shared<IfUnderNode>(currentToken, node, next));
                }
                else if (type == TokenType::IFLESSTHANOREQUAL)
                {
                    nextToken();
                    std::shared_ptr<Node> next = expression();
                    node = std::make_shared<ReturnNode>(
                                                        std::make_shared<IfUnderOrEqualNode>(currentToken, node, next));
                }
                else if (type == TokenType::IFGREATER)
                {
                    nextToken();
                    std::shared_ptr<Node> next = expression();
                    node = std::make_shared<ReturnNode>(
                                                        std::make_shared<IfOverNode>(currentToken, node, next));
                }
                else if (type == TokenType::IFGREATERTHANOREQUAL)
                {
                    nextToken();
                    std::shared_ptr<Node> next = expression();
                    node = std::make_shared<ReturnNode>(
                                                        std::make_shared<IfOverOrEqualNode>(currentToken, node, next));
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

        while (currentToken->getType() == TokenType::AND || currentToken->getType() == TokenType::OR)
        {
            if (type == TokenType::AND)
            {
                nextToken();
                std::shared_ptr<Node> next = condition();
                node = std::make_shared<ReturnNode>(
                                                    std::make_shared<IfAndNode>(currentToken, node, next));
            }
            else if (type == TokenType::OR)
            {
                nextToken();
                std::shared_ptr<Node> next = condition();
                node = std::make_shared<ReturnNode>(
                                                    std::make_shared<IfOrNode>(currentToken, node, next));
            }
        }
        return node;
    }
    return null;
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
            if (!expect(TokenType::LEFTARENTHESIS))
            {
                compilation = false;
                return null;
            }
            acceptIndentation();
            std::shared_ptr<Node> conditionNode = boolean();
            acceptIndentation();
            if (!expect(TokenType::RIGHTPARENTHESIS))
            {
                compilation = false;
                return null;
            }
            acceptIndentation();
            if (!expect(TokenType::LEFTBRACKET))
            {
                compilation = false;
                return null;
            }
            acceptIndentation();
            std::shared_ptr<Node> statementNode = block();
            if (!expect(TokenType::RIGHTBRACKET))
            {
                compilation = false;
                return null;
            }
            acceptIndentation();
            if (accept("else"))
            {
                acceptIndentation();
                if (currentToken->getContent() == "if")
                {
                    return std::make_shared<ReturnNode>(
                                                        std::make_shared<IfNode>(currentToken,
                                                                                 conditionNode,
                                                                                 statementNode,
                                                                                 statement(),
                                                                                 block()));
                }

                if (!expect(TokenType::LEFTBRACKET))
                {
                    compilation = false;
                    return null;
                }
                acceptIndentation();
                std::shared_ptr<Node> elseNode = block();
                acceptIndentation();
                if (!expect(TokenType::RIGHTBRACKET))
                {
                    compilation = false;
                    return null;
                }
                acceptIndentation();
                std::shared_ptr<Node> next = block();
                return std::make_shared<ReturnNode>(
                                                    std::make_shared<IfNode>(currentToken, conditionNode, statementNode, elseNode, next));
            }
            acceptIndentation();
            std::shared_ptr<Node> next = block();
            return std::make_shared<ReturnNode>(
                                                std::make_shared<IfNode>(currentToken, conditionNode, statementNode, nullptr, next));
        }
        else if (accept("while"))
        {
            acceptIndentation();
            expect(TokenType::LEFTARENTHESIS);
            std::shared_ptr<Node> conditionNode = boolean();
            acceptIndentation();
            expect(TokenType::RIGHTPARENTHESIS);
            acceptIndentation();
            expect(TokenType::LEFTBRACKET);
            acceptIndentation();
            std::shared_ptr<Node> statementNode = block();
            acceptIndentation();
            expect(TokenType::RIGHTBRACKET);
            acceptIndentation();
            std::shared_ptr<Node> next = block();
            return std::make_shared<ReturnNode>(std::make_shared<WhileNode>(currentToken, conditionNode, statementNode, next));
        }
        return null;
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
            std::shared_ptr<Node> returnNode = std::make_shared<SetReturnNode>(std::move(boolean()));
            if (!expect(TokenType::SEMICOLON))
            {
                compilation = false;
                return null;
            }
            return std::make_shared<ReturnNode>(std::move(returnNode));
        }
        else if (accept("set"))
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

            if (accept(TokenType::INCREMENT))
            {
                std::shared_ptr<Node> node = std::make_shared<IncrementNode>(currentToken, std::make_shared<GetVarNode>(currentToken, word));
                if (!expect(TokenType::SEMICOLON))
                {
                    compilation = false;
                    return null;
                }
                return std::make_shared<RunNode>(currentToken, std::move(std::make_shared<ReturnNode>(std::move(node))), std::move(block()));
            }

            if (accept(TokenType::DECREMENT))
            {
                std::shared_ptr<Node> node = std::make_shared<DecrementNode>(currentToken, std::make_shared<GetVarNode>(currentToken, word));
                if (!expect(TokenType::SEMICOLON))
                {
                    compilation = false;
                    return null;
                }
                return std::make_shared<RunNode>(currentToken, std::move(std::make_shared<ReturnNode>(std::move(node))), std::move(block()));
            }

            if (tokenType != TokenType::EQUALS &&
                    tokenType != TokenType::ADDITIONEQUAL &&
                    tokenType != TokenType::SUBTRACTIONEQUAL &&
                    tokenType != TokenType::MULTIPLICATIONEQUAL &&
                    tokenType != TokenType::DIVISIONEQUAL)
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
            if (!expect(TokenType::SEMICOLON))
            {
                compilation = false;
                return null;
            }
            std::shared_ptr<Node> blockNode = block();

            if (tokenType == TokenType::EQUALS)
            {
                return std::move(std::make_shared<ReturnNode>(std::make_shared<SetVarNode>(currentToken, word, expressionNode, blockNode)));
            }
            else if (tokenType == TokenType::ADDITIONEQUAL)
            {
                std::shared_ptr<Node> getNode = std::move(std::make_shared<ReturnNode>(std::make_shared<GetVarNode>(currentToken, word)));
                std::shared_ptr<Node> addNode = std::move(std::make_shared<AddNode>(currentToken, getNode, expressionNode));
                return std::move(std::make_shared<ReturnNode>(std::make_shared<SetVarNode>(currentToken, word, std::move(addNode), blockNode)));
            }
            else if (tokenType == TokenType::SUBTRACTIONEQUAL)
            {
                std::shared_ptr<Node> getNode = std::move(std::make_shared<ReturnNode>(std::make_shared<GetVarNode>(currentToken, word)));
                std::shared_ptr<Node> subNode = std::move(std::make_shared<SubNode>(currentToken, getNode, expressionNode));
                return std::move(std::make_shared<ReturnNode>(std::make_shared<SetVarNode>(currentToken, word, std::move(subNode), blockNode)));
            }
            else if (tokenType == TokenType::MULTIPLICATIONEQUAL)
            {
                std::shared_ptr<Node> getNode = std::move(std::make_shared<ReturnNode>(std::make_shared<GetVarNode>(currentToken, word)));
                std::shared_ptr<Node> mulNode = std::move(std::make_shared<MulNode>(currentToken, getNode, expressionNode));
                return std::move(std::make_shared<ReturnNode>(std::make_shared<SetVarNode>(currentToken, word, std::move(mulNode), blockNode)));
            }
            else if (tokenType == TokenType::DIVISIONEQUAL)
            {
                std::shared_ptr<Node> getNode = std::move(std::make_shared<ReturnNode>(std::make_shared<GetVarNode>(currentToken, word)));
                std::shared_ptr<Node> divNode = std::move(std::make_shared<DivNode>(currentToken, getNode, expressionNode));
                return std::move(std::make_shared<ReturnNode>(std::make_shared<SetVarNode>(currentToken, word, std::move(divNode), blockNode)));
            }

            compilation = false;
            return null;
        }
        else if (functions->get(this->currentToken->getContent()) != nullptr)
        {
            std::string word = this->currentToken->getContent();
            nextToken();
            if (!expect(TokenType::LEFTARENTHESIS))
            {
                compilation = false;
                return null;
            }


            std::vector<std::shared_ptr<Node>> arguments;
            if (currentToken->getType() != TokenType::RIGHTPARENTHESIS)
            {
                do
                {
                    acceptIndentation();
                    arguments.push_back(boolean());
                    acceptIndentation();
                }
                while (accept(TokenType::COMMA) && !accept(TokenType::RIGHTPARENTHESIS) && !tokens.empty());
            }

            if (!expect(TokenType::RIGHTPARENTHESIS))
            {
                compilation = false;
                return null;
            }
            if (!expect(TokenType::SEMICOLON))
            {
                compilation = false;
                return null;
            }
            std::shared_ptr<Node> blockNode = block();
            std::shared_ptr<Node> functions = std::make_shared<GetFuncNode>(currentToken, word, this->functions, arguments);
            return std::make_shared<ReturnNode>(std::make_shared<RunNode>(currentToken, (functions), blockNode));
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

            if (!expect(TokenType::LEFTARENTHESIS))
            {
                functions->removeFunction(word);
                compilation = false;
                return null;
            }
            acceptIndentation();

            std::vector<std::string> arguments;
            if (currentToken->getType() != TokenType::RIGHTPARENTHESIS)
            {
                do
                {
                    acceptIndentation();
                    // Check if argument is a set of char characters TODO
                    arguments.push_back(currentToken->getContent());
                    nextToken();
                }
                while (accept(TokenType::COMMA) && !accept(TokenType::RIGHTPARENTHESIS) && !tokens.empty());
            }
            acceptIndentation();

            if (!expect(TokenType::RIGHTPARENTHESIS))
            {
                functions->removeFunction(word);
                compilation = false;
                arguments.clear();
                return null;
            }
            acceptIndentation();

            if (!expect(TokenType::LEFTBRACKET))
            {
                functions->removeFunction(word);
                compilation = false;
                return false;
            }
            acceptIndentation();

            std::shared_ptr<Node> blockNode = block();

            acceptIndentation();
            if (!expect(TokenType::RIGHTBRACKET))
            {
                functions->removeFunction(word);
                compilation = false;
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
    return block();
}

bool Parser::program()
{
    std::shared_ptr<Scope> scope = std::move(std::make_shared<Scope>(std::move(std::make_shared<Variables>(false))));
    if (!tokens.empty() && compilation)
    {
        nextToken();
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
