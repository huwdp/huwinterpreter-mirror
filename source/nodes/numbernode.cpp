/*
    HuwInterpreter is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    HuwInterpreter is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with HuwInterpreter.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "numbernode.h"

NumberNode::NumberNode(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token, std::string value)
    : Node("NumberNode", passable, token)
{
    variableTypeFactory = std::make_shared<VariableTypeFactory>(passable);
    this->value = variableTypeFactory->newVariable(TypeDetector::getType(value));
    this->value->setValue(value);
    Debug::print("NumberNode");
}

NodeType NumberNode::getType()
{
    return NUMBERNODETYPE;
}

std::shared_ptr<Variable> NumberNode::execute(std::shared_ptr<Scope> globalScope, std::shared_ptr<Scope> scope)
{
    Debug::print("NumberNode");
    if (passable->getErrors()->count() > 0)
    {
        return null;
    }
    if (scope->getReturnValue() != nullptr)
    {
        return scope->getReturnValue();
    }
    return value;
}

std::string NumberNode::toString()
{
    if (value->getType() == STRING)
    {
        std::string output = escapedOutput->output(value->toString());
        return "\"" + output + "\"";
    }
    return value->toString();
}
