#include "jssemicolonnode.h"

JSSemicolonNode::JSSemicolonNode(std::shared_ptr<Passible> passible, std::shared_ptr<Node> node)
    : SemicolonNode(passible, node)
{

}

std::string JSSemicolonNode::toString()
{
    return SemicolonNode::toString();
}
