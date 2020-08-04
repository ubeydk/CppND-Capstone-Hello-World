#include <iostream>
#include <curl/curl.h>
#include <string>
#include <chrono> 
#include <thread>
#include <atomic>
#include <climits>
#include <mutex>
#include <fstream>

#include "PageFetcher.h"
#include "TextProcessor.h"
#include "Pokemon.h"
#include "MessageQueue.h"

const int DEFAULT_NUMBER_OF_THREADS = 4;
const int DEFAULT_POKEMON_LIMIT = 100;
const std::string URL_PREFIX = "https://www.pokemon.com/us/pokedex/";

std::mutex vector_mutex;
std::vector<Pokemon> pokemons;

MessageQueue<std::string> message_queue;
std::atomic<int> counter;
int pokemon_limit = DEFAULT_POKEMON_LIMIT;

void fetch_and_process_pages(){
    PageFetcher pageFetcher;
    while(++counter <= pokemon_limit){
        auto [pokemon_name, is_not_empty] = message_queue.receive();
        if(!is_not_empty)
            return;
        std::string url = URL_PREFIX + pokemon_name;
        Pokemon pokemon(pokemon_name);
        std::cout<<"processing: "<<url<<"\n";
        std::string page_text = pageFetcher.FetchPage(url);
        TextProcessor::ProcessText(message_queue, pokemon, page_text);
        std::lock_guard<std::mutex> num_lock(vector_mutex);
        pokemons.emplace_back(pokemon);
    }
}

std::string stringify_pokemon(Pokemon &pokemon){
    std::string data = "";
    data.append("name: " + pokemon.name + "\n");
    data.append("height: " + pokemon.height + "\n");
    data.append("weight: " + pokemon.weight + "\n");
    data.append("description: " + pokemon.description + "\n");
    data.append("---------\n");
    return data;
}

int main(int argc, char **argv) {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    counter = 0;

    std::string initial_pokemon_name = "vaporeon";
    message_queue.send(std::move(initial_pokemon_name));
    int number_of_threads = DEFAULT_NUMBER_OF_THREADS;
    if(argc > 1)
        number_of_threads = std::stoi(argv[1]);
    if(argc > 2)
        pokemon_limit = std::stoi(argv[2]);
    std::vector<std::thread> threads;
    
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < number_of_threads; i++)
        threads.emplace_back(std::thread(fetch_and_process_pages));
    for(auto &thread:threads)
        thread.join();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration_in_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    auto duration_in_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout<< "Number of threads: " << number_of_threads <<"\n";
    std::cout<< "Number of pokemons processed: " << pokemon_limit <<"\n";
    std::cout<< "Execution duration in microseconds: \t" << duration_in_microseconds.count() << "\n";
    std::cout<< "Execution duration in seconds: \t\t" << duration_in_milliseconds.count() / 1000.0 << "\n";

    std::ofstream file;
    file.open("pokemons.txt");
    for(auto &pokemon : pokemons)
        file << stringify_pokemon(pokemon);
    file.close();
    return 0;
}