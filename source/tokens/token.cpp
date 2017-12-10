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

#include "token.h"

namespace HuwInterpreter {
    namespace Tokens {
        Token::Token(std::string content, std::shared_ptr<LineInfo> lineInfo)
        {
            this->content = content;
            type = Types::TokenType::WORD;
            this->lineInfo = lineInfo;
        }

        Token::Token(std::string content, Types::TokenType type, std::shared_ptr<LineInfo> lineInfo)
        {
            this->content = content;
            this->type = type;
            this->lineInfo = lineInfo;
        }

        std::string Token::getContent()
        {
            return content;
        }

        Types::TokenType Token::getType()
        {
            return type;
        }

        void Token::setType(Types::TokenType type)
        {
            this->type = type;
        }

        std::shared_ptr<LineInfo> Token::getLineInfo()
        {
            return lineInfo;
        }

        void Token::setLineInfo(std::shared_ptr<LineInfo> lineInfo)
        {
            this->lineInfo = lineInfo;
        }
    }
}
