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

#include "lineinfo.h"

namespace HuwInterpreter {
    namespace Tokens {
        LineInfo::LineInfo(std::string file, long long lineNumber, long long charNumber)
        {
            this->file = file;
            this->lineNumber = lineNumber;
            this->charNumber = charNumber;
        }

        std::string LineInfo::getFile()
        {
            return file;
        }

        void LineInfo::setFile(std::string file)
        {
            this->file = file;
        }

        long long LineInfo::getLineNumber()
        {
            return lineNumber;
        }

        void LineInfo::setLineNumber(long long lineNumber)
        {
            this->lineNumber = lineNumber;
        }

        long long LineInfo::getCharNumber()
        {
            return charNumber;
        }

        void LineInfo::setCharNumber(long long charNumber)
        {
            this->charNumber = charNumber;
        }
    }
}
