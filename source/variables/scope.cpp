#include "scope.h"

Scope::Scope()
{
    variables = std::make_shared<Variables>(false);
}

Scope::Scope(std::shared_ptr<Variables> parent)
{
    std::shared_ptr<Variables> child = std::make_shared<Variables>(true);
    child->setParent(parent);
    variables = child;
}

std::shared_ptr<Variables> Scope::getVariables()
{
    return variables;
}

void Scope::setVariables(std::shared_ptr<Variables> variables)
{
    this->variables = variables;
}

std::shared_ptr<Variable> Scope::getReturnValue()
{
    return returnValue;
}

void Scope::setReturnValue(std::shared_ptr<Variable> value)
{
    this->returnValue = value;
}
