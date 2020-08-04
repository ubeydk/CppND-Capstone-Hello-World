#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <deque>
#include <condition_variable>
#include <mutex>
#include <unordered_set>
#include <string>

template <typename T>
class MessageQueue{
public:
    void send(T msg){
        std::lock_guard<std::mutex> uLock(_queue_mutex);
        if(_message_set.insert(msg).second){
            _queue.push_back(std::move(msg));
            _cond.notify_one();
        }
    }

    std::pair<T, bool> receive(){
        std::unique_lock<std::mutex> uLock(_queue_mutex);
        _cond.wait(uLock, [this](){
            return !_queue.empty() || is_done();
        });
        if(is_done())
            return {T(), false}; // if message queue is empty, returns second value as false
        std::string msg = std::move(_queue.back());
        increase_processing_message_num();
        _queue.pop_back();
        return {msg, true};
    }

    void increase_processing_message_num(){
        std::lock_guard<std::mutex> num_lock(_num_mutex);
        _processing_message_number++;
    }

    void decrease_processing_message_num(){
        std::lock_guard<std::mutex> num_lock(_num_mutex);
        if(--_processing_message_number == 0 && _queue.empty()){
            _cond.notify_all();
        }
    }
    
private:
    bool is_done(){
        return _queue.empty() && _processing_message_number == 0;
    }
    std::unordered_set<T> _message_set; // to check uniqueness of messages
    std::deque<T> _queue;
    std::mutex _queue_mutex;
    std::mutex _num_mutex;
    std::condition_variable _cond;
    int _processing_message_number = 0;
};

#endif