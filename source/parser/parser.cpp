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
    std::shared_ptr<Variables> v(new Variables());
    this->variables = v;
    this->functions = std::shared_ptr<Functions>(new Functions());
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
    while (this->currentToken->getContent() == " " || this->currentToken->getContent() == "\t")
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

    // fix bug when var not found
    // report error if so


    std::shared_ptr<Node> null;
    acceptIndentation();
    if (it != tokens.end())
    {
        if (TypeDetector::isNumeric(currentToken->getContent()))
        {
            std::string number = currentToken->getContent();
            std::shared_ptr<Node> n1(new NumberNode(currentToken, number));
            nextToken();
            acceptIndentation();

            // Remove
            //std::cout << n1->getToken()->getContent() << std::endl;

            return n1;
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
                        arguments.push_back((boolean()));
                    }
                    while (accept(TokenType::COMMA) && !accept(TokenType::RIGHTPARENTHESIS));
                }

                if (!expect(TokenType::RIGHTPARENTHESIS))
                {
                    compilation = false;
                    arguments.clear();
                    return null;
                }
                acceptIndentation();
                return std::make_shared<GetFuncNode>(currentToken, word, functions, arguments);
            }
            else
            {
                if (currentToken->getType() == TokenType::TEXT)
                {
                    nextToken();
                    std::shared_ptr<TextNode> n3(new TextNode(currentToken, word));
                    return n3;
                }
                nextToken();
                std::shared_ptr<GetVarNode> n4(new GetVarNode(currentToken, word, variables));
                return n4;
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
    std::shared_ptr<Node> null;
    acceptIndentation();
    if (it != tokens.end())
    {
        std::shared_ptr<Node> value;
        if (currentToken->getType() == TokenType::LEFTARENTHESIS)
        {
            nextToken();
            value = boolean();
            //std::cout << value->getToken()->getContent();
            if (!expect(TokenType::RIGHTPARENTHESIS))
            {
                compilation = false;
                return null;
            }
            //nextToken();
            return value;
        }
        std::shared_ptr<Node> value1 = this->value();
        //std::cout << value1->getToken()->getContent();
        return value1;
    }
    return null;
}

std::shared_ptr<Node>Parser::term()
{
    std::shared_ptr<Node> null;
    acceptIndentation();
    if (it != tokens.end())
    {
        std::shared_ptr<Node> value = factor();
        acceptIndentation();

        std::shared_ptr<Node> temp = value;

        while (!tokens.empty() && (currentToken->getType() == TokenType::MULTIPLICATION ||
               currentToken->getType() == TokenType::DIVISION ||
               currentToken->getType() == TokenType::MOD))
        {
            TokenType type = currentToken->getType();
            nextToken();
            acceptIndentation();
            if (type == TokenType::MULTIPLICATION)
            {
                temp = std::make_shared<MulNode>(currentToken, temp, (factor()));
            }
            else if (type == TokenType::DIVISION)
            {
                temp = std::make_shared<DivNode>(currentToken, temp, (factor()));
            }
            else if (type == TokenType::MOD)
            {
                temp = std::make_shared<ModNode>(currentToken, temp, (factor()));
            }
        }
        return temp;
    }
    return null;
}

std::shared_ptr<Node>Parser::expression()
{
    std::shared_ptr<Node> null;
    acceptIndentation();
    if (it != tokens.end())
    {
        std::shared_ptr<Node> value = term();
        acceptIndentation();

        std::shared_ptr<Node> temp = value;

        while (!tokens.empty() && (currentToken->getType() == TokenType::ADDITION || currentToken->getType() == TokenType::SUBTRACTION))
        {
            TokenType type = currentToken->getType();
            nextToken();
            acceptIndentation();
            if (type == TokenType::ADDITION)
            {
                temp = std::make_shared<AddNode>(currentToken, temp, (term()));
            }
            else
            {
                temp = std::make_shared<SubNode>(currentToken, temp, (term()));
            }
        }
        return temp;
    }
    return null;
}

