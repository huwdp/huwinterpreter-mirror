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

#ifndef IERRORS_H
#define IERRORS_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

class IErrors
{
private:
    std::vector<std::shared_ptr<Error>> errorsList;
public:
    IErrors();
    ~IErrors();
    void add(std::string error);
    void add(std::string error, long int lineNumnber);
    void add(std::string error, long int lineNumber, long int charNumber);
    void add(std::make_shared<Error> error);
    void remove(std::make_shared<Error> error);
    void remove(std::string message);
    void remove(long int lineNumnber);
    std::vector<std::shared_ptr<Error>> get();
    void set(std::vector<std::shared_ptr<Error>> errors);
    void print();
};

#endif // IERRORS
