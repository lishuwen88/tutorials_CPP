/*
https://groups.google.com/forum/#!msg/lock-free/ehUtb0_JmFI/dEzBcK8hltMJ

Several comments wrt performance. The padding between head and tail 
does not make sense, because threads always touch them at the same 
time. So with padding they only need to load 2 cache lines instead of 
1. 

You don't need fetch_add to update positions. It is usually compiled 
to an expensive atomic read-modify-write instruction. Plain store is 
enough here. 

The most efficient SPSC queues do not require producer and consumer to 
synchronize during each operation. Instead of both producer and 
consumer looking at both head and tail, they use per-element 
synchronization state that allows them to use mostly independently. 
Search this group or comp.programming.threads archives for SPSC, or 
check out these articles: 
http://www.1024cores.net/home/lock-free-algorithms/queues/fastflow 
http://www.1024cores.net/home/lock-free-algorithms/queues/unbounded-spsc-queue
*/



template<typename T, size_t Size>
class queue_t
{
   typedef uint64_t uint_t;
   static const size_t padding_size = 256;

   char padding0_[padding_size];
   T values_[Size];
   char padding1_[padding_size];
   std::atomic<uint_t> head_;
   char padding2_[padding_size];
   std::atomic<uint_t> tail_;


public:
   queue_t ()
      : head_ (0)
      , tail_ (0)
   {
      // should have been static_assert but my compiler does not support it yet
      assert (Size >= 2 && ((Size - 1) & Size) == 0); // power of two
   }


   bool enqueue (const T & value)
   {
      const uint_t head = head_.load (std::memory_order_relaxed);
      const uint_t tail = tail_.load (std::memory_order_acquire);


      // full?
      if ((head - tail) == Size) 
         return false;

      values_[head & (Size - 1)] = value;
      assert (head < std::numeric_limits<uint_t>::max ());
      head_.fetch_add (1, std::memory_order_release);
      return true;
   }
   
   bool dequeue (T & value)
   {
      const uint_t head = head_.load (std::memory_order_acquire);
      const uint_t tail = tail_.load (std::memory_order_relaxed);


      // empty?
      if (head == tail) 
         return false;

      value = values_[tail & (Size - 1)];
      tail_.fetch_add (1, std::memory_order_release);
      return true;
   }

};
