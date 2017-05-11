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

#include "huwinterpreter.h"

HuwInterpreter::HuwInterpreter()
{
    scanner = std::make_shared<Scanner>();
}

void HuwInterpreter::runFile(std::string fileLocation)
{
    std::ifstream file (fileLocation.c_str());
    bool exists = (bool)file;
    if (!exists)
    {
        std::string errorMessage = "Could not find file \"";
        errorMessage.append(fileLocation);
        errorMessage.append("\"");
        Errors::add(std::make_shared<Error>(ERROR, errorMessage));
        Errors::print();
        return;
    }

    std::shared_ptr<FileTokenManager> fileTokenManager = std::make_shared<FileTokenManager>(fileLocation);
    std::vector<std::shared_ptr<Token>> tokens = scanner->tokenize(fileTokenManager);
    runTokens(tokens);
}

void HuwInterpreter::runText(std::string text)
{
    std::shared_ptr<TokenManager> textTokenManager = std::make_shared<TextTokenManager>(text);
    std::vector<std::shared_ptr<Token>> tokens = scanner->tokenize(textTokenManager);
    runTokens(tokens);
}

void HuwInterpreter::runTokens(std::vector<std::shared_ptr<Token>> tokens)
{
    std::unique_ptr<Parser> parser(new Parser(tokens));
    parser->program();
    Errors::print();
    Errors::removeAll();
}
