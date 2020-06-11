#include "PageFetcher.h"

#include <curl/curl.h>
#include <string>
#include <stdexcept>

std::string PageFetcher::FetchPage(std::string &url){
    _curl = curl_easy_init();
    curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, &PageFetcher::writeCallback);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &_read_buffer);
    if (_curl == nullptr)
        throw std::runtime_error("Failed to create CURL connection");
    CURLcode code = curl_easy_perform(_curl);
    return std::move(_read_buffer);
}

size_t PageFetcher::writeCallback(char *buf, size_t size, size_t nmemb, void *up){
    ((std::string *)up)->append((char *)buf, size * nmemb);
    return size * nmemb;
}


