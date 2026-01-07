#include "SPSCQueue.h"

template <typename T>
SPSCQueue<T>::SPSCQueue(size_t capacity) 
    : capacity_(capacity + 1), buffer_(capacity + 1) {}

template <typename T>
bool SPSCQueue<T>::try_push(const T& data) {
    const size_t head = head_.load(std::memory_order_relaxed);
    const size_t next_head = increment(head);
    
    // Check if full: head+1 == tail
    if (next_head == tail_.load(std::memory_order_acquire)) {
        return false;
    }
    
    buffer_[head] = data;
    // Release ensures the data write is visible before the head update
    head_.store(next_head, std::memory_order_release);
    return true;
}

template <typename T>
bool SPSCQueue<T>::try_pop(T& result) {
    const size_t tail = tail_.load(std::memory_order_relaxed);
    
    // Check if empty: tail == head
    if (tail == head_.load(std::memory_order_acquire)) {
        return false;
    }
    
    result = std::move(buffer_[tail]);
    // Release ensures the data move is complete before the tail update
    tail_.store(increment(tail), std::memory_order_release);
    return true;
}
