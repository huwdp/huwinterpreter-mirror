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

#include "dirfunction.h"

namespace HuwInterpreter {
    namespace Functions {
        DirFunction::DirFunction(std::shared_ptr<Passable> passable)
            : Function(passable)
        {
            setName("dir");
        }

        std::shared_ptr<Variable> DirFunction::execute(std::shared_ptr<Tokens::Token> token, std::shared_ptr<Scope> globalScope,
                                                 std::shared_ptr<Scope> scope,
                                                 std::vector<std::shared_ptr<Nodes::Node>> arguments)
        {
            std::shared_ptr<Variable> returnNode;
            if (arguments.size() == 1)
            {
                std::shared_ptr<Nodes::Node> node1 = arguments.at(0);

                if (node1 != nullptr)
                {
                    std::shared_ptr<Variable> var = node1->execute(globalScope, scope);
                    if (var == nullptr )
                    {
                        passable->getErrorManager()->add(passable->getErrorFactory()->invalidArgument(token, RUNTIME_ERROR, name));
                        return nullVariable;
                    }
                    std::shared_ptr<HashTableVariable> output = std::make_shared<HashTableVariable>(passable);
                    DIR* dirp = opendir(var->toString().c_str());
                    struct dirent * dp;
                    while ((dp = readdir(dirp)) != NULL) {
                       output->add(std::make_shared<StringVariable>(passable, dp->d_name), token);
                    }
                    closedir(dirp);
                    return output;
                }
                else
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->invalidArgument(token, RUNTIME_ERROR, name));
                    return nullVariable;
                }
            }
            else
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->requiresArguments(token, name, "", 2));
            }
            return returnNode;
        }
    }
}
