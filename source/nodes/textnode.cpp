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

#include "textnode.h"

namespace HuwInterpreter {
    namespace Nodes {
        TextNode::TextNode(std::shared_ptr<Passable> passable, std::shared_ptr<Tokens::Token> token, std::string value)
            : Node("TextNode", passable, token)
        {
            ErrorReporting::Debug::print("TextNode");
            this->variableTypeFactory = std::make_shared<Variables::VariableTypeFactory>(passable);
            this->value = variableTypeFactory->newVariable(Helpers::TypeDetector::getType(value));
            this->value->setValue(value);
        }

        NodeType TextNode::getType()
        {
            return TEXTNODETYPE;
        }

        std::shared_ptr<Variables::Variable> TextNode::execute(std::shared_ptr<Variables::Scope> globalScope, std::shared_ptr<Variables::Scope> scope)
        {
            ErrorReporting::Debug::print("TextNode");
            if (passable->getErrorManager()->count() > 0)
            {
                return nullVariable;
            }
            if (scope->getReturnValue() != nullptr)
            {
                return scope->getReturnValue();
            }
            return value;
        }

        std::string TextNode::toString()
        {
            if (value != nullptr)
            {
                std::string output = escapedOutput->output(value->toString());
                return "\"" + output + "\"";
            }
            return "";
        }
    }
}
