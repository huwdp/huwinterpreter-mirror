#include "unaryminusnode.h"

UnaryMinusNode::UnaryMinusNode(std::shared_ptr<Token> token, std::shared_ptr<Node> node)
    : Node(token)
{
    this->node = node;
}

std::shared_ptr<Variable> UnaryMinusNode::execute(std::shared_ptr<Scope> scope)
{
    Debug::print("UnaryMinusNode");
    if (scope->getReturnValue() != nullptr)
    {
        return scope->getReturnValue();
    }
    if (node != nullptr)
    {
        std::shared_ptr<Variable> value = node->execute(scope);
        if (value != nullptr)
        {
            return value->mul(std::make_shared<IntegerVariable>(-1));
        }
    }
    return null;
}
