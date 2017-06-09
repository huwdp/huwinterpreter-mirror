#ifndef ARRAYSET_H
#define ARRAYSET_H

#include "functions/function.h"

class ArraySet : public Function
{
public:
    ArraySet()
    {
        name = "arraySet";
    }

    std::shared_ptr<Variable> run(std::shared_ptr<Token> token,
                                  std::shared_ptr<Scope> scope,
                                  std::vector<std::shared_ptr<Node>> variables);
};

#endif // ARRAYSET_H
