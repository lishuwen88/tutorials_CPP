/*
http://www.sevangelatos.com/lockless-single-producer-single-consumer-bounded-queue/

*/


template <typename T>
class queue_spsc
{
public:
    // Maximum capacity must be specified at construction time
    queue_spsc(int max_capacity);
        
    // The producer can push items in the back of the queue.
    // false is returned if the queue is full
    bool push_back(const T &item);

    // The consumer can pop items from the front of the queue.
    // false is returned if the queue is empty
    bool pop_front(T &item);
    
    
private:
    std::atomic<int> mReadPos;
    std::atomic<int> mWritePos;
    std::vector<T> mBuffer;
    
    
};

inline int increment(int pos)
{
    return (pos + 1) % int(mBuffer.size());
}

bool push_back(const T &item)
{
    int r = mReadPos;
    int w = mWritePos;
    // Assuming we write, where will we move next?
    const int next_w = increment(w);

    // Detect queue full case
    if (r == next_w)
        return false;

    mBuffer[w] = item;
    mWritePos = next_w;
    return true;
}

bool pop_front(T &item)
{
    int r = mReadPos;
    int w = mWritePos;
    // Queue is empty check
    if (r == w)
        return false;

    item = mBuffer[r];
    mReadPos = increment(r);
    return true;
}
