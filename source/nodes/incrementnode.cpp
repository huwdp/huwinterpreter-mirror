#include "incrementnode.h"

IncrementNode::IncrementNode(std::shared_ptr<Token> token, std::shared_ptr<Node> node) : Node(token)
{
    this->node = node;
    Debug::print("Increment");
}

std::shared_ptr<Variable> IncrementNode::execute(std::shared_ptr<Scope> scope)
{
    Debug::print("Increment");
    if (node != nullptr)
    {
        std::shared_ptr<Variable> n = node->execute(scope);
        if (n == nullptr)
        {
            Errors::add(std::make_shared<Error>(ERROR, "Invalid expression", token));
            return null;
        }
        return n->increment();
    }
    Debug::print("Could not increment.");
    return null;
}
