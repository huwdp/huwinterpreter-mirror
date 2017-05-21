#ifndef SCOPE_H
#define SCOPE_H

#include "nodes/node.h"
#include "variables/variables.h"
#include <memory>

class Node;

class Scope
{
private:
    std::shared_ptr<Variable> returnValue;
    std::shared_ptr<Variables> variables;
public:
    Scope();
    Scope(std::shared_ptr<Variables> parent);
    std::shared_ptr<Variables> getVariables();
    void setVariables(std::shared_ptr<Variables> variables);
    std::shared_ptr<Variable> getReturnValue();
    void setReturnValue(std::shared_ptr<Variable> value);
};

#endif // SCOPE_H
