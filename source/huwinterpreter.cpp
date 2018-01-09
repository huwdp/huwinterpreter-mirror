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

namespace  HuwInterpreter {

    Interpreter::Interpreter()
    {
        std::shared_ptr<NodeFactoryFactory> nodeFactoryFactory = std::make_shared<NodeFactoryFactory>();
        nodeFactory = nodeFactoryFactory->build(HUWCODE);
        scanner = std::make_shared<Scanner>();
    }

    void Interpreter::executeFile(std::string fileLocation)
    {
        std::ifstream file (fileLocation.c_str());
        bool exists = static_cast<bool>(file);
        if (!exists)
        {
            std::string errorMessage = "Could not find file \"";
            errorMessage.append(fileLocation);
            errorMessage.append("\"");
            return;
        }
        execute(parseFile(fileLocation));
    }

    void Interpreter::execute(std::vector<std::shared_ptr<Token>> tokens)
    {
        std::unique_ptr<Parser> parser(new Parser(tokens, nodeFactory));
        parser->execute();
    }

    std::string Interpreter::toString(std::vector<std::shared_ptr<Token>> tokens)
    {
        std::unique_ptr<Parser> parser(new Parser(tokens, nodeFactory));
        return parser->toString();
    }

    std::vector<std::shared_ptr<Token>> Interpreter::parseFile(std::string fileLocation)
    {
        std::vector<std::shared_ptr<Token>> tokens;
        std::ifstream file (fileLocation.c_str());
        bool exists = static_cast<bool>(file);
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

    std::vector<std::shared_ptr<Token>> Interpreter::parseText(std::string text)
    {
        std::shared_ptr<TokenManager> textTokenManager = std::make_shared<TextTokenManager>(text);
        return scanner->tokenize(textTokenManager);
    }
}
