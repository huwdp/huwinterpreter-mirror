#ifndef ISARRAY_H
#define ISARRAY_H

#include "function.h"

class IsArrayType : public Function
{
public:
    IsArrayType()
    {
        name = "isArray";
    }

    std::shared_ptr<Variable> run(std::shared_ptr<Token> token,
                                            std::shared_ptr<Scope> scope,
                                            std::vector<std::shared_ptr<Node>> variables);
};

#endif // ISARRAY_H
