

template‹typename Element, size_t Size› 
class CircularFifo{
public:
  enum { Capacity = Size+1 };

  CircularFifo() : _tail(0), _head(0){}   
  virtual ~CircularFifo() {}

  bool push(const Element& item); 
  bool pop(Element& item);

  bool wasEmpty() const;
  bool wasFull() const;
  bool isLockFree() const;

private:
  size_t increment(size_t idx) const; 

  std::atomic‹size_t›  _tail;  
  Element              _array[Capacity];
  std::atomic‹size_t›  _head; 
};

/* Producer only: updates tail index after setting the element in place */
bool push(Element& item_)
{	
  auto current_tail = _tail.load();            
  auto next_tail = increment(current_tail);    
  if(next_tail != _head.load())                         
  {
    _array[current_tail] = item;               
    _tail.store(next_tail);                    
    return true;
  }
  
  return false;  // full queue
}

/* Consumer only: updates head index after retrieving the element */
bool pop(Element& item)
{
  const auto current_head = _head.load();  // 1. loads sequentially the head
  if(current_head == _tail.load())         // 2. compares head to snapshot of tail
    return false;   // empty queue

  item = _array[current_head];             // 3. retrievs the item pointed to by head
  _head.store(increment(current_head));    // 4. update the head index to new position
  return true;
}

bool wasFull() const
{
  const auto next_tail = increment(_tail.load());
  return (next_tail == _head.load());
}


size_t increment(size_t idx) const
{
  return (idx + 1) % Capacity;
}

bool CircularFifo::wasFull() const
{
  auto index = _tail.load();
  auto next_tail = (index + 1) % Capacity;
  return (next_tail == _head.load());
}

bool CircularFifo::wasFull() const
{
  auto index = _tail.load(std::memory_order_seq_cst);
  auto next_tail = (index + 1) % Capacity;
  return (next_tail == _head.load(std::memory_order_seq_cst));
}

bool wasEmpty() const
{
  return (_head.load() == _tail.load());
}
