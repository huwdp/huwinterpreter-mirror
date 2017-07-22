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
    tokenDetector = std::make_shared<TokenDetector>();

}

bool Scanner::isAllowedCharacter(char character)
{
    if (std::isalpha(character))
    {
        return true;
    }
    if (TypeDetector::isNumeric(character))
    {
        return false;
    }
    return unusableTokens->exists(character);
}

std::vector<std::shared_ptr<Token>> Scanner::tokenize(std::shared_ptr<TokenManager> fileReader)
{
    std::vector<std::shared_ptr<Token>> tokens;
    std::string temp = "";

    std::shared_ptr<LineInfo> lineInfo = std::make_shared<LineInfo>("", fileReader->getCurrent()->getLineNumber(),0);

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
        else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), DOT))
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
                tokens.push_back(std::move(std::make_shared<Token>(temp, std::move(lineInfo))));
                temp = "";
            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), QUOTE))
            {
                fileReader->next();
                while (!tokenDetector->compare(fileReader->getCurrent()->getContent(), QUOTE) && !fileReader->isEnd())
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
                tokens.push_back(std::move(std::make_shared<Token>(temp, TEXT, std::move(lineInfo))));
                temp = "";

                // Move to next it
                if (!fileReader->isEnd())
                {
                    fileReader->next();
                }
            }

            lineInfo = std::make_shared<LineInfo>("", fileReader->getCurrent()->getLineNumber(),0);
            if (tokenDetector->compare(fileReader->getCurrent()->getContent(), LEFTARENTHESIS))
            {
                tokens.push_back(std::move(std::make_shared<Token>("(", LEFTARENTHESIS, std::move(lineInfo))));
            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), RIGHTPARENTHESIS))
            {
                tokens.push_back(std::move(std::make_shared<Token>(")", RIGHTPARENTHESIS, std::move(lineInfo))));
            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), SEMICOLON))
            {
                tokens.push_back(std::move(std::make_shared<Token>(";", SEMICOLON, std::move(lineInfo))));
            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), NOT))
            {
                tokens.push_back(std::move(std::make_shared<Token>("!", NOT, std::move(lineInfo))));
            }
            else if (fileReader->getCurrent()->getContent() == ' ' || fileReader->getCurrent()->getContent() == '\t')
            {
                tokens.push_back(std::move(std::make_shared<Token>(" ", INDENTATION, std::move(lineInfo))));
            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), MULTIPLICATION))
            {
                if (tokenDetector->compare(fileReader->peak()->getContent(), EQUALS))
                {
                    fileReader->getNext();
                    tokens.push_back(std::make_shared<Token>("*=", MULTIPLICATIONEQUAL, std::move(lineInfo)));
                }
                else
                {
                    tokens.push_back(std::make_shared<Token>("*", MULTIPLICATION, std::move(lineInfo)));
                }
            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), DIVISION))
            {
                if (fileReader->peak()->getContent() == '*')
                {
                    fileReader->getNext();
                    while (!fileReader->isEnd() && fileReader->getCurrent()->getContent() != '\n')
                    {
                        if (!fileReader->isEnd() && fileReader->getNext()->getContent() == '*')
                        {
                            if (!fileReader->isEnd() && fileReader->getNext()->getContent() == '/')
                            {
                                break;
                            }
                        }

                        // Fix bug here
                    }
                }
                else
                {
                    if (tokenDetector->compare(fileReader->peak()->getContent(), EQUALS))
                    {
                        fileReader->getNext();
                        tokens.push_back(std::make_shared<Token>("/=", DIVISIONEQUAL, std::move(lineInfo)));
                    }
                    else
                    {
                        tokens.push_back(std::make_shared<Token>("/", DIVISION, std::move(lineInfo)));
                    }
                }
            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), MOD))
            {
                tokens.push_back(std::move(std::make_shared<Token>("%", MOD, std::move(lineInfo))));
            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), ADDITION))
            {
                if (tokenDetector->compare(fileReader->peak()->getContent(), EQUALS))
                {
                    fileReader->getNext();
                    tokens.push_back(std::move(std::make_shared<Token>("+=", ADDITIONEQUAL, std::move(lineInfo))));
                }
                else if (tokenDetector->compare(fileReader->peak()->getContent(), ADDITION))
                {
                    fileReader->getNext();
                    tokens.push_back(std::move(std::make_shared<Token>("++", INCREMENT, std::move(lineInfo))));
                }
                else
                {
                    tokens.push_back(std::move(std::make_shared<Token>("+", ADDITION, std::move(lineInfo))));
                }
            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), SUBTRACTION))
            {
                if (tokenDetector->compare(fileReader->peak()->getContent(), EQUALS))
                {
                    fileReader->getNext();
                    tokens.push_back(std::move(std::make_shared<Token>("-=", SUBTRACTIONEQUAL, std::move(lineInfo))));
                }
                else if (tokenDetector->compare(fileReader->peak()->getContent(), SUBTRACTION))
                {
                    fileReader->getNext();
                    tokens.push_back(std::move(std::make_shared<Token>("--", DECREMENT, std::move(lineInfo))));
                }
                else
                {
                    tokens.push_back(std::move(std::make_shared<Token>("-", SUBTRACTION, std::move(lineInfo))));
                }
            }
            else if (fileReader->getCurrent()->getContent() == '=')
            {
                if (!fileReader->isEnd())
                {
                    fileReader->next();
                    if (fileReader->getCurrent()->getContent() == '=')
                    {
                        tokens.push_back(std::move(std::make_shared<Token>("==", IFEQUALS, std::move(lineInfo))));
                    }
                    else
                    {
                        fileReader->prev();
                        tokens.push_back(std::move(std::make_shared<Token>("=", EQUALS, std::move(lineInfo))));
                    }
                }
                else
                {
                    tokens.push_back(std::move(std::make_shared<Token>("=", EQUALS, std::move(lineInfo))));
                }
            }
            else if (fileReader->getCurrent()->getContent() == '&')
            {
                if (!fileReader->isEnd())
                {
                    fileReader->next();
                    if (fileReader->getCurrent()->getContent() == '&')
                    {
                        tokens.push_back(std::move(std::make_shared<Token>("&&", AND, std::move(lineInfo))));
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
                        tokens.push_back(std::move(std::make_shared<Token>("||", OR, std::move(lineInfo))));
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
                    if (tokenDetector->compare(fileReader->getCurrent()->getContent(), EQUALS))
                    {
                        tokens.push_back(std::move(std::make_shared<Token>("!=", IFNOTEQUALS, std::move(lineInfo))));
                    }
                }
                else
                {

                }
            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), IFLESSTHAN))
            {
                if (!fileReader->isEnd())
                {
                    fileReader->next();
                    if (fileReader->getCurrent()->getContent() == '=')
                    {

                        tokens.push_back(std::move(std::make_shared<Token>("<=", IFLESSTHANOREQUAL, std::move(lineInfo))));
                    }
                    else
                    {
                        tokens.push_back(std::move(std::make_shared<Token>("<", IFLESSTHAN, std::move(lineInfo))));
                        fileReader->prev();
                    }
                }
                else
                {
                    tokens.push_back(std::move(std::make_shared<Token>("<", IFLESSTHAN, std::move(lineInfo))));
                }
            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), IFGREATER))
            {
                if (!fileReader->isEnd())
                {
                    fileReader->next();
                    if (fileReader->getCurrent()->getContent() == '=')
                    {
                        tokens.push_back(std::move(std::make_shared<Token>(">=", IFGREATERTHANOREQUAL, std::move(lineInfo))));
                    }
                    else
                    {

                        tokens.push_back(std::move(std::make_shared<Token>(">", IFGREATER, std::move(lineInfo))));
                        fileReader->prev();
                    }
                }
                else
                {
                    tokens.push_back(std::move(std::make_shared<Token>(">", IFGREATER, std::move(lineInfo))));
                }
            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), SEMICOLON))
            {
                tokens.push_back(std::move(std::make_shared<Token>(";", SEMICOLON, std::move(lineInfo))));
            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), RIGHTBRACKET))
            {
                tokens.push_back(std::move(std::make_shared<Token>("}", RIGHTBRACKET, lineInfo)));
            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), LEFTBRACKET))
            {
                tokens.push_back(std::move(std::make_shared<Token>("{", LEFTBRACKET, std::move(lineInfo))));
            }
            else if (tokenDetector->compare(fileReader->getCurrent()->getContent(), COMMA))
            {
                tokens.push_back(std::move(std::make_shared<Token>(",", COMMA, std::move(lineInfo))));
            }
        }
        fileReader->next();
    }
    return tokens;
}
