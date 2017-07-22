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

#ifndef TOKENTYPES
#define TOKENTYPES

enum TokenType {RIGHTPARENTHESIS,
                 LEFTARENTHESIS,
                 MULTIPLICATION,
                 DIVISION,
                 ADDITION,
                 SUBTRACTION,
                 MOD,
                 EQUALS,
                 IFEQUALS,
                 IFNOTEQUALS,
                 IFLESSTHAN,
                 IFLESSTHANOREQUAL,
                 IFGREATER,
                 IFGREATERTHANOREQUAL,
                 LEFTBRACKET,
                 RIGHTBRACKET,
                 SEMICOLON,
                 COMMA,
                 WORD,
                 NUMBER,
                 INDENTATION,
                 TABINDENTATION,
                 TEXT,
                 QUOTE,
                 AND,
                 OR,
                 BITWISEAND,
                 BITWISEOR,
                 DOT,
                 MULTIPLICATIONEQUAL,
                 DIVISIONEQUAL,
                 ADDITIONEQUAL,
                 SUBTRACTIONEQUAL,
                 INCREMENT,
                 DECREMENT,
                 NOT
};


enum VarType
{
    INTEGER,
    DOUBLE,
    STRING,
    ARRAY,
    NUMBERA,
    NONE
};

#endif // TOKENTYPES
