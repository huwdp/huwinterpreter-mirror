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

#include "errors.h"

namespace HuwInterpreter {
    namespace ErrorReporting {
        ErrorManager::~ErrorManager()
        {
            errorList.clear();
        }

        void ErrorManager::add(std::string message)
        {
            errorList.push_back(std::make_shared<Error>(ERROR, message));
        }

        void ErrorManager::add(std::shared_ptr<Error> error)
        {
            errorList.push_back(error);
        }

        void ErrorManager::removeAll()
        {
            errorList.clear();
        }

        std::vector<std::shared_ptr<Error>> ErrorManager::get()
        {
            return errorList;
        }

        void ErrorManager::set(std::vector<std::shared_ptr<Error>> ErrorManager)
        {
            errorList = ErrorManager;
        }

        void ErrorManager::print()
        {
            for (std::vector<std::shared_ptr<Error>>::iterator it = errorList.begin(); it != errorList.end(); ++it)
            {
                std::string value = (*it)->getMessage();
                std::cout << value << std::endl;
            }
        }

        long long ErrorManager::count()
        {
            return errorList.size();
        }
    }
}
