#ifndef ARRAYGET_H
#define ARRAYGET_H

#include "functions/function.h"

class ArrayGet : public Function
{
public:
    ArrayGet()
    {
        name = "arrayGet";
    }

    std::shared_ptr<Variable> run(std::shared_ptr<Token> token,
                                  std::shared_ptr<Scope> scope,
                                  std::vector<std::shared_ptr<Node>> variables);
};

#endif // ARRAYGET_H
