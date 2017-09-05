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

#include <iostream>
#include <string>
#include <memory>
#include "parser/parser.h"
#include "tokens/token.h"
#include "tokens/scanner.h"
#include "io/io.h"
#include "errors/errors.h"
#include "tokens/filetokenmanager.h"
#include "huwinterpreter.h"

void printHelp(int argc, char* argv[])
{
    if (argc > 1)
    {
        std::cerr << "1. Usage: " << argv[0] << " [filename] to run file." << std::endl;
        std::cerr << "2. Usage: " << argv[0] << " -t [text] to run text." << std::endl;
        std::cerr << "3. Usage: " << argv[0] << " --hc [filename] for HuwCode formatter" << std::endl;
        std::cerr << "4. Usage: " << argv[0] << " -h for help." << std::endl;
    }
    else
    {
        std::cerr << "1. Usage: [filename] to run file." << std::endl;
        std::cerr << "2. Usage: -t [text] to run text." << std::endl;
        std::cerr << "3. Usage: --hc for HuwCode formatter" << std::endl;
        std::cerr << "4. Usage: -h for help." << std::endl;
    }
}

int main(int argc, char* argv[])
{
    std::shared_ptr<HuwInterpreter> interpreter = std::make_shared<HuwInterpreter>();
    if (argc < 2)
    {
        printHelp(argc, argv);
        return 1;
    }
    std::string argument = argv[1];

    if (argument == "-h")
    {
        printHelp(argc, argv);
    }
    else if (argument == "-t")
    {
        std::string text = "";
        std::cout << ">>> ";
        std::getline (std::cin,text);
        while (text != "exit")
        {
            interpreter->runText(text);
            std::cout << ">>>";
            std::getline (std::cin,text);
        }
    }
    else if (argument == "--hc" && argc == 3)
    {
        std::shared_ptr<Node> node = interpreter->parseFile(argv[2]);
        if (node != nullptr)
        {
            std::cout << node->toString() << std::endl;
        }
    }
    else
    {
        interpreter->runFile(argument);
    }
    std::exit(0);
}
