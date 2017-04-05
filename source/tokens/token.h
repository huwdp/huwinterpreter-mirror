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

#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <memory>
#include "../types/tokentypes.h"
#include "../tokens/token.h"
#include "../tokens/lineinfo.h"

class Token
{
private:
    std::string content;
    TokenType type;
    std::shared_ptr<LineInfo> lineInfo;
public:
    Token(std::string content, std::shared_ptr<LineInfo> lineInfo);
    Token(std::string content, TokenType type, std::shared_ptr<LineInfo> lineInfo);
    ~Token();
    std::string getContent();
    TokenType getType();
    void setType(TokenType type);
    std::shared_ptr<LineInfo> getLineInfo();
    void setLineInfo(std::shared_ptr<LineInfo> lineInfo);
};

#endif // TOKEN_H
