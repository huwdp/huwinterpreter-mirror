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

#include "stacktracemanager.h"

namespace HuwInterpreter {
    namespace ErrorReporting {
        StackTraceManager::StackTraceManager()
        {
            this->queueSize = 20;
        }

        StackTraceManager::StackTraceManager(unsigned int queueSize)
        {
            this->queueSize = queueSize;
        }

        StackTraceManager::~StackTraceManager()
        {
            stackTraceQueue.clear();
        }

        void StackTraceManager::enqueue(std::shared_ptr<StackTrace> stackTrace)
        {
            stackTraceQueue.push_front(stackTrace);

            if (stackTraceQueue.size() >= queueSize)
            {
                stackTraceQueue.pop_back();
            }
        }

        void StackTraceManager::dequeue()
        {
            if (stackTraceQueue.size() > 0)
            {
                stackTraceQueue.pop_front();
            }
        }

        std::deque<std::shared_ptr<StackTrace>> StackTraceManager::get()
        {
            return stackTraceQueue;
        }
    }
}
