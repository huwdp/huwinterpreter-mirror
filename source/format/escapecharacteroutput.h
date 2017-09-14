#ifndef ESCAPECHARACTEROUTPUT_H
#define ESCAPECHARACTEROUTPUT_H

#include <string>

class EscapeCharacterOutput
{
public:
    EscapeCharacterOutput();
    std::string output(char value);
    std::string output(std::string value);
};

#endif // ESCAPECHARACTEROUTPUT_H
