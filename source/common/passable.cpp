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

#include "passable.h"

namespace HuwInterpreter {
    Passable::Passable()
    {
        this->errorManager = std::make_shared<ErrorManager>();
        this->errorFactory = std::make_shared<ErrorFactory>();
    }

    Passable::Passable(std::shared_ptr<ErrorManager> errorManager, std::shared_ptr<ErrorReporting::ErrorFactory> errorFactory)
    {
        this->errorManager = errorManager;
        this->errorFactory = errorFactory;
    }

    std::shared_ptr<ErrorManager> Passable::getErrorManager()
    {
        return errorManager;
    }

    void Passable::setErrorManager(std::shared_ptr<ErrorManager> errorManager)
    {
        this->errorManager = std::move(errorManager);
    }

    std::shared_ptr<ErrorFactory> Passable::getErrorFactory()
    {
        return errorFactory;
    }

    void Passable::setErrorFactory(std::shared_ptr<ErrorFactory> errorFactory)
    {
        this->errorFactory = std::move(errorFactory);
    }
}
