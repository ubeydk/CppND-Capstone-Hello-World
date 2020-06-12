#ifndef TEXTPROCESSOR_H
#define TEXTPROCESSOR_H

#include <string>

#include "Pokemon.h"
#include "MessageQueue.h"

class TextProcessor{
    public:
    static void ProcessText(
        MessageQueue &message_queue, Pokemon &pokemon, const std::string &text);
    private:
    TextProcessor();
    static std::string extractDataFromLine(std::string &line);
    static std::string extractPokemonRefFromLine(std::string &line);
};


#endif