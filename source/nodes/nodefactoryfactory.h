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

#ifndef NODEFACTORYFACTORY_H
#define NODEFACTORYFACTORY_H

#include "nodefactory.h"
#include "huwcodenodefactory.h"
#include "js/jsnodefactory.h"

enum NodeFactoryType {HUWCODE, JAVASCRIPT };

class NodeFactoryFactory
{
public:
    NodeFactoryFactory();
    std::shared_ptr<NodeFactory> build(NodeFactoryType type);
};

#endif // NODEFACTORYFACTORY_H
