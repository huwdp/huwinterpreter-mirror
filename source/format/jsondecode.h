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


#ifndef JSONDECODE_H
#define JSONDECODE_H

#include <string>
#include "variables/variable.h"
#include "variables/doublevariable.h"
#include "variables/stringvariable.h"
#include "variables/hashtablevariable.h"
#include "tokens/tokens.h"
#include "tokens/token.h"

class JSONDecode
{
private:
    std::string::iterator it;
    std::string::iterator end;
    std::string text = "";
public:
    JSONDecode(std::string text);

};

#endif // JSONDECODE_H
*/
