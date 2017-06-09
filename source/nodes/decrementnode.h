#ifndef DECREMENTNODE_H
#define DECREMENTNODE_H

#include "node.h"

class DecrementNode : public Node
{
private:
    std::shared_ptr<Node> node;
public:
    DecrementNode(std::shared_ptr<Token> token, std::shared_ptr<Node> node);
    std::shared_ptr<Variable> execute(std::shared_ptr<Scope> scope);
};

#endif // DECREMENTNODE_H
