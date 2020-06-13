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

std::string URL_PREFIX = "https://www.pokemon.com/us/pokedex/";
int DEFAULT_NUMBER_OF_THREADS = 4;

std::mutex vector_mutex;
std::vector<Pokemon> pokemons;

MessageQueue message_queue;
std::atomic<int> counter;
int limit = INT_MAX;

void fetch_and_process_pages(){
    PageFetcher pageFetcher;
    while(++counter <= limit){
        try{
            std::string pokemon_name = message_queue.receive();
            std::string url = URL_PREFIX + pokemon_name;
            Pokemon pokemon(pokemon_name);
            std::cout<<url<<" processing\n";
            std::string page_text = pageFetcher.FetchPage(url);
            TextProcessor::ProcessText(message_queue, pokemon, page_text);
            std::lock_guard<std::mutex> num_lock(vector_mutex);
            pokemons.emplace_back(pokemon);
        }catch(...){
            break;
        }
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
        limit = std::stoi(argv[2]);
    std::vector<std::thread> threads;
    
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < number_of_threads; i++)
        threads.emplace_back(std::thread(fetch_and_process_pages));
    for(auto &thread:threads)
        thread.join();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout<<"Number of threads: "<< number_of_threads <<"\n";
    std::cout<<"\nExecution duration: "<<duration.count()<<" microseconds\n";

    std::ofstream file;
    file.open("pokemons.txt");
    for(auto &pokemon : pokemons)
        file << stringify_pokemon(pokemon);
    file.close();
    return 0;
}