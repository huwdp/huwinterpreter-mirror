#ifndef UNARYMINUSNODE_H
#define UNARYMINUSNODE_H

#include "node.h"

class UnaryMinusNode : public Node
{
private:
    std::shared_ptr<Node> node;
public:
    UnaryMinusNode(std::shared_ptr<Token> token, std::shared_ptr<Node> node);
    std::shared_ptr<Variable> execute(std::shared_ptr<Scope> scope);
};

#endif // UNARYMINUSNODE_H
