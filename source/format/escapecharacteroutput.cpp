#include "escapecharacteroutput.h"

EscapeCharacterOutput::EscapeCharacterOutput()
{

}

std::string EscapeCharacterOutput::output(char value)
{
    if (value == '"')
    {
        return "\\\"";
    }
    else if (value == '\\')
    {
        return "\\";
    }
    std::string character = std::string(1, value);
    return character;
}

std::string EscapeCharacterOutput::output(std::string value)
{
    std::string output;
    for (std::string::iterator it = value.begin(); it != value.end(); ++it)
    {
        if ((*it) == '"')
        {
            output.append("\\\"");
        }
        else if ((*it) == '\\')
        {
            output.append("\\");
        }
        else
        {
            output.append(1, (*it));
        }
    }
    return output;
}


