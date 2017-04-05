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

#include "isnumeric.h"

#define ISNUMERIC_C
#ifdef ISNUMBERIC_C

bool isNumeric(std::string input)
{
    try
    {
        std::stod(input);
    }
    catch (std::invalid_argument& e)
    {
        throw std::invalid_argument(e.what());
    }
    catch (const std::out_of_range e)
    {
        throw std::out_of_range(e.what());
    }
    return true;
}
#endif
