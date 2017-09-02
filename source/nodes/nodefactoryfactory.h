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
