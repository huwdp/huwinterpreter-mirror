#include "isarraytype.h"

std::shared_ptr<Variable> IsArrayType::run(std::shared_ptr<Token> token,
                                        std::shared_ptr<Scope> scope,
                                        std::vector<std::shared_ptr<Node>> variables)
{
    std::shared_ptr<Variable> returnNode;
    if (variables.size() == 1)
    {
        std::shared_ptr<Node> node = variables.at(0);
        std::shared_ptr<Variable> var = node->execute(scope);
        if (node != nullptr)
        {
            if (var->getType() == ARRAY)
            {
                returnNode = std::make_shared<NumberVariable>(true);
            }
            returnNode = std::make_shared<NumberVariable>(false);
        }
    }
    else
    {
        Errors::add(std::make_shared<Error>(FUNCTION_ERROR, "isIntType function requires one arguments", token));
    }
    return returnNode;
}
