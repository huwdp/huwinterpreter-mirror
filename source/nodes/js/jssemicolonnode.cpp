#include "jssemicolonnode.h"

JSSemicolonNode::JSSemicolonNode(std::shared_ptr<Node> node)
    : SemicolonNode(node)
{

}

std::string JSSemicolonNode::toString()
{
    return SemicolonNode::toString();
}
