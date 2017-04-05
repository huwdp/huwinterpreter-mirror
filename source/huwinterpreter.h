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

#ifndef HUWINTERPRETER_H
#define HUWINTERPRETER_H

#include <iostream>
#include <string>
#include <memory>
#include "parser/parser.h"
#include "tokens/token.h"
#include "tokens/scanner.h"
#include "io/io.h"
#include "errors/errors.h"
#include "tokens/filetokenmanager.h"
#include "tokens/texttokenmanager.h"

class HuwInterpreter
{
private:
    std::shared_ptr<Scanner> scanner;
    std::shared_ptr<FileTokenManager> fileTokenManager;
    std::vector<std::shared_ptr<Token>> tokens;
    std::unique_ptr<Parser> parser;
public:
    HuwInterpreter();
    void runFile(std::string fileLocation);
    void runText(std::string text);
    void runTokens(std::vector<std::shared_ptr<Token>>);
};

#endif // HUWINTERPRETER_H
