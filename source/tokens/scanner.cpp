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

#include "scanner.h"

#include <string>
#include <vector>
#include <iostream>
#include "../errors/debug.h"

Scanner::Scanner()
{
    tokenDetector = std::make_shared<TokenDetector>();
}

Scanner::~Scanner()
{

}


bool isNum(char num)
{
    if (num >= '0' && num <= '9')
    {
        return true;
    }
    return false;
}

bool isCharacter(char character)
{
    if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'))
    {
        return true;
    }
    return false;
}

std::vector<std::shared_ptr<Token>> Scanner::tokenize(std::shared_ptr<TokenManager> fileReader)
{
    std::vector<std::shared_ptr<Token>> tokens;
    std::string temp = "";

    std::shared_ptr<LineInfo> lineInfo(new LineInfo("", fileReader->getCurrent()->getLineNumber(),0));

    while (!fileReader->isEnd())
    {
        lineInfo = std::make_shared<LineInfo>("", fileReader->getCurrent()->getLineNumber(),0);

        if (fileReader->getCurrent()->getContent() == ' ')
        {
            if (!temp.empty())
            {
                tokens.push_back(std::move(std::make_shared<Token>(temp, std::move(lineInfo))));
                temp = "";
            }
        }
        else if (TypeDetector::isNumeric(fileReader->getCurrent()->getContent()))
        {
            temp.push_back(fileReader->getCurrent()->getContent());
        }
        else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), TokenType::DOT))
        {
            temp.push_back(fileReader->getCurrent()->getContent());
        }
        else if (isCharacter(fileReader->getCurrent()->getContent()))
        {
            temp.push_back(fileReader->getCurrent()->getContent());
        }
        else
        {
            if (!temp.empty())
            {

                tokens.push_back(std::move(std::make_shared<Token>(temp, std::move(lineInfo))));
                temp = "";
            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), TokenType::QUOTE))
            {
                    fileReader->next();
                    while (!tokenDetector->compare(fileReader->getCurrent()->getContent(), TokenType::QUOTE) && !fileReader->isEnd())
                    {
                        lineInfo = std::make_shared<LineInfo>("", fileReader->getCurrent()->getLineNumber(),0);
                        if (fileReader->getCurrent()->getContent() == '\\')
                        {
                            if (!fileReader->isEnd())
                            {
                                fileReader->next();
                                if (fileReader->getCurrent()->getContent() == '"')
                                {
                                    temp.push_back(fileReader->getCurrent()->getContent());
                                    fileReader->next();
                                    fileReader->next();
                                }
                                fileReader->prev();
                            }
                            else
                            {
                                temp.push_back(fileReader->getCurrent()->getContent());
                                fileReader->next();
                            }
                        }
                        else
                        {
                            temp.push_back(fileReader->getCurrent()->getContent());
                            fileReader->next();
                        }
                    }
                tokens.push_back(std::move(std::make_shared<Token>(temp, TokenType::TEXT, std::move(lineInfo))));
                temp = "";

                // Move to next it
                if (!fileReader->isEnd())
                {
                    fileReader->next();
                }
            }
            lineInfo = std::make_shared<LineInfo>("", fileReader->getCurrent()->getLineNumber(),0);
            if (tokenDetector->compare(fileReader->getCurrent()->getContent(), TokenType::LEFTARENTHESIS))
            {
                tokens.push_back(std::move(std::make_shared<Token>("(", TokenType::LEFTARENTHESIS, std::move(lineInfo))));
            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), TokenType::RIGHTPARENTHESIS))
            {
                tokens.push_back(std::move(std::make_shared<Token>(")", TokenType::RIGHTPARENTHESIS, std::move(lineInfo))));
            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), TokenType::SEMICOLON))
            {
                tokens.push_back(std::move(std::make_shared<Token>(";", TokenType::SEMICOLON, std::move(lineInfo))));
            }
            else if (fileReader->getCurrent()->getContent() == ' ' || fileReader->getCurrent()->getContent() == '\t')
            {
                tokens.push_back(std::move(std::make_shared<Token>(" ", TokenType::INDENTATION, std::move(lineInfo))));
            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), TokenType::MULTIPLICATION))
            {
                tokens.push_back(std::make_shared<Token>("*", TokenType::MULTIPLICATION, std::move(lineInfo)));
            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), TokenType::DIVISION))
            {
                if (fileReader->peak()->getContent() == '*')
                {
                    fileReader->getNext();
                    while (!fileReader->isEnd() && fileReader->getCurrent()->getContent() != '\n')
                    {
                        if (fileReader->getNext()->getContent() == '*')
                        {
                            if (fileReader->getNext()->getContent() == '/')
                            {
                                break;
                            }
                        }

                        // Fix bug here
                    }
                }
                else
                {
                    tokens.push_back(std::move(std::make_shared<Token>("/", TokenType::DIVISION, std::move(lineInfo))));
                }
            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), TokenType::MOD))
            {
                tokens.push_back(std::move(std::make_shared<Token>("%", TokenType::MOD, std::move(lineInfo))));
            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), TokenType::ADDITION))
            {
                char token = fileReader->getPrev()->getContent();
                fileReader->next();
                if (tokenDetector->compare(token, LEFTARENTHESIS) ||
                        tokenDetector->compare(token, ADDITION) ||
                        tokenDetector->compare(token, SUBTRACTION) ||
                        tokenDetector->compare(token, MULTIPLICATION) ||
                        tokenDetector->compare(token, DIVISION))
                {
                    temp.push_back(fileReader->getCurrent()->getContent());
                }
                else
                {
                    tokens.push_back(std::move(std::make_shared<Token>("+", TokenType::ADDITION, std::move(lineInfo))));
                }

            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), TokenType::SUBTRACTION))
            {
                char token = fileReader->getPrev()->getContent();
                fileReader->next();
                if (tokenDetector->compare(token, LEFTARENTHESIS) ||
                        tokenDetector->compare(token, ADDITION) ||
                        tokenDetector->compare(token, SUBTRACTION) ||
                        tokenDetector->compare(token, MULTIPLICATION) ||
                        tokenDetector->compare(token, DIVISION))
                {
                    temp.push_back(fileReader->getCurrent()->getContent());
                }
                else
                {
                    tokens.push_back(std::move(std::make_shared<Token>("-", TokenType::SUBTRACTION, std::move(lineInfo))));
                }
            }
            else if (fileReader->getCurrent()->getContent() == '=')
            {
                if (!fileReader->isEnd())
                {
                    fileReader->next();
                    if (fileReader->getCurrent()->getContent() == '=')
                    {
                        tokens.push_back(std::move(std::make_shared<Token>("==", TokenType::IFEQUALS, std::move(lineInfo))));
                    }
                    else
                    {
                        fileReader->prev();
                        tokens.push_back(std::move(std::make_shared<Token>("=", TokenType::EQUALS, std::move(lineInfo))));
                    }
                }
                else
                {
                    tokens.push_back(std::move(std::make_shared<Token>("=", TokenType::EQUALS, std::move(lineInfo))));
                }
            }
            else if (fileReader->getCurrent()->getContent() == '&')
            {
                if (!fileReader->isEnd())
                {
                    fileReader->next();
                    if (fileReader->getCurrent()->getContent() == '&')
                    {
                        tokens.push_back(std::move(std::make_shared<Token>("&&", TokenType::AND, std::move(lineInfo))));
                    }
                    else
                    {
                        fileReader->prev();
                        // Bitwise and
                    }
                }
                else
                {
                    // Bitwise and
                }
            }
            else if (fileReader->getCurrent()->getContent() == '|')
            {
                if (!fileReader->isEnd())
                {
                    fileReader->next();
                    if (fileReader->getCurrent()->getContent() == '|')
                    {
                        tokens.push_back(std::move(std::make_shared<Token>("||", TokenType::OR, std::move(lineInfo))));
                    }
                    else
                    {
                        fileReader->prev();
                        // Bitwise or
                    }
                }
                else
                {
                    // Bitwise or
                }
            }
            else if (fileReader->getCurrent()->getContent() == '!')
            {
                if (!fileReader->isEnd())
                {
                    fileReader->next();
                    if (tokenDetector->compare(fileReader->getCurrent()->getContent(), TokenType::EQUALS))
                    {
                        tokens.push_back(std::move(std::make_shared<Token>("!=", TokenType::IFNOTEQUALS, std::move(lineInfo))));
                    }
                }
                else
                {

                }
            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), TokenType::IFLESSTHAN))
            {
                if (!fileReader->isEnd())
                {
                    fileReader->next();
                    if (fileReader->getCurrent()->getContent() == '=')
                    {

                        tokens.push_back(std::move(std::make_shared<Token>("<=", TokenType::IFLESSTHANOREQUAL, std::move(lineInfo))));
                    }
                    else
                    {
                        tokens.push_back(std::move(std::make_shared<Token>("<", TokenType::IFLESSTHAN, std::move(lineInfo))));
                        fileReader->prev();
                    }
                }
                else
                {
                    tokens.push_back(std::move(std::make_shared<Token>("<", TokenType::IFLESSTHAN, std::move(lineInfo))));
                }
            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), TokenType::IFGREATER))
            {
                if (!fileReader->isEnd())
                {
                    fileReader->next();
                    if (fileReader->getCurrent()->getContent() == '=')
                    {
                        tokens.push_back(std::move(std::make_shared<Token>(">=", TokenType::IFGREATERTHANOREQUAL, std::move(lineInfo))));
                    }
                    else
                    {

                        tokens.push_back(std::move(std::make_shared<Token>(">", TokenType::IFGREATER, std::move(lineInfo))));
                        fileReader->prev();
                    }
                }
                else
                {
                    tokens.push_back(std::move(std::make_shared<Token>(">", TokenType::IFGREATER, std::move(lineInfo))));
                }
            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), TokenType::SEMICOLON))
            {
                tokens.push_back(std::move(std::make_shared<Token>(";", TokenType::SEMICOLON, std::move(lineInfo))));
            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), TokenType::RIGHTBRACKET))
            {
                tokens.push_back(std::move(std::make_shared<Token>("}", TokenType::RIGHTBRACKET, lineInfo)));
            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), TokenType::LEFTBRACKET))
            {
                tokens.push_back(std::move(std::make_shared<Token>("{", TokenType::LEFTBRACKET, std::move(lineInfo))));
            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), TokenType::COMMA))
            {
                tokens.push_back(std::move(std::make_shared<Token>(",", TokenType::COMMA, std::move(lineInfo))));
            }
        }
        fileReader->next();
    }
    return tokens;
}