std::shared_ptr<Node>Parser::condition()
{
    std::shared_ptr<Node> null;
    if (it != tokens.end())
    {
        std::shared_ptr<Node> value = expression();
        if (value != nullptr)
        {
            TokenType type = currentToken->getType();

            std::shared_ptr<Node> temp = value;

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
                    temp = std::make_shared<IfEqualNode>(currentToken, temp, (next));
                }
                else if (type == TokenType::IFNOTEQUALS)
                {
                    nextToken();
                    std::shared_ptr<Node> next = expression();
                    temp = std::make_shared<IfNotEqualNode>(currentToken, temp, (next));
                }
                else if (type == TokenType::IFLESSTHAN)
                {
                    nextToken();
                    std::shared_ptr<Node> next = expression();
                    temp = std::make_shared<IfUnderNode>(currentToken, temp, (next));
                }
                else if (type == TokenType::IFLESSTHANOREQUAL)
                {
                    nextToken();
                    std::shared_ptr<Node> next = expression();
                    temp = std::make_shared<IfUnderOrEqualNode>(currentToken, temp, (next));
                }
                else if (type == TokenType::IFGREATER)
                {
                    nextToken();
                    std::shared_ptr<Node> next = expression();
                    temp = std::make_shared<IfOverNode>(currentToken, temp, (next));
                }
                else if (type == TokenType::IFGREATERTHANOREQUAL)
                {
                    nextToken();
                    std::shared_ptr<Node> next = expression();
                    temp = std::make_shared<IfOverOrEqualNode>(currentToken, temp, (next));
                }
            }
            return temp;
        }
    }
    return null;
}

std::shared_ptr<Node>Parser::boolean()
{
    std::shared_ptr<Node> null;
    if (it != tokens.end())
    {
        std::shared_ptr<Node> value = condition();
        TokenType type = currentToken->getType();

        std::shared_ptr<Node> temp = value;

        while (currentToken->getType() == TokenType::AND || currentToken->getType() == TokenType::OR)
        {
            if (type == TokenType::AND)
            {
                nextToken();
                std::shared_ptr<Node> next = condition();
                temp = std::make_shared<IfAndNode>(currentToken, temp, (next));
            }
            else if (type == TokenType::OR)
            {
                nextToken();
                std::shared_ptr<Node> next = condition();
                temp = std::make_shared<IfOrNode>(currentToken, temp, (next));
            }
        }
        return temp;
    }
    return null;
}

std::shared_ptr<Node>Parser::statement()
{
    std::shared_ptr<Node> null;
    if (it != tokens.end())
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
            std::shared_ptr<Node> condition2 = boolean();
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
            std::shared_ptr<Node> statement2 = block();
            if (!expect(TokenType::RIGHTBRACKET))
            {
                compilation = false;
                return null;
            }
            acceptIndentation();
            if (accept("else"))
            {
                acceptIndentation();
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
                return std::make_shared<IfNode>(currentToken, condition2, statement2, elseNode, next);
            }
            acceptIndentation();
            std::shared_ptr<Node> next = block();
            return std::make_shared<IfNode>(currentToken, condition2, statement2, nullptr, next);
        }
        else if (accept("while"))
        {
            acceptIndentation();
            expect(TokenType::LEFTARENTHESIS);
            std::shared_ptr<Node> condition2 = boolean();
            expect(TokenType::RIGHTPARENTHESIS);
            acceptIndentation();
            expect(TokenType::LEFTBRACKET);
            std::shared_ptr<Node> statement2 = block();
            expect(TokenType::RIGHTBRACKET);
            acceptIndentation();
            std::shared_ptr<Node> next = block();
            return std::make_shared<WhileNode>(currentToken, condition2, statement2, next);
        }
        return null;
    }
    return null;
}

std::shared_ptr<Node>Parser::block()
{
    std::shared_ptr<Node> null;
    acceptIndentation();
    if (it != tokens.end())
    {
        if (accept("set"))
        {
            acceptIndentation();
            std::string word = currentToken->getContent();
            if (!TypeDetector::isWord(currentToken->getContent()))
            {
                compilation = false;
                return null;
            }
            nextToken();
            acceptIndentation();
            if (!expect(TokenType::EQUALS))
            {
                compilation = false;
                return null;
            }

            acceptIndentation();
            std::shared_ptr<Node> expression1 = boolean();
            if (expression1 == nullptr)
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
            std::shared_ptr<Node> block1 = block();
            return std::make_shared<SetVarNode>(currentToken, word, expression1, block1, variables);
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
            do
            {
                acceptIndentation();
                arguments.push_back(boolean());
                acceptIndentation();
            }
            while (accept(TokenType::COMMA) && !accept(TokenType::RIGHTPARENTHESIS));

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
            std::shared_ptr<Node> block2 = block();
            std::shared_ptr<Node> functions(new GetFuncNode(currentToken, word, this->functions, arguments));
            return std::make_shared<RunNode>(currentToken, (functions), block2);
        }
        else
        {
            return statement();
        }
    }
    return null;
}

bool Parser::program()
{
    if (!tokens.empty())
    {
        nextToken();
        std::shared_ptr<Node> done = block();
        if (done.get() != nullptr && compilation)
        {
            done->execute();
            return true;
        }
    }
    return false;
}
