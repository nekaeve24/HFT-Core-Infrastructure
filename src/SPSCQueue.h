#ifndef HFT_CORE_SPSC_QUEUE_H
#define HFT_CORE_SPSC_QUEUE_H

#include <atomic>
#include <vector>
#include <memory>

/**
 * @brief A bounded Single-Producer Single-Consumer Lock-Free Queue.
 * Designed for sub-microsecond latency in HFT execution pipelines.
 */
template <typename T>
class SPSCQueue {
public:
    explicit SPSCQueue(size_t capacity);
    ~SPSCQueue() = default;

    // Producer: Returns false if the queue is full
    bool try_push(const T& data);
    
    // Consumer: Returns false if the queue is empty
    bool try_pop(T& result);

    bool empty() const;
    size_t size() const;

private:
    // Align to cache line size (typically 64 bytes) to prevent "False Sharing"
    // which is a critical HFT performance bottleneck.
    alignas(64) std::atomic<size_t> head_{0}; 
    alignas(64) std::atomic<size_t> tail_{0};

    const size_t capacity_;
    std::vector<T> buffer_;

    size_t increment(size_t index) const {
        return (index + 1) % capacity_;
    }
};

#endif // HFT_CORE_SPSC_QUEUE_H
