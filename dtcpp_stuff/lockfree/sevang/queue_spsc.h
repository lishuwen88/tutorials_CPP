#pragma once
#ifndef SPRX_QUEUE_SPSC
#define SPRX_QUEUE_SPSC

#include <vector>
#include <atomic>
#include <cassert>

template <typename T>
class queue_spsc
{
public:
	queue_spsc(int max_capacity)
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
		const int r = mReadPos.load(std::memory_order_consume);
		const int w = mWritePos.load(std::memory_order_consume);

		// Assuming we write, where will we move next?
		const int next_w = increment(w);

		// The two pointers colliding means we would have exceeeded the
		// queue size and create an ambiguous state with being empty..
		if (r == next_w)
			return false;

		mBuffer[w] = item;
		mWritePos.store(next_w, std::memory_order_release);
		return true;


	}

	bool pop_front(T &item)
	{
		int r = mReadPos.load(std::memory_order_consume);
		int w = mWritePos.load(std::memory_order_consume);
		// Queue is empty (or was empty when we checked)
		if (r == w)
			return false;

		item = mBuffer[r];
		mReadPos.store(increment(r), std::memory_order_release);
		return true;
	}

private:
	inline int increment(int pos) const
	{
		return (pos + 1) % int(mBuffer.size());
	}

	std::vector<T> mBuffer;
	std::atomic<int> mReadPos;
	std::atomic<int> mWritePos;
};

#endif

