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

#ifndef TEXTTOKENMANAGER_H
#define TEXTTOKENMANAGER_H

#include "tokenmanager.h"

namespace HuwInterpreter {
    namespace Tokens {
        class TextTokenManager : public TokenManager
        {
        private:
            std::vector<std::shared_ptr<IO::FileLine>> lines;
            std::vector<std::shared_ptr<IO::FileLine>>::iterator it;
        public:
            TextTokenManager(std::string input);
            std::shared_ptr<IO::FileLine> getCurrent();
            std::shared_ptr<IO::FileLine> getNext();
            std::shared_ptr<IO::FileLine> getPrev();
            void next();
            void prev();
            std::shared_ptr<IO::FileLine> peak();
            bool isEnd();
            bool isEmpty();
        };
    }
}

#endif // TEXTTOKENMANAGER_H
