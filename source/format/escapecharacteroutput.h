#ifndef ESCAPECHARACTEROUTPUT_H
#define ESCAPECHARACTEROUTPUT_H

#include <string>

namespace HuwInterpreter {
    namespace Helpers {
        class EscapeCharacterOutput
        {
        public:
            EscapeCharacterOutput();
            static std::string output(char value);
            static std::string output(std::string value);
        };
    }
}

#endif // ESCAPECHARACTEROUTPUT_H
