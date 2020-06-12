#include "MessageQueue.h"

void MessageQueue::send(std::string &&msg)
{
    std::lock_guard<std::mutex> uLock(_queue_mutex);
    if(_message_set.insert(msg).second){
        _queue.push_back(std::move(msg));
        _cond.notify_one();
    }
}

std::string MessageQueue::receive()
{   
    std::unique_lock<std::mutex> uLock(_queue_mutex);
    _cond.wait(uLock, [this](){
        return !_queue.empty() || is_done();
    });
    if(is_done())
        throw "Processing ended";
    std::string msg = std::move(_queue.back());
    increase_processing_message_num();
    _queue.pop_back();
    return msg;
}


void MessageQueue::increase_processing_message_num(){
    std::lock_guard<std::mutex> num_lock(_num_mutex);
    _processing_message_number++;
}

void MessageQueue::decrease_processing_message_num(){
    std::lock_guard<std::mutex> num_lock(_num_mutex);
    if(--_processing_message_number == 0 && _queue.empty()){
        _cond.notify_all();
    }
}

bool MessageQueue::is_done(){
    return _queue.empty() && _processing_message_number == 0;
}
