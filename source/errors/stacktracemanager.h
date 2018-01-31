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

#include <memory>
#include <queue>

#ifndef STACKTRACEMANAGER_H
#define STACKTRACEMANAGER_H

#include "stacktrace.h"

namespace HuwInterpreter {
    namespace ErrorReporting {
        class StackTraceManager
        {
        private:
            unsigned int queueSize = 20;
            bool queueLimit;
            std::deque<std::shared_ptr<StackTrace>> stackTraceQueue;
        public:
            StackTraceManager();
            StackTraceManager(unsigned int queueSize);
            StackTraceManager(unsigned int queueSize, bool queueLimit);
            ~StackTraceManager();
            void push(std::shared_ptr<StackTrace> stackTrace);
            void pop();
            std::deque<std::shared_ptr<StackTrace>> get();
        };
    }
}

#endif // STACKTRACEMANAGER_H
