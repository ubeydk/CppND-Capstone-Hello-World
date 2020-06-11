#include <iostream>
#include <curl/curl.h>
#include <string>
#include <chrono> 

#include "PageFetcher.h"
#include "TextProcessor.h"
#include "Pokemon.h"
#include "MessageQueue.h"

int main() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    auto start = std::chrono::high_resolution_clock::now();
    std::string url = "https://www.pokemon.com/us/pokedex/vaporeon";
    PageFetcher pf;
    std::string page_text = pf.FetchPage(url);
    Pokemon poke("vaporeon");
    MessageQueue message_queue;
    TextProcessor::ProcessText(page_text, poke, message_queue);
    
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout<<"Execution duration: "<<duration.count()<<"\n";
    return 0;
}