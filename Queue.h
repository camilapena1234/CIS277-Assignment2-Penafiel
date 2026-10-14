#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef>
#include <vector>

template <typename T>
class Queue {
private:
    std::vector<T> data_;
    std::size_t head_;
    std::size_t size_;
    std::size_t capacity_;

public:
    explicit Queue(std::size_t capacity)
        : data_(capacity), head_(0), size_(0), capacity_(capacity) {}

    bool enqueue(const T& value) {
        if (full()) {
            return false;
        }

        std::size_t index = (head_ + size_) % capacity_;
        data_[index] = value;
        ++size_;
        return true;
    }

    bool dequeue(T& value) {
        if (empty()) {
            return false;
        }

        value = data_[head_];
        head_ = (head_ + 1) % capacity_;
        --size_;
        return true;
    }

    bool front(T& value) const {
        if (empty()) {
            return false;
        }

        value = data_[head_];
        return true;
    }

    bool empty() const {
        return size_ == 0;
    }

    bool full() const {
        return size_ == capacity_;
    }

    std::size_t size() const {
        return size_;
    }

    std::size_t capacity() const {
        return capacity_;
    }
};

#endif
