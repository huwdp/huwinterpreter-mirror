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

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "tokens/token.h"
#include "tokens/tokens.h"
#include <iostream>
#include <sstream>
#include <memory>

#include "errors/errors.h"
#include "errors/error.h"
#include "nodes/node.h"

#include "nodes/nodefactory.h"

#include "nodes/ifnode.h"
#include "nodes/whilenode.h"


#include "nodes/equalnode.h"

#include "nodes/ifequalnode.h"
#include "nodes/ifnotequalnode.h"
#include "nodes/ifundernode.h"
#include "nodes/ifunderorequalnode.h"
#include "nodes/ifovernode.h"
#include "nodes/ifoverorequalnode.h"

#include "nodes/ifandnode.h"
#include "nodes/ifornode.h"
#include "nodes/bitwiseandnode.h"
#include "nodes/bitwiseornode.h"

#include "nodes/getvarnode.h"
#include "nodes/setvarnode.h"
#include "nodes/addconstnode.h"
#include "nodes/addvarnode.h"
#include "nodes/getfuncnode.h"
#include "nodes/numbernode.h"
#include "nodes/textnode.h"
#include "nodes/runnode.h"

#include "nodes/addnode.h"
#include "nodes/subnode.h"
#include "nodes/mulnode.h"
#include "nodes/divnode.h"
#include "nodes/modnode.h"
#include "nodes/unaryminusnode.h"
#include "nodes/unarynotnode.h"

#include "nodes/setreturnnode.h"

#include "nodes/bracketnode.h"

#include "nodes/incrementnode.h"
#include "nodes/decrementnode.h"

//#include "variables/variables.h"
#include "variables/scope.h"
#include "functions/customfunction.h"

#include "nodes/arraygetnode.h"

namespace HuwInterpreter {

    using namespace Nodes;
    using namespace Types;

    class Parser
    {
    private:
        std::shared_ptr<NodeFactory> nodeFactory;
        std::vector<std::shared_ptr<Tokens::Token>> tokens;
        std::vector<std::shared_ptr<Tokens::Token>>::iterator it;
        std::shared_ptr<Tokens::Token> currentToken;
        std::shared_ptr<Functions::FunctionManager> functions;
        std::shared_ptr<Functions::FunctionManager> customFunctions;
        bool compilation;
        std::shared_ptr<Nodes::Node> nullNode;
        std::shared_ptr<NodeFactory> codeFactory;
        std::shared_ptr<Passable> passable;

        void setCompilation(bool compilation);
        void nextToken();
        void prevToken();
        std::shared_ptr<Tokens::Token> peakToken();
        void error(const std::string msg);
        void acceptIndentation();
        void acceptSemicolon();
        bool accept(std::string s);
        bool accept(TokenType tokenType);
        bool expect(std::string s);
        bool expect(TokenType tokenType);
        std::string syntaxError(std::string content);
        bool expectSemicolon();
        void errorMessage(std::string errorMsg, std::shared_ptr<Tokens::Token> currentToken);
        std::shared_ptr<Nodes::Node> parseSquareBrackets(std::shared_ptr<Nodes::Node> node);
        std::shared_ptr<Nodes::Node> parseValue();
        std::shared_ptr<Nodes::Node> parseFactor();
        std::shared_ptr<Nodes::Node> parseTerm();
        std::shared_ptr<Nodes::Node> parseExpression();
        std::shared_ptr<Nodes::Node> parseBitwiseLeftRight();
        std::shared_ptr<Nodes::Node> parseEqualAndEqualNot();
        std::shared_ptr<Nodes::Node> parseLessThanAndLessThanOrEqual();
        std::shared_ptr<Nodes::Node> parseGreaterThanAndGreaterThanOrEqual();
        std::shared_ptr<Nodes::Node> parseBitwiseAnd();
        std::shared_ptr<Nodes::Node> parseBitwiseXOr();
        std::shared_ptr<Nodes::Node> parseBitwiseOr();
        std::shared_ptr<Nodes::Node> parseAnd();
        std::shared_ptr<Nodes::Node> parseOr();
        std::shared_ptr<Nodes::Node> parseCondition();
        std::shared_ptr<Nodes::Node> parseBoolean();
        std::shared_ptr<Nodes::Node> parseCompound();
        std::shared_ptr<Nodes::Node> parseAssingment();
        std::shared_ptr<Nodes::Node> parseFunction();
        std::shared_ptr<Nodes::Node> parseDecloration();
        std::shared_ptr<Nodes::Node> parseElseStatement();
        std::shared_ptr<Nodes::Node> parseStatement();
        std::shared_ptr<Nodes::Node> parseBlock();
    public:
        Parser(std::vector<std::shared_ptr<Tokens::Token>> tokens,
               std::shared_ptr<NodeFactory> nodeFactory);
        bool getCompilation();
        std::shared_ptr<Nodes::Node> parse();
        std::string toString();
        bool execute();
    };
}

#endif // PARSER_H
