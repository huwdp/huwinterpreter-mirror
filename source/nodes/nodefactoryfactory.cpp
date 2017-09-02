#include "nodefactoryfactory.h"

NodeFactoryFactory::NodeFactoryFactory()
{
}

std::shared_ptr<NodeFactory> NodeFactoryFactory::build(NodeFactoryType type)
{
    std::shared_ptr<NodeFactory> nodeFactory;
    switch (type)
    {
    case HUWCODE:
        nodeFactory = std::make_shared<HuwCodeNodeFactory>();
        break;
    case JAVASCRIPT:
        nodeFactory = std::make_shared<JSNodeFactory>();
        break;
    }
    return nodeFactory;
}
