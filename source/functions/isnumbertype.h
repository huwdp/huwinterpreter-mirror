#ifndef ISNUMBER_H
#define ISNUMBER_H

#include "function.h"

class IsNumberType : public Function
{
public:
    IsNumberType()
    {
        name = "isNumber";
    }

    std::shared_ptr<Variable> run(std::shared_ptr<Token> token,
                                  std::shared_ptr<Scope> scope,
                                  std::vector<std::shared_ptr<Node>> variables);
};

#endif // ISNUMBER_H
