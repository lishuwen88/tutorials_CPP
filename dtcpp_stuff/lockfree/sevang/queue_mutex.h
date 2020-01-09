#pragma once
#ifndef QUEUE_MUTEX_H
#define QUEUE_MUTEX_H

#include <vector>
#include <cassert>
#include <mutex>

template <typename T>
class queue_mutex
{
public:
    queue_mutex(int max_capacity)
        : mBuffer(max_capacity + 1)
        , mReadPos(0)
        , mWritePos(0)
    {
        assert(max_capacity > 0);
        // Protect from integer overflow
        assert(max_capacity + 1 > 0);
    }

    bool push_back(const T &item)
    {
        std::lock_guard<std::mutex> guard(mLock);
        const int r = mReadPos;
        const int w = mWritePos;

        // Assuming we write, where will we move next?
        const int next_w = increment(w);

        // The two pointers colliding means we would have exceeeded the
        // queue size and create an ambiguous state with being empty..
        if (r == next_w)
            return false;

        mBuffer[w] = item;
        mWritePos = next_w;
        return true;
    }

    bool pop_front(T &item)
    {
        std::lock_guard<std::mutex> guard(mLock);
        int r = mReadPos;
        int w = mWritePos;
        // Queue is empty (or was empty when we checked)
        if (r == w)
            return false;

        item = mBuffer[r];
        mReadPos = increment(r);
        return true;
    }

private:
    inline int increment(int pos) const
    {
        return (pos + 1) % int(mBuffer.size());
    }

    std::vector<T> mBuffer;
    int mReadPos;
    int mWritePos;
    std::mutex mLock;
};

#endif // QUEUE_MUTEX_H
