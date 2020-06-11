#ifndef TEXTPROCESSOR_H
#define TEXTPROCESSOR_H

#include <string>

#include "Pokemon.h"
#include "MessageQueue.h"

class TextProcessor{
    public:
    static void ProcessText(
        const std::string &text, Pokemon &pokemon, MessageQueue &message_queue); //TODO take queue and pokemon array
    private:
    TextProcessor();
    static std::string extractDataFromLine(std::string &line);
    static std::string extractPokemonRefFromLine(std::string &line);
};


#endif