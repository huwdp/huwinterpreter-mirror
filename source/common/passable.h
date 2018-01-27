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

#ifndef PASSABLE_H
#define PASSABLE_H

#include "errors/errors.h"
#include "errors/errorfactory.h"
#include "errors/stacktracemanager.h"

namespace HuwInterpreter {

    using namespace ErrorReporting;

    class Passable
    {
    private:
        std::shared_ptr<ErrorManager> errorManager;
        std::shared_ptr<ErrorFactory> errorFactory;
        std::shared_ptr<StackTraceManager> stackTraceManager;
    public:
        Passable();
        Passable(std::shared_ptr<ErrorManager> errorManager,
                 std::shared_ptr<ErrorFactory> errorFactory,
                 std::shared_ptr<StackTraceManager> stackTraceManager);
        std::shared_ptr<ErrorManager> getErrorManager();
        void setErrorManager(std::shared_ptr<ErrorManager> errorManager);
        std::shared_ptr<ErrorFactory> getErrorFactory();
        void setErrorFactory(std::shared_ptr<ErrorFactory> errorFactory);
        std::shared_ptr<StackTraceManager> getStackTraceManager();
        void setStackTraceManager(std::shared_ptr<StackTraceManager> stackTraceManager);
    };
}

#endif // PASSABLE_H
