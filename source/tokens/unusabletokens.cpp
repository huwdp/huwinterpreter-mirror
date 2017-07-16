#include "unusabletokens.h"

UnusableTokens::UnusableTokens()
{
    init();
}

void UnusableTokens::init()
{
    items.clear();
    /*
    words.push_back("\t");
    words.push_back("(");
    words.push_back(")");
    words.push_back("{");
    words.push_back("}");
    words.push_back("+");
    words.push_back("-");
    words.push_back("*");
    words.push_back("/");
    words.push_back("^");
    words.push_back("&");
    words.push_back("|");
    words.push_back("<");
    words.push_back(">");
    words.push_back("!");
    words.push_back(".");
    words.push_back("\"");
    words.push_back(",");
    words.push_back(";");
    words.push_back("=");
    words.push_back("%");
    */
    items["("] = LEFTARENTHESIS;
    items["*"] = MULTIPLICATION;
    items["/"] = DIVISION;
    items["+"] = ADDITION;
    items["-"] = SUBTRACTION;
    items["%"] = MOD;
    items["="] = EQUALS;
    items["=="] = IFEQUALS;
    items["!="] = IFNOTEQUALS;
    items["<"] = IFLESSTHAN;
    items["<="] = IFLESSTHANOREQUAL;
    items[">"] = IFGREATER;
    items[">="] = IFGREATERTHANOREQUAL;
    items["{"] = LEFTBRACKET;
    items["}"] = RIGHTBRACKET;
    items[";"] = SEMICOLON;
    items[","] = COMMA;
    items["&&"] = AND;
    items["||"] = OR;
    items["."] = DOT;
    items["*="] = MULTIPLICATIONEQUAL;
    items["/="] = DIVISIONEQUAL;
    items["+="] = ADDITIONEQUAL;
    items["-="] = SUBTRACTIONEQUAL;
    items["++"] = INCREMENT;
    items["--"] = DECREMENT;
}

bool UnusableTokens::exists(TokenType tokenType)
{
    return std::find_if(items.begin(), items.end(),
        [tokenType](const std::unordered_map<std::string, TokenType>::value_type& item) { return item.second == tokenType; }) != items.end();
}

bool UnusableTokens::exists(std::string text)
{
    return items.find(text) != items.end();
}

bool UnusableTokens::exists(char character)
{
    return items.find(std::to_string(character)) != items.end();
}

void UnusableTokens::add(TokenType tokenType, std::string text)
{
    if (!exists(tokenType))
    {
        items[text] = tokenType;
    }
}





