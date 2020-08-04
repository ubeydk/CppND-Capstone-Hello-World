#ifndef POKEMON_H
#define POKEMON_H


#include <string>
#include <vector>

class Pokemon{
public:
    Pokemon(const std::string&);
    std::string name;
    std::string height;
    std::string weight;
    std::string description;
    //////////////////////////////////////////////////////////////
    // More field can be added but I didn't add for simplicity  //
    //////////////////////////////////////////////////////////////
};


#endif