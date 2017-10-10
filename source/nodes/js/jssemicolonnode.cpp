#include "jssemicolonnode.h"

JSSemicolonNode::JSSemicolonNode(std::shared_ptr<Passable> passable, std::shared_ptr<Node> node)
    : SemicolonNode(passable, node)
{

}

std::string JSSemicolonNode::toString()
{
    return SemicolonNode::toString();
}
