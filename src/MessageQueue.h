#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <deque>
#include <condition_variable>
#include <mutex>
#include <unordered_set>
#include <string>

class MessageQueue
{
public:
    void send(std::string &&msg);
    std::string receive();
    void increase_processing_message_num();
    void decrease_processing_message_num();
    
private:
    bool is_done();
    std::unordered_set<std::string> _message_set; // to check uniqueness of messages
    std::deque<std::string> _queue;
    std::mutex _queue_mutex;
    std::mutex _num_mutex;
    std::condition_variable _cond;
    int _processing_message_number = 0;
};

#endif