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
#include "errors/debug.h"

Scanner::Scanner()
{
    unusableTokens = std::make_shared<UnusableTokens>();
    tokens = std::make_shared<Tokens>();
    items = std::vector<std::shared_ptr<Token>>();
}

bool Scanner::isAllowedCharacter(char character)
{
    if (TypeDetector::isNumeric(character))
    {
        return false;
    }
    return !unusableTokens->exists(character);
}

void Scanner::AddToken(TokenType tokenType, std::shared_ptr<LineInfo> lineInfo)
{
    items.push_back(std::move(std::make_shared<Token>(tokens->get(tokenType), tokenType, lineInfo)));
}

void Scanner::AddToken(std::string text, TokenType tokenType, std::shared_ptr<LineInfo> lineInfo)
{
    items.push_back(std::move(std::make_shared<Token>(text , tokenType, lineInfo)));
}

std::vector<std::shared_ptr<Token>> Scanner::tokenize(std::shared_ptr<TokenManager> fileReader)
{
    items.clear();
    std::string temp = "";
    std::shared_ptr<LineInfo> lineInfo = std::make_shared<LineInfo>("", fileReader->getCurrent()->getLineNumber(),0);
    while (!fileReader->isEnd())
    {
        lineInfo = std::make_shared<LineInfo>("", fileReader->getCurrent()->getLineNumber(),0);

        if (fileReader->getCurrent()->getContent() == ' ')
        {
            if (!temp.empty())
            {
                items.push_back(std::move(std::make_shared<Token>(temp, lineInfo)));
                temp = "";
            }
        }
        else if (tokens->compare(fileReader->getCurrent()->getContent(), INDENTATION))
        {

        }
        else if (tokens->compare(fileReader->getCurrent()->getContent(), TABINDENTATION))
        {

        }
        else if (fileReader->getCurrent()->getContent() == ' ' || fileReader->getCurrent()->getContent() == '\t')
        {
            // Do nothing here as recording indentation is kinda pointless.
        }
        else if (TypeDetector::isNumeric(fileReader->getCurrent()->getContent()))
        {
            temp.push_back(fileReader->getCurrent()->getContent());
        }
        else if (tokens->compare(fileReader->getCurrent()->getContent(), DOT))
        {
            temp.push_back(fileReader->getCurrent()->getContent());
        }
        else if (isAllowedCharacter(fileReader->getCurrent()->getContent()))
        {
            temp.push_back(fileReader->getCurrent()->getContent());
        }
        else
        {
            if (!temp.empty())
            {
                items.push_back(std::move(std::make_shared<Token>(temp, lineInfo)));
                temp = "";
            }
            else if (tokens->compare(fileReader->getCurrent()->getContent(), QUOTE))
            {
                fileReader->next();
                while (!tokens->compare(fileReader->getCurrent()->getContent(), QUOTE) && !fileReader->isEnd())
                {
                    lineInfo = std::make_shared<LineInfo>("", fileReader->getCurrent()->getLineNumber(),0);
                    if (fileReader->getCurrent()->getContent() == '\\')
                    {
                        if (!fileReader->isEnd())
                        {
                            if (tokens->compare(fileReader->getNext()->getContent(), QUOTE))
                            {
                                temp.push_back(fileReader->getCurrent()->getContent());
                                fileReader->next();
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
                    else
                    {
                        temp.push_back(fileReader->getCurrent()->getContent());
                        fileReader->next();
                    }
                }
                items.push_back(std::move(std::make_shared<Token>(temp, TEXT, lineInfo)));
                temp = "";

                // Move to next it
                if (!fileReader->isEnd())
                {
                    fileReader->next();
                }
            }

            lineInfo = std::make_shared<LineInfo>("", fileReader->getCurrent()->getLineNumber(),0);

            if (tokens->compare(fileReader->getCurrent()->getContent(), LEFTPARENTHESIS))
            {
                AddToken(LEFTPARENTHESIS, lineInfo);
            }
            else if (tokens->compare(fileReader->getCurrent()->getContent(), RIGHTPARENTHESIS))
            {
                AddToken(RIGHTPARENTHESIS, lineInfo);
            }
            else if (tokens->compare(fileReader->getCurrent()->getContent(), SEMICOLON))
            {
                AddToken(SEMICOLON, lineInfo);
            }

            else if (fileReader->getCurrent()->getContent() == ' ' || fileReader->getCurrent()->getContent() == '\t')
            {
                // Do nothing here as recording indentation is kinda pointless.
            }
            else if (tokens->compare(fileReader->getCurrent()->getContent(), MULTIPLICATION))
            {
                if (tokens->compare(fileReader->peak()->getContent(), EQUALS))
                {
                    fileReader->next();
                    AddToken(MULTIPLICATIONEQUAL, lineInfo);
                }
                else
                {
                    AddToken(MULTIPLICATION, lineInfo);
                }
            }
            else if (tokens->compare(fileReader->getCurrent()->getContent(), DIVISION))
            {
                if (tokens->compare(fileReader->peak()->getContent(), MULTIPLICATION))
                {
                    fileReader->next();
                    while (!fileReader->isEnd() && fileReader->getCurrent()->getContent() != '\n')
                    {
                        if (!fileReader->isEnd() && fileReader->getNext()->getContent() == '*')
                        {
                            if (!fileReader->isEnd() && fileReader->getNext()->getContent() == '/')
                            {
                                break;
                            }
                        }
                    }
                }
                else
                {
                    if (tokens->compare(fileReader->peak()->getContent(), EQUALS))
                    {
                        fileReader->next();
                        AddToken(DIVISIONEQUAL, lineInfo);
                    }
                    else
                    {
                        AddToken(DIVISION, lineInfo);
                    }
                }
            }
            else if (tokens->compare(fileReader->getCurrent()->getContent(), MOD))
            {
                AddToken(MOD, lineInfo);
            }
            else if (tokens->compare(fileReader->getCurrent()->getContent(), ADDITION))
            {
                if (tokens->compare(fileReader->peak()->getContent(), EQUALS))
                {
                    fileReader->next();
                    AddToken(ADDITIONEQUAL, lineInfo);
                }
                else if (tokens->compare(fileReader->peak()->getContent(), ADDITION))
                {
                    fileReader->next();
                    AddToken(INCREMENT, lineInfo);
                }
                else
                {
                    AddToken(ADDITION, lineInfo);
                }
            }
            else if (tokens->compare(fileReader->getCurrent()->getContent(), SUBTRACTION))
            {
                if (tokens->compare(fileReader->peak()->getContent(), EQUALS))
                {
                    fileReader->next();
                    AddToken(SUBTRACTIONEQUAL, lineInfo);
                }
                else if (tokens->compare(fileReader->peak()->getContent(), SUBTRACTION))
                {
                    fileReader->next();
                    AddToken(DECREMENT, lineInfo);
                }
                else
                {
                    AddToken(SUBTRACTION, lineInfo);
                }
            }
            else if (tokens->compare(fileReader->getCurrent()->getContent(), EQUALS))
            {
                if (!fileReader->isEnd())
                {
                    if (tokens->compare(fileReader->getNext()->getContent(), EQUALS))
                    {
                        AddToken(IFEQUALS, lineInfo);
                    }
                    else
                    {
                        fileReader->prev();
                        AddToken(EQUALS, lineInfo);
                    }
                }
                else
                {
                    AddToken(EQUALS, lineInfo);
                }
            }
            else if (tokens->compare(fileReader->getCurrent()->getContent(), BITWISEAND))
            {
                if (!fileReader->isEnd())
                {
                    if (tokens->compare(fileReader->getNext()->getContent(), BITWISEAND))
                    {
                        AddToken(AND, lineInfo);
                    }
                    else
                    {
                        AddToken(BITWISEAND, lineInfo);
                        fileReader->prev();
                    }
                }
            }
            else if (tokens->compare(fileReader->getCurrent()->getContent(), BITWISEOR))
            {
                if (!fileReader->isEnd())
                {
                    if (tokens->compare(fileReader->getNext()->getContent(), BITWISEOR))
                    {
                        AddToken(OR, lineInfo);
                    }
                    else
                    {
                        AddToken(BITWISEOR, lineInfo);
                        fileReader->prev();
                    }
                }
            }
            if (tokens->compare(fileReader->getCurrent()->getContent(), BITWISEXOR))
            {
                AddToken(BITWISEXOR, lineInfo);
            }
            else if (tokens->compare(fileReader->getCurrent()->getContent(), NOT))
            {
                if (!fileReader->isEnd())
                {
                    if (tokens->compare(fileReader->peak()->getContent(), EQUALS))
                    {
                        AddToken(IFNOTEQUALS, lineInfo);
                    }
                    else
                    {
                        AddToken(NOT, lineInfo);
                    }
                }
                else
                {
                    AddToken(NOT, lineInfo);
                }
            }
            else if (tokens->compare(fileReader->getCurrent()->getContent(), IFLESSTHAN))
            {
                if (!fileReader->isEnd())
                {
                    if (tokens->compare(fileReader->peak()->getContent(), EQUALS))
                    {
                        fileReader->next();
                        AddToken(IFLESSTHANOREQUAL, lineInfo);
                    }
                    else if (tokens->compare(fileReader->peak()->getContent(), IFLESSTHAN))
                    {
                        fileReader->next();
                        AddToken(LEFTSHIFT, lineInfo);
                    }
                    else
                    {
                        AddToken(IFLESSTHAN, lineInfo);

                    }
                }
                else
                {
                    items.push_back(std::move(std::make_shared<Token>("<", IFLESSTHAN, lineInfo)));
                }
            }
            else if (tokens->compare(fileReader->getCurrent()->getContent(), IFGREATER))
            {
                if (!fileReader->isEnd())
                {
                    if (tokens->compare(fileReader->peak()->getContent(), EQUALS))
                    {
                        fileReader->next();
                        AddToken(IFGREATERTHANOREQUAL, lineInfo);
                    }
                    else if (tokens->compare(fileReader->peak()->getContent(), IFGREATER))
                    {
                        fileReader->next();
                        AddToken(RIGHTSHIFT, lineInfo);
                    }
                    else
                    {
                        AddToken(IFGREATER, lineInfo);
                    }
                }
                else
                {
                    AddToken(IFGREATER, lineInfo);
                }
            }
            else if (tokens->compare(fileReader->getCurrent()->getContent(), BITWISECOMPLEMENT))
            {
                AddToken(BITWISECOMPLEMENT, lineInfo);
            }
            else if (tokens->compare(fileReader->getCurrent()->getContent(), SEMICOLON))
            {
                AddToken(SEMICOLON, lineInfo);
            }
            else if (tokens->compare(fileReader->getCurrent()->getContent(), RIGHTBRACKET))
            {
                AddToken(RIGHTBRACKET, lineInfo);
            }
            else if (tokens->compare(fileReader->getCurrent()->getContent(), LEFTBRACKET))
            {
                AddToken(LEFTBRACKET, lineInfo);
            }
            else if (tokens->compare(fileReader->getCurrent()->getContent(), COMMA))
            {
                AddToken(COMMA, lineInfo);
            }
        }
        fileReader->next();
    }
    return items;
}
