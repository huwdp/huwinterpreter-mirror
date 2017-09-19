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
    std::shared_ptr<NodeFactoryFactory> nodeFactoryFactory = std::make_shared<NodeFactoryFactory>();
    nodeFactory = nodeFactoryFactory->build(HUWCODE);
    scanner = std::make_shared<Scanner>();
}

void HuwInterpreter::executeFile(std::string fileLocation)
{
    std::ifstream file (fileLocation.c_str());
    bool exists = (bool)file;
    if (!exists)
    {
        std::string errorMessage = "Could not find file \"";
        errorMessage.append(fileLocation);
        errorMessage.append("\"");
        return;
    }
    execute(parseFile(fileLocation));
}

void HuwInterpreter::execute(std::vector<std::shared_ptr<Token>> tokens)
{
    std::unique_ptr<Parser> parser(new Parser(tokens, nodeFactory));
    parser->execute();
    Errors::print();
    Errors::removeAll();
}

std::string HuwInterpreter::toString(std::vector<std::shared_ptr<Token>> tokens)
{
    std::unique_ptr<Parser> parser(new Parser(tokens, nodeFactory));
    return parser->toString();
}

std::vector<std::shared_ptr<Token>> HuwInterpreter::parseFile(std::string fileLocation)
{
    std::vector<std::shared_ptr<Token>> tokens;
    std::ifstream file (fileLocation.c_str());
    bool exists = (bool)file;
    if (!exists)
    {
        std::string errorMessage = "Could not find file \"";
        errorMessage.append(fileLocation);
        errorMessage.append("\"");
        return tokens;
    }
    std::shared_ptr<FileTokenManager> fileTokenManager = std::make_shared<FileTokenManager>(fileLocation);
    return scanner->tokenize(fileTokenManager);
}

std::vector<std::shared_ptr<Token>> HuwInterpreter::parseText(std::string text)
{
    std::shared_ptr<TokenManager> textTokenManager = std::make_shared<TextTokenManager>(text);
    return scanner->tokenize(textTokenManager);
}
