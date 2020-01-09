int data = 0;
bool ready = false;

// called on thread 1
void produce( int value )
{
	data = value;
	ready = true;
}

// called on thread 2
bool try_consume( int& out_value )
{
	if( ready )
	{
		out_value = data;
		return true;
	}
	return false;
}


// version 2
int data = 0;
std::atomic<bool> ready = false;

// called on thread 1
void produce( int value )
{
	data = value;

	// Memory operations before this cannot be reordered past it
	ready.store( true, std::memory_order_release );
}

// called on thread 2
bool try_consume( int& out_value )
{
	// Memory operations after this cannot be reordered before it
	if( ready.load( std::memory_order_acquire ) )
	{
		out_value = data;
		return true;
	}
	return false;
}
