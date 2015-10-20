#ifndef RING_BUFFER_H
#define RING_BUFFER_H
#include <stdint.h>
#include <unistd.h>

template <typename T, size_t length>
class RingBuffer {
public:
    RingBuffer()
    : storage_count_{0},
      push_index_{0},
      pop_index_{0}
    {}

    ~RingBuffer()
    {}


    size_t getCount(void)
    {
        return storage_count_;
    }


    void push(T pushed_tval)
    {
        buffer_[push_index_] = pushed_tval;

        ++push_index_;
        if (push_index_ == length)
            push_index_ = 0;

/// head and tail follow each other if ring buffer is full.
        if (storage_count_ == length)
        {
            ++pop_index_;
            if (pop_index_ == length)
                pop_index_ = 0;
        }
        else
        {
            ++storage_count_;
        }
    }


    bool pop(T& popped_tval)
    {
        if (storage_count_ > 0)
            --storage_count_;
        else
            return false;

        popped_tval = buffer_[pop_index_];

        if (pop_index_ > 0)
            --pop_index_;
        else
            pop_index_ = length - 1;
        return true;
    }

    bool peek(T& peeked_tval)
    {
        if (storage_count_ == 0)
            return false;
        peeked_tval = buffer_[pop_index_];
        return true;
    }

private:
    size_t push_index_;
    size_t pop_index_;
    size_t storage_count_;

    T buffer_[length];

};
#endif
