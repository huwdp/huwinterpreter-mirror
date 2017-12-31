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

#ifndef TOKENMANAGER_H
#define TOKENMANAGER_H

#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include "io/fileline.h"
#include "types/tokentypes.h"

namespace HuwInterpreter {
    namespace Tokens {
        class TokenManager
        {
        protected:
            std::shared_ptr<IO::FileLine> nullToken;
        public:
            virtual std::shared_ptr<IO::FileLine> getCurrent() = 0;
            virtual std::shared_ptr<IO::FileLine> getNext() = 0;
            virtual std::shared_ptr<IO::FileLine> getPrev() = 0;
            virtual void next() = 0;
            virtual void prev() = 0;
            virtual std::shared_ptr<IO::FileLine> peak() = 0;
            virtual bool isEnd() = 0;
            virtual bool isEmpty() = 0;
        };
    }
}

#endif // TOKENMANAGER_H
