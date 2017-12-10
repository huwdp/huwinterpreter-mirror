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

#ifndef FILELINE_H
#define FILELINE_H

#include <string>

namespace HuwInterpreter {
    namespace IO {
        class FileLine
        {
        private:
            char content;
            long long lineNumber;
        public:
            FileLine(char content, long long lineNumber);
            char getContent();
            void setContent(char content);
            long long getLineNumber();
            void setLineNumber(long long lineNumber);
        };
    }
}

#endif // FILELINE_H
