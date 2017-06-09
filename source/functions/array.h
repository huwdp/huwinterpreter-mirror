#ifndef ARRAY_H
#define ARRAY_H

#include "functions/function.h"
#include "variables/hashtablevariable.h"

class Array : public Function
{
public:
    Array()
    {
        name = "array";
    }

    std::shared_ptr<Variable> run(std::shared_ptr<Token> token,
                                  std::shared_ptr<Scope> scope,
                                  std::vector<std::shared_ptr<Node>> variables);
};

#endif // ARRAY_H
