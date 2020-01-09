/*
1)
Memory ordering problem
This line:

        if (first == m_last.load(std::memory_order_relaxed))
            return false;
should be:

        if (first == m_last.load(std::memory_order_acquire))
            return false;
Otherwise, on the next line you may load the wrong value out of m_buffer due to the load being reordered before the load to m_last. I spotted this because I noticed a memory_order_release without a corresponding memory_order_acquire. The pop() function also needs a load of m_last with memory_order_acquire.

You have the same problem in push(). If you don't load m_first with memory_order_acquire, you run the risk of writing to the buffer when it is full, thus overwriting some element. Even the assertion won't help because you could have overwritten the buffer and then loaded a modified value for m_first.

Example of failure
Since your comment indicated that I didn't explain thoroughly enough, I will give an example of how the pop could go wrong.

The queue is empty, with m_first = m_last = 0.
The consumer calls try_pop().
In try_pop(), m_first is loaded as 0.
Now, the cpu speculatively loads m_buffer[0], even though you haven't reached that line yet.
The producer calls push().
The producer writes m_buffer[0], and then increments m_last to 1, in that order.
The consumer reads m_last as 1.
The consumer uses the value speculatively loaded in step 4 as the value for m_buffer[0], but this value is wrong.
By adding the memory_order_acquire, you prevent the load of m_buffer[0] from happening until after step 7.

2)
The management of the m_buffer is not tied to the lifetime of the queue.

The buffer is passed in as a char* buffer but the size along with it is in number of Ts it can hold. This can be confusing. Either pass in a T* directly with the number of Ts it can hold or pass the length of the buffer in bytes and then divide with sizeof(T) in the constructor;

void setup(T* buffer, U32 size) {
    m_buffer = buffer;
    m_size = size;
    clear();
}
There is no way for the producer to check if the queue is full. It will just overflow the buffer when asserts are disabled (which they will be in production).

bool isFull(){
    return inc(m_last.load(std::memory_order_relaxed)) == m_first.load(std::memory_order_relaxed);
}

3)
Since C++11 I generally prefer to stick to the standard types uint32_t and uint8_t etc. as defined in cstdint. With custom typedefs like U8 or U32 you can never be sure that the correct type has been used unless you go and check the typedef.

Similar ASSERT seems to be a custom macros - I'd prefer to stick with the standard assert.

I'd say setup is somewhat non-idiomatic C++. I would expect a constructor instead taking a buffer of type T*.
*/
template <typename T>
class LockFreeQueue {
public:
    void setup(U8* buffer, U32 size) {
        m_buffer = (T*)buffer;
        m_size = size;
        clear();
    }

    void clear() {
        m_first.store(0, std::memory_order_relaxed);
        m_last.store(0, std::memory_order_relaxed);
    }

    void push(const T& value) {   // only for single producer
        U32 last = m_last.load(std::memory_order_relaxed);
        m_buffer[last] = value;
        U32 next = inc(last);
        ASSERT(next != m_first.load(std::memory_order_relaxed), "Queue overflow");
        m_last.store(next, std::memory_order_release);
    }

    bool isEmpty() {
        return m_first.load(std::memory_order_relaxed) == m_last.load(std::memory_order_relaxed);
    }

    void pop(T& result) {    // for single consumer. check isEmpty() before
        ASSERT(!isEmpty(), "Queue is empty");
        U32 first = m_first.load(std::memory_order_relaxed);
        // U32 first = m_first.load(std::memory_order_acquire)
        result = m_buffer[first];
        m_first.store(inc(first), std::memory_order_release);
    }

    bool tryPop(T& result) {    // for multiple consumers. don't use isEmpty()
        while (true) {
            U32 first = m_first.load(std::memory_order_relaxed);
            if (first == m_last.load(std::memory_order_relaxed))
            //if (first == m_last.load(std::memory_order_acquire))
                return false;
            result = m_buffer[first];
            if (m_first.compare_exchange_weak(first, inc(first), std::memory_order_release))
                return true;
        }
    }

private:
    U32 inc(U32 n) { return (n + 1) % m_size; }

    T* m_buffer;
    U32 m_size;
    std::atomic<U32> m_first;
    std::atomic<U32> m_last;
};
