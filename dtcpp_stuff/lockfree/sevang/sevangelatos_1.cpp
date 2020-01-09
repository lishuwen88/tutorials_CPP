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
};
