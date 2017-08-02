#ifndef ISSTRING_H
#define ISSTRING_H

#include "function.h"

class IsStringType : public Function
{
public:
    IsStringType()
    {
        name = "isString";
    }

    std::shared_ptr<Variable> run(std::shared_ptr<Token> token,
                                  std::shared_ptr<Scope> scope,
                                  std::vector<std::shared_ptr<Node>> variables);
};

#endif // ISSTRING_H
