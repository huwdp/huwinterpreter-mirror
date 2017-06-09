#ifndef INCREMENTNODE_H
#define INCREMENTNODE_H

#include "node.h"

class IncrementNode : public Node
{
private:
    std::shared_ptr<Node> node;
public:
    IncrementNode(std::shared_ptr<Token> token, std::shared_ptr<Node> node);
    std::shared_ptr<Variable> execute(std::shared_ptr<Scope> scope);
};

#endif // INCREMENTNODE_H
