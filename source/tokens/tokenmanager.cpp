#include "tokenmanager.h"

TokenManager::TokenManager()
{

}

void TokenManager::init()
{

}

TokenType TokenManager::get(std::string text)
{
    return items[text];
}

TokenType TokenManager::get(char character)
{
    return items[std::string(character)];
}

std::string TokenManager::get(TokenType tokenType)
{
    return std::find_if(items.begin(), items.end(), [](bool){(*it).second == std::string(character);}).first;
}

