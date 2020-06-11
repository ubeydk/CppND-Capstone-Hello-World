#ifndef PAGEFETCHER_H
#define PAGEFETCHER_H

#include <string>
#include <curl/curl.h>

class PageFetcher{
    public:
    std::string FetchPage(std::string &url);
    private:
    static size_t writeCallback(char *buf, size_t size, size_t nmemb, void *up);
    CURL *_curl;
    std::string _read_buffer;
};

#endif