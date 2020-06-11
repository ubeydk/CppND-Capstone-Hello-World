#include <string>
#include <sstream>

//TEMP below
#include <iostream>

#include "TextProcessor.h"
#include "MessageQueue.h"


void TextProcessor::ProcessText(
        const std::string &text, Pokemon &pokemon, MessageQueue &message_queue){
    std::istringstream string_stream(text);
    std::string line; 
    std::cout<<"********PROCESSING HAS STARTED**********\n";
    // find ref to previous pokemon
    while(std::getline(string_stream, line)){
        if(line.find("class=\"previous\"") != std::string::npos){
            message_queue.send(TextProcessor::extractPokemonRefFromLine(line));
            break;
        }
    }

    // find ref to next pokemon
    while(std::getline(string_stream, line)){
        if(line.find("class=\"next\"") != std::string::npos){
            message_queue.send(TextProcessor::extractPokemonRefFromLine(line));
            break;
        }
    }
    // get descriptions
    /////
    while(std::getline(string_stream, line)){
        if(line.find("version-x") != std::string::npos){
            std::getline(string_stream, line);
            if(line.find('>') != std::string::npos)
                std::getline(string_stream, line);
            std::istringstream mini_stream(line);
            std::string word;
            while(mini_stream >> word){
                pokemon.description.append(word + " ");
            }
            pokemon.description.append("\n");
            break;
        }
    }

    while(std::getline(string_stream, line)){
        if(line.find("version-y") != std::string::npos){
            std::getline(string_stream, line);
            if(line.find('>') != std::string::npos)
                std::getline(string_stream, line);
            std::istringstream mini_stream(line);
            std::string word;
            while(mini_stream >> word){
                pokemon.description.append(word + " ");
            }
            break;
        }
    }
    /////

    while(std::getline(string_stream, line)){
        if(line.find("Height") != std::string::npos){
            std::getline(string_stream, line);
            pokemon.height = extractDataFromLine(line);
            break;
        }
    }

    while(std::getline(string_stream, line)){
        if(line.find("Weight") != std::string::npos){
            std::getline(string_stream, line);
            pokemon.weight = extractDataFromLine(line);
            break;
        }
    }
    std::cout<<pokemon.name<<" \n"<<pokemon.height<<" \n"<<pokemon.weight<<std::endl;
    std::cout<<pokemon.description;
}

std::string TextProcessor::extractPokemonRefFromLine(std::string &line){
    std::istringstream string_stream(line);
    std::string subpart;
    std::string pokemon_name = "";
    while(string_stream>>subpart){
        if(subpart.find("href") != std::string::npos){
            pokemon_name = subpart.substr(subpart.find_last_of('/') + 1);
            pokemon_name.pop_back();
            break;
        }
    }
    return std::move(pokemon_name);
}

std::string TextProcessor::extractDataFromLine(std::string &line){
    int first_open = line.find_first_of('>');
    int last_close = line.find_last_of('<');
    std::string data = line.substr(first_open + 1, last_close - first_open - 1);
    return std::move(data);
}