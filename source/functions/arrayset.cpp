#include "arrayset.h"

std::shared_ptr<Variable> ArraySet::run(std::shared_ptr<Token> token,
                              std::shared_ptr<Scope> scope,
                              std::vector<std::shared_ptr<Node>> variables)
{
    std::shared_ptr<Variable> answer;
    if (variables.size() == 3)
    {
        std::shared_ptr<Node> node1 = variables.at(0);
        std::shared_ptr<Node> node2 = variables.at(1);
        std::shared_ptr<Node> node3 = variables.at(2);

        if (node1 == nullptr || node2 == nullptr || node3 == nullptr)
        {
            return null;
        }

        std::shared_ptr<Variable> var1 = node1->execute(scope);
        std::shared_ptr<Variable> var2 = node2->execute(scope);
        std::shared_ptr<Variable> var3 = node3->execute(scope);

        if (var1 == nullptr || var2 == nullptr || var3 == nullptr)
        {
            return null;
        }

        if (var1->getType() != ARRAY)
        {
            Errors::add(std::make_shared<Error>(RUNTIME_ERROR, "First parameter is not a type of ARRAY"));
            return null;
        }

        var1->set(var2->toString(), var3);

        // Todo
        // Maybe return true here
    }
    else
    {
        Errors::add(std::make_shared<Error>(FUNCTION_ERROR, "ArrayGet function requires three argument", token));
    }
    return answer;
}
