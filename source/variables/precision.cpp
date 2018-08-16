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

#include "precision.h"

namespace HuwInterpreter {
    namespace Helpers {
        Precision::Precision()
        {}

        bool Precision::isSafeInteger(double value = 0.0)
        {
            if (value >= -9007199254740991 && value <= 9007199254740991)
            {
                return true;
            }
            return false;
        }

        bool Precision::isSafeInteger(long long value = 0)
        {
            if (value >= -9007199254740991 && value <= 9007199254740991)
            {
                return true;
            }
            return false;
        }

        Types::VarType Precision::getType(double value = 0.0)
        {
            if ((fmod(value,1) == 0.0) || (fabs(value - round(value)) < 0.000000001))
            {
                return Types::VarType::INTEGER;
            }
            return Types::VarType::DOUBLE;
        }
    }
}
