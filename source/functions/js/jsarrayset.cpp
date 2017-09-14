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

#include "jsarrayset.h"

std::string JSArraySet::toString(std::vector<std::shared_ptr<Node>> variables)
{
    if (variables.size() == 3)
    {
        return variables.at(0)->toString() + "[" + variables.at(1)->toString() + "]=" + variables.at(2);
    }
    return "";
}
