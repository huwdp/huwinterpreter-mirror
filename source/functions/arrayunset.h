#ifndef ARRAYUNSET_H
#define ARRAYUNSET_H

#include "functions/function.h"

class ArrayUnset : public Function
{
public:
    ArrayUnset()
    {
        name = "arrayUnset";
    }

    std::shared_ptr<Variable> run(std::shared_ptr<Token> token,
                                  std::shared_ptr<Scope> scope,
                                  std::vector<std::shared_ptr<Node>> variables);
};

#endif // ARRAYUNSET_H
