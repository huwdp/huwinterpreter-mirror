#include "unarynotnode.h"

UnaryNotNode::UnaryNotNode(std::shared_ptr<Token> token, std::shared_ptr<Node> node)
    : Node(token)
{
    this->node = node;
}

std::shared_ptr<Variable> UnaryNotNode::execute(std::shared_ptr<Scope> scope)
{
    Debug::print("UnaryNot");
    if (scope->getReturnValue() != null)
    {
        return scope->getReturnValue();
    }
    if (node != nullptr)
    {
        std::shared_ptr<Variable> var = node->execute(scope);
        if (var != nullptr)
        {
            if (var->toBool())
            {
                return std::make_shared<NumberVariable>(0.0);
            }
            else
            {
                return std::make_shared<NumberVariable>(1.0);
            }
        }
    }
    return null;
}
