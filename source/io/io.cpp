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

#include "io.h"

namespace HuwInterpreter {
    namespace IO {
        std::string IO::read(std::string file)
        {
            std::string output;
            std::string line;
            std::ifstream stream(file);

            if (stream.is_open())
            {
                while (std::getline(stream,line))
                {
                    output.append(line);
                }
                stream.close();
            }
            return output;
        }

        bool IO::write(std::string fileLocation, std::string content)
        {
            std::ofstream file(fileLocation);
            if (file.is_open())
            {
                if (file.fail())
                {
                    return false;
                }
                file << content;
                file.close();
                return true;
            }
            return false;
        }

        bool IO::append(std::string fileLocation, std::string content)
        {
            std::ofstream file(fileLocation);
            if (file.is_open())
            {
                file.open (fileLocation, std::ios_base::app);
                if (file.fail())
                {
                    return false;
                }
                file << content;
                file.close();
                return true;
            }
            return false;
        }

        bool IO::fileExists(std::string fileLocation)
        {
            std::ifstream file(fileLocation);
            return file.good();
        }
    }
}
