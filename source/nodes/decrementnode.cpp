#include "decrementnode.h"

DecrementNode::DecrementNode(std::shared_ptr<Token> token, std::shared_ptr<Node> node) : Node(token)
{
    this->node = node;
    Debug::print("Decrement");
}

std::shared_ptr<Variable> DecrementNode::execute(std::shared_ptr<Scope> scope)
{
    Debug::print("Decrement");
    if (scope->getReturnValue() != nullptr)
    {
        return scope->getReturnValue();
    }
    if (node != nullptr)
    {
        std::shared_ptr<Variable> n = node->execute(scope);
        if (n == nullptr)
        {
            Errors::add(std::make_shared<Error>(ERROR, "Invalid expression", token));
            return null;
        }
        return n->decrement();
    }
    Debug::print("Could not increment.");
    return null;
}
