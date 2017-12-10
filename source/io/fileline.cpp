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

#include "fileline.h"

namespace HuwInterpreter {
    namespace IO {
        FileLine::FileLine(char content, long long lineNumber)
        {
            this->content = content;
            this->lineNumber = lineNumber;
        }

        char FileLine::getContent()
        {
            return content;
        }

        void FileLine::setContent(char content)
        {
            this->content = content;
        }

        long long FileLine::getLineNumber()
        {
            return lineNumber;
        }

        void FileLine::setLineNumber(long long lineNumber)
        {
            this->lineNumber = lineNumber;
        }
    }
}
