#ifndef IFEQUAL_H
#define IFEQUAL_H
#include <string.h>
#include <stdio.h>
#include <string>
#include "instruction.h"
#include "../variables/variable.h"


class Variable;

class IfEqual : public Instruction
{
private:
    std::shared_ptr<Variable> a;
    std::shared_ptr<Variable> b;
public:
    IfEqual(std::shared_ptr<Variable> a, std::shared_ptr<Variable> b)
    {
        this->a = a;
        this->b = b;
    }

    std::shared_ptr<Variable> execute()
    {
        if (a != nullptr && b != nullptr)
        {
            a->ifEqual(b);
        }
        else
        {
            cout << "Error: Could not find variable" << endl;
        }
        std::shared_ptr<FileLine> null;
        return null;
    }
};
#endif
